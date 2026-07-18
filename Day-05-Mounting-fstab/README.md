
---

## Troubleshooting Simulated

### 1. Broken fstab Entry
- Added a dummy entry to fstab to simulate a mount failure.
- Recovered by commenting out the bad entry and running `mount -a`.

### 2. Emergency Mode Recovery
- Rebooted the system with a broken fstab entry.
- System dropped into **Emergency Mode**.
- Remounted root as read-write using `mount -o remount,rw /`.
- Fixed the fstab file by commenting out the bad entry.
- Verified the fix with `mount -a` and rebooted.

---

## Screenshots

### 1. UUID of LVM Volume
![UUID](screenshots/01-uuid-blkid.png)

### 2. fstab Entry
![fstab Entry](screenshots/02-fstab-entry.png)

### 3. Mount Verification
![Mount Verify](screenshots/03-mount-verify.png)

### 4. Troubleshooting Error
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
- Emergency mode simulated and recovered.
- All screenshots documented.

---

## Next Steps
- Move to **Day 6: SELinux Basics**
