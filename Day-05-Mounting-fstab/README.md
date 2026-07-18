
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
