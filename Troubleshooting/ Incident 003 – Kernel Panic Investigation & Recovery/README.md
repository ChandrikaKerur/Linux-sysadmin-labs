Kernel Panic Investigation & Recovery
Corrupted initramfs | Rocky Linux 10.2 | Kernel 6.12.0-211.28.1.el10_2.x86_64
1. Incident Overview
A Rocky Linux server failed to boot after the initramfs image was intentionally corrupted. The server displayed a kernel panic because the kernel could not mount the root filesystem.
Kernel panic - not syncing: VFS: Unable to mount root fs
Objective: identify the cause, recover the server, restore boot, and validate the system.
2. Boot Process
BIOS/UEFI
    ↓
GRUB
    ↓
Kernel
    ↓
initramfs
    ↓
Root filesystem
    ↓
systemd
    ↓
Services
initramfs is an early userspace environment used during boot to load required drivers/storage components and help locate and mount the real root filesystem. In this incident, GRUB and the kernel loaded, but boot failed when the root filesystem could not be accessed.
3. Verify the System
Check /etc/fstab
cat /etc/fstab
Verify UUIDs
blkid
The UUIDs were checked against /etc/fstab. No obvious UUID mismatch was found.
<img width="940" height="424" alt="image" src="https://github.com/user-attachments/assets/b3ceff16-cdbb-45a9-84c2-42922002bd2f" />

4. Check Kernel and initramfs
uname -r
ls -lh /boot
Active kernel: 6.12.0-211.28.1.el10_2.x86_64. The /boot directory contained the kernel and its initramfs.
<img width="940" height="359" alt="image" src="https://github.com/user-attachments/assets/fe84307f-0dbc-423e-9927-2adbe4b9e38e" />

5. Create a Backup
cp /boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img \
   /boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.lab-backup.img
ls -lh /boot/initramfs*
A known-good backup was created before intentionally damaging the image. This provided a recovery point.
<img width="940" height="428" alt="image" src="https://github.com/user-attachments/assets/959df6d5-300e-4c9b-9fb4-e313114b9686" />

6. Verify initramfs Before Corruption
lsinitrd /boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img | head -30
lsinitrd successfully displayed the image and dracut modules, confirming the initramfs was readable.
<img width="940" height="445" alt="image" src="https://github.com/user-attachments/assets/4f9d6e12-e7e7-4cba-b693-454b2a239a9d" />


7. Simulate Failure — Corrupt initramfs
dd if=/dev/zero \
of=/boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img \
bs=1K count=100 conv=notrunc
This overwrote the beginning of the initramfs with zero bytes, damaging its archive structure. This command was used only for the lab simulation and is destructive.
<img width="940" height="100" alt="image" src="https://github.com/user-attachments/assets/3d809926-4539-4ba5-8c70-40d40937fceb" />


8. Confirm Corruption
lsinitrd /boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img
File format not recognized
cpio: premature end of archive
The errors confirmed that the initramfs was corrupted.
<img width="940" height="330" alt="image" src="https://github.com/user-attachments/assets/3266d820-2149-463c-83b8-70de36f1d603" />


9. Reboot and Observe Panic
reboot
Kernel panic - not syncing: VFS: Unable to mount root fs
The root logical volume shown in the panic was /dev/mapper/rlm-root.
<img width="940" height="545" alt="image" src="https://github.com/user-attachments/assets/9900095a-28e3-4927-9833-63d1ce8b83c7" />


10. Analyze the Panic
An 'Unable to mount root fs' error can have several causes: invalid fstab, incorrect UUID, missing storage driver, LVM/storage problems, filesystem corruption, or damaged initramfs.
In this lab, fstab and blkid had already been checked, and the initramfs had been intentionally corrupted. Therefore the root cause was a corrupted initramfs.
Kernel panic
    ↓
VFS unable to mount root filesystem
    ↓
/dev/mapper/rlm-root
    ↓
Root cause: corrupted initramfs
11. Boot into Rescue Mode
Troubleshooting
→ Rescue a Rocky Linux Minimal system
→ Continue
The Rocky Linux installation ISO was used because the installed OS could not boot.
<img width="940" height="523" alt="image" src="https://github.com/user-attachments/assets/5c76ec4c-f7fd-40cd-b483-53847d268767" />


12. Access Installed System
ls -lh /mnt/sysroot
The rescue environment mounted the installed system under /mnt/sysroot.
<img width="940" height="686" alt="image" src="https://github.com/user-attachments/assets/c1924d9f-4295-4840-b4a7-dd4bacebe7a1" />


