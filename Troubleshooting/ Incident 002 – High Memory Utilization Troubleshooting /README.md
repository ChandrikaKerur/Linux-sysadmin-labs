# 🚨 Incident 002 – High Memory Utilization Troubleshooting (Rocky Linux 9)

## 📖 Overview
This lab demonstrates how to investigate and resolve a High Memory Utilization issue on a Red Hat Enterprise Linux (RHEL 9) server. The objective is to identify the process consuming excessive memory, investigate the issue, resolve it safely, and verify that the server has returned to a healthy state.

---

## 🎯 Scenario
The application team reports that the Linux server has become slow due to high memory utilization. As a Linux System Administrator, I performed the following troubleshooting steps.

---

## Step 1 – Verify Memory Utilization

```bash
free -h
```

**Purpose:** Check Total, Used, Free, Available Memory and Swap Usage.

📷 Screenshot: `free -h`
<img width="940" height="102" alt="image" src="https://github.com/user-attachments/assets/7d537530-0f77-4604-bbdd-a39d3a6e9c4f" />

---

## Step 2 – Monitor System Performance

```bash
vmstat 1 5
```

**Purpose:** Monitor memory statistics, CPU utilization, running processes, and swap activity.

📷 Screenshot: `vmstat`

<img width="940" height="149" alt="image" src="https://github.com/user-attachments/assets/b818a3fd-223d-4d5c-87ab-1edba8677454" />

---

## Step 3 – Monitor in Real Time

```bash
top
```

**Purpose:** Observe real-time CPU, memory usage, and identify memory-intensive processes.

📷 Screenshot: `top`

<img width="940" height="470" alt="image" src="https://github.com/user-attachments/assets/3ec79ea7-5f2e-4b85-a842-75eb0927cf5a" />


---

## Step 4 – Identify High Memory Process

```bash
ps -eo pid,user,%mem,%cpu,cmd --sort=-%mem | head
```

**Purpose:** Display processes sorted by highest memory usage.

📷 Screenshot: `ps`

<img width="940" height="470" alt="image" src="https://github.com/user-attachments/assets/38c1c2e9-bdff-4a8e-8c4b-57141a4584ad" />


---

## Step 5 – Verify the Process

```bash
ps -fp <PID>
```

**Purpose:** Verify the process owner and command before taking any action.

---

## Step 6 – Resolve the Issue

Terminate the process gracefully.

```bash
kill <PID>
```

If it does not terminate:

```bash
kill -9 <PID>
```

📷 Screenshot: Process Termination

<img width="940" height="186" alt="image" src="https://github.com/user-attachments/assets/41f48bbf-b5b1-4635-8dbb-2aed54b94834" />


---

## Step 7 – Verify Resolution

```bash
free -h
top
vmstat 1 5
```

**Observation:**
- Memory utilization returned to normal.
- Available memory increased.
- No abnormal memory-consuming processes remained.
- System performance returned to normal.

📷 Screenshots: `free -h`, `top`, `vmstat`
<img width="940" height="222" alt="image" src="https://github.com/user-attachments/assets/5d318885-451e-4065-8bbf-58e711e02fb5" />


---

## 🔍 Root Cause Analysis (RCA)

The high memory utilization was intentionally caused using the `stress-ng` utility to simulate a production-like incident. The `stress-ng` process consumed most of the available memory, resulting in memory pressure and slower system performance. No Out of Memory (OOM) event occurred because the allocated memory remained within the available system resources.

---

## ✅ Resolution

- Verified memory utilization using `free -h`
- Monitored performance using `vmstat`
- Identified the high-memory process using `ps`
- Verified the process details
- Terminated the process gracefully
- Confirmed memory utilization returned to normal

---

## 🛠 Commands Used

```bash
free -h
vmstat 1 5
top
ps -eo pid,user,%mem,%cpu,cmd --sort=-%mem | head
ps -fp <PID>
kill <PID>
kill -9 <PID>
```

---

## 📚 Key Learnings

- Understood the difference between Used, Free, and Available Memory.
- Learned how Linux manages memory using Buffer/Cache.
- Identified memory-intensive processes using `ps`.
- Monitored memory utilization using `free`, `top`, and `vmstat`.
- Safely terminated a high-memory process.
- Verified successful recovery after troubleshooting.

---

## 🎤 Interview Questions

1. What is the difference between Used Memory and Available Memory?
2. What is Buffer/Cache in Linux?
3. What is Swap Memory?
4. Why does Linux use Swap?
5. How do you identify the process consuming the most memory?
6. How do you troubleshoot high memory utilization?
7. What are common production causes of high memory usage?
8. Why is Available Memory more important than Free Memory?
9. Would you immediately kill a high-memory process?
10. How do you verify that memory utilization has returned to normal?
