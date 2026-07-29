Day 7: Systemd & Services

Objective
To learn how to manage services using systemd — the default init system in modern Linux. Includes starting, stopping, enabling, disabling, masking, unmasking, and troubleshooting services.

Commands Used

| Command | Description |
|---------|-------------|
| `sudo systemctl status <service>` | Check service status |
| `sudo systemctl start <service>` | Start a service |
| `sudo systemctl stop <service>` | Stop a service |
| `sudo systemctl restart <service>` | Restart a service |
| `sudo systemctl enable <service>` | Enable service to start at boot |
| `sudo systemctl disable <service>` | Disable service from starting at boot |
| `sudo systemctl is-enabled <service>` | Check if service is enabled |
| `sudo systemctl list-units --type=service` | List all active services |
| `sudo systemctl --failed` | List all failed services |
| `sudo journalctl -u <service>` | View logs for a specific service |
| `sudo journalctl -f` | Follow logs in real-time |
| `sudo systemctl daemon-reload` | Reload systemd configuration |
| `sudo systemctl mask <service>` | Prevent a service from starting (even manually) |
| `sudo systemctl unmask <service>` | Remove a mask from a service |

Screenshots

1. Service Status - `01-service-status.png`
2. Starting and Stopping a Service - `02-start-stop-service.png`
3. Enabling a Service - `03-enable-service.png`
4. Listing Services - `04-list-services.png`
5. Viewing Service Logs - `05-service-logs.png`
6. Custom Service Created - `06-custom-service.png`
7. Custom Service Running - `07-service-running.png`
8. Troubleshooting a Failed Service - `08-troubleshoot-failed.png`
9. Masking and Unmasking a Service - `09-mask-unmask.png`
10. Final Service Status - `10-final-status.png`

Steps Performed

1. Checked Service Status
$ sudo systemctl status sshd

2. Started, Stopped, and Restarted a Service
$ sudo systemctl start sshd
$ sudo systemctl stop sshd
$ sudo systemctl restart sshd

3. Enabled and Disabled a Service
$ sudo systemctl enable sshd
$ sudo systemctl disable sshd
$ sudo systemctl is-enabled sshd

4. Listed All Services
$ sudo systemctl list-units --type=service
$ sudo systemctl --failed

5. Viewed Service Logs
$ sudo journalctl -u sshd -n 20
$ sudo journalctl -u sshd -f

6. Created a Custom Service

Step 1: Created a script
$ sudo vi /usr/local/bin/myservice.sh

#!/bin/bash
while true; do
    echo "$(date) - My custom service is running" >> /var/log/myservice.log
    sleep 60
done

$ sudo chmod +x /usr/local/bin/myservice.sh

Step 2: Created a service unit file
$ sudo vi /etc/systemd/system/myservice.service

[Unit]
Description=My Custom Service
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/myservice.sh
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target

Step 3: Reloaded and started the service
$ sudo systemctl daemon-reload
$ sudo systemctl start myservice
$ sudo systemctl enable myservice

7. Troubleshot a Failed Service

- Introduced an error in the script (missing #!/bin/bash)
- Service entered a failed state
- Used journalctl to diagnose the issue
- Fixed the script and restarted the service

$ sudo journalctl -u myservice -n 20
$ sudo systemctl restart myservice
$ sudo systemctl status myservice

8. Mask and Unmask a Service

- Disabled the service first
- Removed the service file
- Masked and unmasked the service

$ sudo systemctl disable myservice
$ sudo rm /etc/systemd/system/myservice.service
$ sudo systemctl daemon-reload
$ sudo systemctl mask myservice
$ sudo systemctl status myservice
$ sudo systemctl start myservice   # This should fail
$ sudo systemctl unmask myservice
$ sudo systemctl enable myservice
$ sudo systemctl start myservice
$ sudo systemctl status myservice

Observations

Disable vs Mask:
- Disable: Removes the symlink from multi-user.target.wants/. Service won't start at boot, but can be started manually.
- Mask: Links the service to /dev/null. Service cannot be started at all, even manually.

Custom Service:
- Service unit files go in /etc/systemd/system/.
- Always run systemctl daemon-reload after creating or modifying a unit file.
- Use Restart=always to ensure the service restarts if it crashes.

Key Takeaways
- systemctl is the primary tool for managing services.
- journalctl is used to view service logs.
- Disable = "Do not start at boot." Mask = "Cannot start at all."
- Always use systemctl daemon-reload after creating or modifying a service file.

Challenges Faced

1. Missing Shebang (#!/bin/bash)
- Issue: The service script failed because #!/bin/bash was missing at the top.
- Fix: Added #!/bin/bash to the script and made it executable (chmod +x).

2. Mask Conflict
- Issue: The service file already existed in /etc/systemd/system/, so masking failed.
- Fix: Disabled the service and removed the file before masking.

Final Status
✅ Day 7 Lab Complete
- Service status checked.
- Services started, stopped, restarted, enabled, and disabled.
- Custom service created and managed.
- Service logs viewed and followed.
- Failed service troubleshot and fixed.
- Service masked and unmasked.
