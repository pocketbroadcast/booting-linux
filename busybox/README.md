# Busybox

In this section we build minimal Linux based on a default configured busybox. To run it in qemu invoke:

> Note: Depending on your system and user you have to prepend `sudo`

```
make run
```


Additionally, you can review the contents of the rootfs:
```
make inspect-rootfs
ls -la mount/rootfs
```