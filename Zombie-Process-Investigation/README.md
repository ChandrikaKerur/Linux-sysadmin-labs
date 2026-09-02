# 🧟 Zombie Process Investigation (Linux)

A hands-on Linux project demonstrating how a **Zombie Process** is created, identified, investigated, and removed.

This project explains the lifecycle of a zombie process using a simple C program and common Linux administration commands.

---

## 📌 Objective

The objectives of this project are to:

- Create a Zombie Process
- Understand why Zombie processes exist
- Identify Zombie processes using Linux commands
- Investigate the parent-child relationship
- Remove the Zombie process correctly
- Learn common interview questions related to Zombie processes

---

## 🛠️ Technologies Used

- Linux (RHEL 9)
- C Programming
- GCC Compiler
- Process Management Commands

---
```

---

# Step 1 - Create the Zombie Process

### Source Code

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("Parent PID = %d\n", getpid());
        sleep(300);
    }
    else
    {
        printf("Child exiting...\n");
        exit(0);
    }

    return 0;
}
```

---

## Compile

```bash
gcc zombie.c -o zombie
```

---

## Execute

```bash
./zombie
```

Example Output

```
Parent PID = 1958
Child exiting...
```

<img width="928" height="119" alt="image" src="https://github.com/user-attachments/assets/9f0db519-1c64-4205-9e40-bde75c80a516" />

---

# Step 2 - What Happens Internally?

```
fork()

        Parent
           |
      fork()
      /     \
 Parent     Child
             |
           exit()
             |
        Zombie Process
```

### Explanation

- Parent process continues executing.
- Child process exits immediately.
- Parent **does not call `wait()`**.
- Kernel keeps the child's PID and exit status.
- Child enters **Zombie (Z)** state.

---

# Step 3 - View Process Tree

Command

```bash
pstree -p
```

Example

```
bash(1842)
   └── zombie(1958)
          └── zombie(1959)


<img width="895" height="565" alt="image" src="https://github.com/user-attachments/assets/9e798965-2e75-4ec6-acb1-344ed7b363c0" />


```

### Observation

- `1958` → Parent Process
- `1959` → Child Process (Zombie)

---

# Step 4 - Verify Zombie Process

Display all processes

```bash
ps -e -o pid,ppid,state,cmd
```

or

```bash
ps -el
```

or

```bash
ps aux | grep defunct
```

Expected Output

```
PID    PPID   S   CMD

1959   1958   Z   [zombie] <defunct>

<img width="751" height="84" alt="image" src="https://github.com/user-attachments/assets/240b42ad-3f77-4e50-a4f6-98185d1d2ca7" />

```

### Observation

State **Z** indicates a Zombie process.

---

# Step 5 - Inspect Parent Process

Command

```bash
ps -fp 1958
```

Example

```
UID      PID   PPID   CMD

root    1958   1842   ./zombie
```



### Observation

The parent process is still running because it is sleeping for 300 seconds.

---

# Step 6 - Why Doesn't `kill -9` Work?

Command

```bash
kill -9 1959
```

Nothing happens.

### Why?

A Zombie process is already terminated.

Only a small **process table entry** remains to store:

- PID
- Exit status
- Process accounting information

There is no running process to terminate.

---

# Step 7 - Remove the Zombie

Find the Parent PID

```bash
ps -fp 1958
```

Terminate the Parent

```bash
kill 1958
```

The kernel reassigns the Zombie process to **systemd (PID 1)**, which reaps it.

---

# Step 8 - Verify Removal

Command

```bash
ps aux | grep defunct
```

No Zombie process should be displayed.

<img width="940" height="67" alt="image" src="https://github.com/user-attachments/assets/68feea07-cc3c-4fd2-81d3-1a9792a846bb" />

```

---

# Process Lifecycle

```
fork()

      Parent
         |
         |
     Child
         |
      exit()
         |
    Zombie Process
         |
     wait()/Parent exits
         |
   Kernel removes entry
```

---

# Commands Used

```bash
gcc zombie.c -o zombie

./zombie

pstree -p

ps -e -o pid,ppid,state,cmd

ps -el

ps aux | grep defunct

ps -fp <PID>

kill <ParentPID>
```

---

# Key Learnings

- Understood the purpose of `fork()`
- Learned how Zombie processes are created
- Investigated parent-child relationships
- Used `pstree` to visualize process hierarchy
- Used `ps` to inspect process states
- Learned why `kill -9` cannot remove a Zombie process
- Learned how Zombie processes are cleaned up

---

# Interview Questions

### What is a Zombie process?

A terminated child process whose parent has not yet collected its exit status using `wait()` or `waitpid()`.

---

### Why does Linux create Zombie processes?

To preserve the child's exit status until the parent retrieves it.

---

### Does a Zombie process consume CPU?

No.

---

### Does a Zombie process consume memory?

Only a very small process table entry remains.

---

### Why doesn't `kill -9` remove a Zombie?

Because the process has already terminated.

---

### How do you remove a Zombie process?

- Parent calls `wait()` / `waitpid()`, or
- Terminate the parent process.

---

### Which commands help identify Zombie processes?

```bash
ps -el

ps aux | grep defunct

pstree -p
```

---

# Conclusion

This project demonstrates the complete lifecycle of a Zombie process—from creation to investigation and cleanup—using standard Linux administration tools. It reinforces practical process management skills that are useful for Linux System Administration and technical interviews.