13. Find initramfs and Backup
ls -lh /mnt/sysroot/boot/initramfs*
Both the damaged initramfs and the .lab-backup.img were visible.
<img width="940" height="364" alt="image" src="https://github.com/user-attachments/assets/3856424e-9343-4b72-b0d3-17e1a4351b9c" />


14. Restore initramfs
cp /mnt/sysroot/boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.lab-backup.img \
   /mnt/sysroot/boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img
lsinitrd /mnt/sysroot/boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img | head
The known-good backup was copied over the corrupted image. The restored image could be read successfully.

<img width="940" height="481" alt="image" src="https://github.com/user-attachments/assets/f2b768d3-4dfb-4125-94d8-c4f9ad7b6735" />


15. Exit Rescue and Reboot
exit
reboot
Remove/eject the installation ISO if necessary so the VM boots from its normal disk.

16. Verify Recovery
uname -r
systemctl --failed
The server successfully booted with the expected kernel. systemctl --failed reported 0 loaded units listed, confirming no failed systemd units.
<img width="940" height="353" alt="image" src="https://github.com/user-attachments/assets/7bae9e34-255c-4568-9f9f-cf67911d1cf0" />


17. Verify initramfs After Recovery
lsinitrd /boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img | head
The image was recognized again and its dracut metadata/modules were displayed. This confirmed the initramfs was healthy.

<img width="1217" height="252" alt="image" src="https://github.com/user-attachments/assets/102c266a-a6bb-4cc1-be6e-936718385126" />

18. Root Cause
The server failed to boot because the initramfs image for the active kernel was corrupted. The corruption prevented the early boot environment from accessing /dev/mapper/rlm-root, resulting in a VFS root-filesystem mount failure and kernel panic.

19. Recovery Flow
Normal Boot
     ↓
Kernel Panic
     ↓
Identify root filesystem failure
     ↓
Boot Rocky Linux Rescue Environment
     ↓
Mount installed system
     ↓
Locate corrupted initramfs
     ↓
Restore known-good backup
     ↓
Reboot
     ↓
Verify kernel + systemd
     ↓
Server recovered

20. Alternative Recovery — Rebuild initramfs
dracut --force
dracut --force --kver 6.12.0-211.28.1.el10_2.x86_64
lsinitrd /boot/initramfs-6.12.0-211.28.1.el10_2.x86_64.img
Rebuilding with dracut is another common recovery method when the underlying kernel and configuration are healthy. In this lab, a known-good backup was restored to demonstrate backup-based recovery.

21. What I Learned
•	A kernel panic is an operating-system-level failure, unlike a normal application crash.
•	initramfs is critical during early boot because it provides the environment/components needed to locate and mount the root filesystem.
•	Create a recovery point before making risky boot changes.
•	'Unable to mount root fs' does not automatically mean the filesystem itself is corrupt; investigate fstab, UUIDs, LVM, storage, initramfs, kernel, and filesystem health.
•	Rescue mode allows repair of an installed system even when the normal OS cannot boot.

22. Commands — Quick Reference
cat /etc/fstab
blkid
uname -r
ls -lh /boot
lsinitrd /boot/initramfs-*.img

# Backup
cp /boot/initramfs-<kernel>.img /boot/initramfs-<kernel>.lab-backup.img

# Lab-only corruption simulation
dd if=/dev/zero of=/boot/initramfs-<kernel>.img bs=1K count=100 conv=notrunc

# Rescue
Troubleshooting → Rescue a Rocky Linux system → Continue

# Check installed system
ls -lh /mnt/sysroot/boot/initramfs*

# Restore
cp /mnt/sysroot/boot/initramfs-<kernel>.lab-backup.img /mnt/sysroot/boot/initramfs-<kernel>.img

# Validate
lsinitrd /mnt/sysroot/boot/initramfs-<kernel>.img

# After reboot
uname -r
systemctl --failed
lsinitrd /boot/initramfs-<kernel>.img


Final Incident Summary

A simulated production-style kernel panic was investigated by following the Linux boot path, validating filesystem configuration, identifying a corrupted initramfs, entering the Rocky Linux rescue environment, restoring a known-good initramfs backup, rebooting, and validating the recovered system. The lab demonstrates a practical and repeatable approach to diagnosing boot failures caused by initramfs corruption.
