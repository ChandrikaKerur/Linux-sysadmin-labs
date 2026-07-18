# Day 5: Mounting & fstab (Persistent Storage)

## Objective
To learn how to configure permanent storage mounts using `/etc/fstab` and recover from mount failures — including emergency mode.

---

## Commands Used

| Command | Description |
|---------|-------------|
| `df -h` | Check disk usage |
| `lsblk -f` | List block devices with filesystem info |
| `sudo blkid /dev/vg_data/lv_data` | Get UUID of a device |
| `sudo vi /etc/fstab` | Edit the fstab file |
| `sudo mount -a` | Mount all entries in fstab |
| `sudo umount /mnt/lv_data` | Unmount a filesystem |
| `mount -o remount,rw /` | Remount root as read-write in emergency mode |
| `systemctl get-default` | Check current default target |
| `reboot` | Reboot the system |

---

## fstab Entry Added

---

## Troubleshooting Simulated

### 1. Unmount / Remount Test
- Practiced unmounting (`umount /mnt/lv_data`) and verifying with `df -h`.
- Tested remounting using `mount -a` to ensure the filesystem came back.

### 2. Broken fstab Entry
- Added a dummy entry to fstab to simulate a mount failure.
- Recovered by commenting out the bad entry and running `mount -a`.

### 3. Emergency Mode Recovery (Advanced Challenge)
- Rebooted the system with a broken fstab entry.
- System dropped into **Emergency Mode**.
- Confirmed the system was in emergency mode using `systemctl get-default`.
- Remounted root as read-write using `mount -o remount,rw /`.
- Fixed the fstab file by commenting out the bad entry.
- Verified the fix with `mount -a` and rebooted successfully.

---

## Screenshots

### 1. UUID of LVM Volume
![UUID](screenshots/01-uuid-blkid.png)

### 2. fstab Entry
![fstab Entry](screenshots/02-fstab-entry.png)

### 3. Mount Verification (mount -a & df -h)
![Mount Verify](screenshots/03-mount-verify.png)

### 4. Troubleshooting Error (Bad fstab)
![Troubleshoot Error](screenshots/04-troubleshoot-error.png)

### 5. Emergency Mode
![Emergency Mode](screenshots/05-emergency-mode.png)

### 6. Remount Root as Read-Write
![Remount RW](screenshots/06-remount-rw.png)

### 7. fstab Fixed
![fstab Fixed](screenshots/07-fstab-fixed.png)

### 8. Verification After Reboot
![Post Recovery Verify](screenshots/08-post-recovery-verify.png)

---

## Key Takeaways
- Always use **UUID** instead of device names for persistence.
- Test `fstab` with `mount -a` before rebooting.
- Back up `/etc/fstab` before making changes.
- In emergency mode, remount root as read-write to fix fstab.
- `mount -o remount,rw /` is your "get out of jail free" card in emergency mode.
- Always verify unmounts with `df -h` or `mount | grep lv_data`.

---

## Challenges Faced

### 1. Mount Point Typo
- **Issue:** Initially typed `/mmt/lv_data` instead of `/mnt/lv_data`.
- **Fix:** Corrected the mount point path in fstab.

### 2. Emergency Mode Recovery
- **Issue:** System dropped into emergency mode after adding a fake fstab entry.
- **Fix:** Remounted root as read-write, commented out the bad entry, and rebooted.

---

## Final Status
✅ **Day 5 Lab Complete**
- fstab entry added and tested.
- Persistent mount configured.
- Unmount and remount verified.
- Emergency mode simulated and recovered.
- All screenshots documented.

---

## Next Steps
- Move to **Day 6: SELinux Basics**
