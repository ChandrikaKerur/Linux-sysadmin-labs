# Day 2: Sudo Access Management

## Objective
To learn how to grant specific, limited sudo access to users and groups.

## Sudo Rule Created
**File:** `/etc/sudoers.d/developer`

**Content:**
```bash
# Allow the developer user to restart the web server
developer ALL=(ALL) /usr/bin/systemctl restart httpd
