Linux Boot Failure Simulation & GRUB Recovery

Incident 004 • Rocky Linux 10.2 • Hands-on Recovery Lab

Lab Objective

Simulate a Linux boot failure by deliberately removing /boot/grub2/grub.cfg, observe the GRUB failure, recover the installed Rocky Linux system from Rescue Mode, reinstall GRUB, regenerate grub.cfg, and verify a successful boot.

What This Lab Demonstrates

GRUB bootloader vs. grub.cfg

How a missing grub.cfg affects boot

How to use Rocky Linux Rescue Mode

How /mnt/sysroot and chroot are used during recovery

How to identify the correct boot disk

How to recognize a BIOS boot partition

How to reinstall GRUB and regenerate grub.cfg


Step 1 — Take a VM Snapshot

Before making any destructive change, take a VMware snapshot. This gives you a safe rollback point.

Step 2 — Verify and Back Up grub.cfg

First confirm that the GRUB configuration exists, then save a copy under /root. Keeping the backup outside /boot/grub2 makes the recovery copy separate from the file being intentionally modified.

ls -lh /boot/grub2/grub.cfg
cp /boot/grub2/grub.cfg /root/grub.cfg.bkp
ls -lh /root/grub.cfg.bkp

<img width="847" height="150" alt="image" src="https://github.com/user-attachments/assets/62af3124-5740-4f3e-955b-79ef1508b1e7" />

Backup of the original grub.cfg before simulating the failure.

Step 3 — Delete grub.cfg to Simulate the Failure

Remove the GRUB configuration file. This is the deliberate failure condition for the lab.

rm -rf /boot/grub2/grub.cfg
ls -lh /boot/grub2/grub.cfg

<img width="655" height="141" alt="image" src="https://github.com/user-attachments/assets/43dda4ad-b571-4802-a0c7-922383027491" />


grub.cfg has been removed and the verification shows it is missing.

Step 4 — Power Off the VM

Shut down the VM so it can be restarted from the Rocky Linux installation ISO.

init 0

Step 5 — Boot from the Rocky Linux ISO

In VMware Workstation, connect the Rocky Linux ISO at power-on and make the optical drive the boot device. This gives us access to the rescue environment.

VM Settings → CD/DVD → Connect at power on → boot from CD/DVD

<img width="810" height="470" alt="image" src="https://github.com/user-attachments/assets/5607cfa5-9e30-440c-ac32-c1857769f76f" />




Rocky Linux boot menu. Troubleshooting is available for recovery.

Step 6 — Observe the GRUB Failure

Because grub.cfg is missing, GRUB itself starts but cannot load the normal boot configuration. The system stops at the GRUB command prompt.


<img width="826" height="521" alt="image" src="https://github.com/user-attachments/assets/8b83adff-4f76-4b7e-baed-1d826597f1ca" />


GRUB prompt shown after the missing grub.cfg failure.

Step 7 — Select Troubleshooting → Rescue

From the Rocky Linux boot menu, select Troubleshooting and then the Rescue option. Rescue Mode is designed to repair an installed Linux system that cannot boot normally.

Troubleshooting → Rescue a Rocky Linux Minimal system

Step 8 — Select Continue

Choose option 1, Continue. The rescue environment searches for the installed Linux system and mounts it under /mnt/sysroot.

1

<img width="1195" height="665" alt="image" src="https://github.com/user-attachments/assets/87ad7519-513b-4327-808f-d55f8e3bad69" />



Rescue environment asking whether to mount the installed system under /mnt/sysroot.

Step 9 — Enter the Installed System

Use chroot so that commands are executed as if /mnt/sysroot were the root directory of the installed Rocky Linux system.

chroot /mnt/sysroot
<img width="776" height="307" alt="image" src="https://github.com/user-attachments/assets/83e512f3-273a-412c-a9e3-145f176d1877" />



Rescue shell after entering the installed system and running lsblk.

Step 10 — Identify the Correct Disk

Use lsblk to identify the disk containing the operating system. In this lab, the OS disk is /dev/sda. Do not blindly use a device name from another system.

lsblk

<img width="776" height="307" alt="image" src="https://github.com/user-attachments/assets/0e072fe5-4f0a-4e1d-beac-7f6950258324" />




lsblk output showing /dev/sda, /boot, LVM root, swap, and the additional data disk.

Step 11 — Check the Partition Layout

