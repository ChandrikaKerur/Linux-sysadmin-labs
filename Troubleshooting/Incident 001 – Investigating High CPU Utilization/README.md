# 🚨 Incident 001 – High CPU Utilization Troubleshooting

## 📖 Overview

This lab demonstrates a structured approach to troubleshooting high CPU utilization on a Red Hat Enterprise Linux (RHEL) server.

The objective is to identify the root cause of high CPU usage, resolve the issue, and verify that the server has returned to a healthy state.

---

# 🖥️ Lab Environment

| Component | Details |
|-----------|---------|
| Operating System | Rocky Linux 9 |
| Tool Used | stress |
| Purpose | Simulate high CPU utilization |

---

# 🎯 Scenario

A Linux production server became slow and users experienced delayed response while accessing applications.

As a Linux System Administrator, the objective is to:

- Verify the issue
- Identify the process consuming CPU
- Investigate system performance
- Resolve the issue
- Confirm the server is healthy

---

# Step 1 – Verify System Load

## Command

```bash
uptime
```

## Purpose

Check the system load average.

## Observation

The load average was significantly higher than normal, indicating the CPU was handling more work than expected.

### Screenshot

![Uptime](screenshots/02-uptime-before.png)

<img width="602" height="56" alt="uptime after" src="https://github.com/user-attachments/assets/473845bb-55c4-476f-8c67-15115108c0cb" />


---

# Step 2 – Identify High CPU Process

## Command

```bash
top
```

## Purpose

Monitor CPU utilization in real time.

## Observation

The `stress` process was consuming approximately 98% CPU, indicating it was responsible for the increased CPU utilization.

### Screenshot

![Top Output](screenshots/03-top-high-cpu.png)

<img width="878" height="351" alt="CPU after increasing the load" src="https://github.com/user-attachments/assets/83072bf0-2df4-482d-8157-7e47842800ac" />


---

# Step 3 – Identify the Process

## Command

```bash
ps -eo pid,user,%cpu,%mem,cmd --sort=-%cpu | head
```

## Purpose

Display processes sorted by CPU utilization.

## Observation

The `stress` process appeared at the top of the list with the highest CPU usage.

### Screenshot

![PS Output](screenshots/04-ps-output.png)

<img width="897" height="461" alt="load increase" src="https://github.com/user-attachments/assets/cbe9e731-2e1a-492e-94a3-87ff47d3f459" />


---

# Step 4 – Analyze CPU Statistics

## Command

```bash
vmstat 1 5
```

## Purpose

Monitor CPU and system performance.

## Observation

- High User CPU utilization
- Low Idle CPU
- Increased Running Processes

### Screenshot

![VMStat](screenshots/05-vmstat.png)

<img width="897" height="461" alt="load increase" src="https://github.com/user-attachments/assets/8ca7d812-0b39-4994-83ad-c6b96766de6f" />


---

# Step 5 – Verify Memory Usage

## Command

```bash
free -h
```

## Purpose

Confirm whether the issue is CPU-related or caused by memory pressure.

## Observation

Memory usage remained normal and swap usage was zero, confirming the issue was CPU-related.

### Screenshot

![Memory](screenshots/06-free-memory.png)

<img width="748" height="73" alt="memory looks good " src="https://github.com/user-attachments/assets/ec67080d-fd10-44e3-b315-a77ae44f9a1c" />


---

# Step 6 – Resolve the Issue

## Identify the Process

```bash
ps -ef | grep stress
```

## Terminate the Process

```bash
kill <PID>
```

If the process does not terminate gracefully:

```bash
kill -9 <PID>
```

> In production environments, `kill -9` should only be used when graceful termination fails.

### Screenshot

![Kill Process](screenshots/07-kill-process.png)

<img width="827" height="240" alt="Kill the process gracefully " src="https://github.com/user-attachments/assets/ecc3e755-88ef-4ead-8317-027a49fe33f2" />

---

# Step 7 – Verify Resolution

## Command

```bash
top
```

## Observation

CPU utilization returned to normal and no high CPU processes were observed.

### Screenshot

![CPU Normal](screenshots/08-top-after.png)

<img width="833" height="572" alt="Processes are killed" src="https://github.com/user-attachments/assets/07b86b75-6136-40ec-8dde-04b665440b72" />

---

## Verify Load Average

```bash
uptime
```

The load average gradually decreased after terminating the CPU-intensive process.

### Screenshot

![Uptime After](screenshots/09-uptime-after.png)

<img width="553" height="47" alt="load average is back to normal" src="https://github.com/user-attachments/assets/633ebfe5-6882-41be-8f23-254fe6fa239e" />


---

# 🔍 Root Cause Analysis

The `stress` utility intentionally generated CPU-intensive worker threads to simulate high CPU utilization. This increased CPU usage and the system load average.

---

# ✅ Resolution

- Verified system health
- Identified the high CPU process using `top`
- Confirmed the offending process using `ps`
- Analyzed CPU statistics using `vmstat`
- Terminated the process
- Verified CPU utilization returned to normal

---

# 🚀 Prevention

In production environments, high CPU utilization can be caused by:

- Infinite loops in applications
- High web traffic
- Database-intensive queries
- Scheduled jobs
- Runaway scripts
- Malware or cryptomining processes

Recommended preventive measures:

- Configure CPU monitoring
- Set alerts using monitoring tools
- Review application performance regularly
- Monitor long-running processes
- Perform capacity planning

---

# 🛠️ Commands Used

```bash
hostnamectl
cat /etc/redhat-release
lscpu
uptime
top
stress --cpu 4 --timeout 300
ps -eo pid,user,%cpu,%mem,cmd --sort=-%cpu | head
vmstat 1 5
free -h
ps -ef | grep stress
kill <PID>
kill -9 <PID>
```

---

# 📚 Key Learnings

- Understood the difference between CPU utilization and load average.
- Used `top` to identify CPU-intensive processes.
- Used `ps` to investigate running processes.
- Used `vmstat` to analyze CPU performance.
- Verified memory usage using `free -h`.
- Learned how to safely terminate resource-intensive processes.
- Validated system health after resolving the issue.

---

# ⭐ Interview Questions

1. What is Load Average?
2. What is the difference between CPU Utilization and Load Average?
3. How do you troubleshoot a Linux server with high CPU usage?
4. What does `us`, `sy`, `id`, and `wa` mean in `top`?
5. What is the difference between `kill` and `kill -9`?
6. What are common production causes of high CPU utilization?
