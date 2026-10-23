OOM Killer Deep Dive Lab

Memory Exhaustion → OOM Killer → OOM Scoring → Process Protection

A hands-on Linux troubleshooting lab demonstrating how to reproduce memory pressure, observe the kernel OOM killer, inspect oom_score and oom_score_adj, and protect a process from OOM-killer selection.

1. Lab Objective

Check available RAM and swap before generating memory pressure.

Run stress-ng to deliberately consume memory.

Observe the Linux kernel invoking the OOM killer.

Identify which processes are being killed and inspect their OOM values.

Understand oom_score versus oom_score_adj.

Protect a test process using oom_score_adj = -1000.

Trigger memory pressure again and verify that the protected process survives.

2. OOM Score vs OOM Score Adj

Value

What it means

Range / effect

oom_score

Kernel-calculated score used when selecting an OOM victim.

Higher value = more likely to be killed.

oom_score_adj

Adjustment applied to influence the OOM decision.

-1000 = protected; 0 = neutral; +1000 = strong preference to kill.

Important: oom_score is calculated by the kernel and can change with the process's memory usage. oom_score_adj is the administrator-controlled bias. A process with oom_score_adj = -1000 is excluded from normal OOM-killer victim selection.

Step 1: Check Memory and Existing stress-ng Processes

Command executed:

free -h
ps -ef | grep stress-ng

Execution screenshot

<img width="1177" height="302" alt="image" src="https://github.com/user-attachments/assets/6292ae1f-aed3-427c-8f49-2136a5aebed9" />




What this shows: The VM has about 1.7 GiB RAM. The screenshot also shows stress-ng processes running with a 3G memory workload. This establishes why the VM can reach memory pressure quickly.

Step 2: Stop the Existing Stress Workload and Check the System

Command executed:

pkill stress-ng
ps -ef | grep stress-ng
free -h
vmstat 1 5

Execution screenshot

<img width="1026" height="407" alt="image" src="https://github.com/user-attachments/assets/93a28939-372a-4d8f-8842-738c24c56258" />




What this shows: After killing stress-ng, free memory rises to roughly 1.4 GiB and swap usage falls. vmstat shows the system after the workload has been removed.

Step 3: Confirm OOM-Killer Activity in the Kernel Log

Command executed:

journalctl -k | grep -i "out of memory" | tail -10

Execution screenshot

<img width="1867" height="1011" alt="image" src="https://github.com/user-attachments/assets/a2c9212d-fa3e-4147-ad48-d054ff8eab77" />



What this shows: The kernel reports repeated messages such as 'Out of memory: Killed process ... (stress-ng)'. The log also shows oom_score_adj:1000 for the stress-ng victims. This is direct evidence that the kernel OOM killer is terminating memory-consuming stress-ng workers.

Step 4: Inspect oom_score and oom_score_adj

Command executed:

for pid in $(pgrep stress-ng); do
  echo "PID=$pid"
  echo -n "oom_score="
  cat /proc/$pid/oom_score
  echo -n "oom_score_adj="
  cat /proc/$pid/oom_score_adj
done

Execution screenshot

<img width="975" height="537" alt="image" src="https://github.com/user-attachments/assets/6432130f-bec4-4f5f-9b5a-67b8014206e2" />




What this shows: This compares the two values for the running stress-ng processes. Notice that oom_score and oom_score_adj are different concepts: oom_score is the calculated score, while oom_score_adj is the adjustment. In this captured run, some stress-ng processes show -1000 while worker processes show +1000, illustrating that different processes can have different adjustments.

Step 5: Create a Test Process and Check Its OOM Adjustment

Command executed:

sleep 1000 &
ps -p <PID> -o pid,cmd
cat /proc/<PID>/oom_score_adj

Execution screenshot

<img width="817" height="310" alt="image" src="https://github.com/user-attachments/assets/50b48346-cbed-4039-8426-6f8dfa82baa9" />




What this shows: The test process is sleep 1000. Its initial oom_score_adj is 0, which is the neutral/default setting.

Step 6: Protect the Process with oom_score_adj = -1000

Command executed:

echo -1000 > /proc/<PID>/oom_score_adj
cat /proc/<PID>/oom_score_adj

Execution screenshot

<img width="817" height="310" alt="image" src="https://github.com/user-attachments/assets/a2232763-28f9-47d1-98c4-f40060f4c459" />




What this shows: The value changes from 0 to -1000. This is the key protection step. A process with oom_score_adj = -1000 is protected from normal OOM-killer victim selection.

Step 7: Trigger Memory Pressure Again and Verify Protection

Command executed:

stress-ng --vm 2 --vm-bytes 3G --timeout 60s
ps -p <PID> -o pid,cmd
cat /proc/<PID>/oom_score_adj
journalctl -k | grep -i "out of memory" | tail -5

Execution screenshot

<img width="1917" height="871" alt="image" src="https://github.com/user-attachments/assets/44b0d3b2-5cec-4d60-935e-362141ad5a99" />



What this shows: This is the complete proof of the lab. stress-ng generates the memory pressure and the kernel records OOM kills for stress-ng processes. At the same time, the protected sleep process (PID 2705 in the screenshot) is still present and its oom_score_adj remains -1000.

3. Final Lab Conclusion

The experiment successfully demonstrates the Linux OOM-killer workflow:

Memory becomes scarce because stress-ng requests more memory than the VM can comfortably provide.

The kernel invokes the OOM killer.

The kernel selects memory-consuming stress-ng processes as victims.

oom_score represents the calculated OOM kill preference.

oom_score_adj modifies that preference.

Setting oom_score_adj to -1000 protects the selected process.

The protected process remains alive while stress-ng processes are killed during OOM conditions.

4. Interview-Ready Explanation

If asked, 'How do you protect a critical Linux process from the OOM killer?'

Answer: I can set the process's /proc/<PID>/oom_score_adj value to -1000. The range is -1000 to +1000. Negative values make the process less likely to be selected, while positive values make it more likely. -1000 provides OOM-killer protection. I would verify it with cat /proc/<PID>/oom_score_adj and then reproduce memory pressure to confirm the process survives.

5. GitHub Project Description

OOM Killer Deep Dive Lab — Reproduced Linux memory exhaustion using stress-ng, analyzed kernel OOM-killer logs, inspected oom_score and oom_score_adj, and protected a critical test process using oom_score_adj = -1000. Verified the result by triggering memory pressure and confirming that stress-ng workers were killed while the protected process remained running.