Inspect the partition table before installing GRUB. The disk uses GPT and contains a 1 MB BIOS boot partition, confirming that the installed GRUB is the BIOS/i386-pc type.

fdisk -l /dev/sda

<img width="1206" height="330" alt="image" src="https://github.com/user-attachments/assets/984a1825-bb40-494e-852a-c9616068e18e" />




fdisk output showing GPT and the BIOS boot partition on /dev/sda1.

Step 12 — Reinstall GRUB

Install the GRUB bootloader to the correct boot disk. The successful output confirms that the installation completed without errors.

grub2-install /dev/sda

<img width="726" height="165" alt="image" src="https://github.com/user-attachments/assets/29a9cdf9-aab8-4445-97b3-5c156b67d247" />




Successful grub2-install for /dev/sda.

Step 13 — Regenerate grub.cfg

Recreate the missing GRUB configuration file. This is separate from reinstalling the GRUB bootloader.

grub2-mkconfig -o /boot/grub2/grub.cfg

<img width="1087" height="271" alt="image" src="https://github.com/user-attachments/assets/aa430550-3d93-4dc1-aa28-0f2958b174a0" />



grub2-mkconfig successfully generates a new grub.cfg.

Step 14 — Verify the New grub.cfg

Confirm that the configuration file has been recreated in /boot/grub2.

ls -lh /boot/grub2/grub.cfg


<img width="776" height="107" alt="image" src="https://github.com/user-attachments/assets/273d595c-d2a6-4fd3-8a74-44e7514efaa9" />


Verification that the recreated grub.cfg now exists.

Step 15 — Exit the Rescue Environment

Exit the chroot/rescue environment. Return control to the normal system and prepare to reboot.

exit

Step 16 — Disconnect the Installation ISO

In VMware Workstation, disconnect the Rocky Linux ISO so that the VM boots from its hard disk rather than returning to the installer.

VM Settings → CD/DVD → uncheck Connect at power on

Step 17 — Reboot the VM

Restart the VM. GRUB should now find the regenerated configuration and present/load the normal Rocky Linux boot entry.

reboot

Step 18 — Verify the Successful Boot

After login, verify the running kernel and confirm that the normal root shell is available. In this lab, the system successfully returned to Rocky Linux 10.2.

uname -r
<img width="702" height="160" alt="image" src="https://github.com/user-attachments/assets/84909aa1-8155-48ca-84b2-8922be9c80dc" />




Successful Rocky Linux boot and root login.


Why the Recovery Worked

The failure was limited to the GRUB configuration file. The bootloader was repaired with grub2-install, and the missing configuration was recreated with grub2-mkconfig. Once both were available and the ISO was disconnected, the VM could boot normally.

Important Concepts to Remember

GRUB: The bootloader responsible for starting the Linux boot process.

grub.cfg: The GRUB configuration containing boot entries, kernel/initramfs locations and boot parameters.

/mnt/sysroot: The mount point used by Rescue Mode for the installed Linux system.

chroot /mnt/sysroot: Changes the apparent root directory so recovery commands operate on the installed OS.

grub2-install: Installs the GRUB bootloader to the selected disk.

grub2-mkconfig: Generates a new GRUB configuration file.

BIOS boot partition: A small partition used by BIOS-mode GRUB on a GPT-partitioned disk.

GRUB Recovery Flow

grub.cfg deleted
      ↓
GRUB boot failure / grub> prompt
      ↓
Boot Rocky Linux Rescue Mode
      ↓
chroot /mnt/sysroot
      ↓
Identify /dev/sda
      ↓
grub2-install /dev/sda
      ↓
grub2-mkconfig -o /boot/grub2/grub.cfg
      ↓
Reboot from hard disk
      ↓
Rocky Linux boots successfully

Interview Answer

If grub.cfg is missing, GRUB may start but cannot load the normal boot configuration and can stop at the grub> prompt. I would boot into Rescue Mode, mount the installed system, chroot into /mnt/sysroot, identify the correct boot disk and firmware mode, reinstall GRUB if required, regenerate /boot/grub2/grub.cfg, and reboot to verify recovery.

Final Status

INCIDENT 004 — RESOLVED

Root cause: /boot/grub2/grub.cfg was intentionally deleted during the lab.

Recovery: Rescue Mode → chroot → identify boot disk → reinstall GRUB → regenerate grub.cfg → reboot.
