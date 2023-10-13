# Init process

After the kernel booted and mounted the rootfs it tries to run the init program (PID=1) from one of
the predefined locations in the kernel. First is `/sbin/init`.

```
[    2.601082] Run /sbin/init as init process
[    2.611864] Run /etc/init as init process
[    2.613596] Run /bin/init as init process
[    2.614119] Run /bin/sh as init process
```

On a ubunt system this file points to `systemd` which takes over all system management tasks and runs until the system is
shut down.

```
$ ls -la /sbin/init 
lrwxrwxrwx 1 root root 20 Mär 27  2023 /sbin/init -> /lib/systemd/systemd
```

The code in this repository is used to demonstrate the kernels behaviour to load the init process.

> Note: Depending on your system and user you have to prepend `sudo`

To just boot the init process run:
```
make run
```

If you want to boot with an initramfs run:
```
make run-with-initramfs
```

Additionally, you can review the contents of the initrd:
```
make inspect-initramfs
```

or to inspect another initramfs image:
```
make inspect-initramfs RAMDISK=some-other-initrd.img
```

## Sources:

https://unix.stackexchange.com/a/136280/265125
https://unix.stackexchange.com/questions/136278/what-are-the-minimum-root-filesystem-applications-that-are-required-to-fully-boo/136280#136280

https://wiki.gentoo.org/wiki/Custom_Initramfs#:~:text=An%20initramfs%20contains%20at%20least,that%20are%20required%20by%20%2Finit.