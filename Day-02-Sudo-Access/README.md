# Day 2: Sudo Access Management

## Objective
To learn how to grant specific, limited sudo access to users and groups.

## Sudo Rule Created
**File:** `/etc/sudoers.d/developer`

**Content:**
```bash
# Allow the developer user to restart the web server
developer ALL=(ALL) /usr/bin/systemctl restart httpd

This rule gives the developer user permission to run only the systemctl restart httpd command as root.

## Screenshots
![Sudo Rule Test](https://raw.githubusercontent.com/ChandrikaKerur/Linux-sysadmin-labs/main/Day-02-Sudo-Access/sudo-rule-test.png)

## Key Takeaways
visudo is the only safe way to edit sudoers files.
Always use the full path to the command.
Least privilege is a core security principle.

## Challenges Faced
1. Syntax Error While Editing Sudoers File
Issue: When I first created the sudoers file, I accidentally typed extra text (bash and ^) inside the file. This caused a syntax error when I tried to save it.
Error Message: /etc/sudoers.d/developer:1:5: syntax error
How I Fixed It: I used visudo which caught the error and prevented me from saving a broken file. I exited without saving (:q!), reopened the file, and typed only the correct rule. This taught me that visudo is a safety net—it protects your system from breaking due to syntax errors.

2. Service Not Found (httpd)
Issue: When I tested the sudo rule with sudo systemctl restart httpd, I got an error: Failed to restart httpd.service: Unit httpd.service not found.
How I Fixed It: I realized the web server (httpd) was not installed on my system. I installed it using sudo dnf install httpd -y and then started the service. After that, the sudo rule worked perfectly.
Lesson Learned: sudo controls who can run a command, but it doesn't guarantee the command itself will succeed. You still need to ensure the service or file exists.
