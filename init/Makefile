ifeq ($(PLEASE_PANIC),1)
    CC_FLAG_PLEASE_PANIC := -DPLEASE_PANIC
endif

vmlinuz:
	cp /boot/vmlinuz-$(shell uname -r) vmlinuz

initrd.img:
	cp /boot/initrd.img-$(shell uname -r) initrd.img

.PHONY: inspect-initramfs
inspect-initramfs: RAMDISK=initrd.img
inspect-initramfs: $(RAMDISK)
	mkdir -p mount/unpacked-$(RAMDISK)
	unmkinitramfs $(RAMDISK) mount/unpacked-$(RAMDISK)

init: init.c
	gcc $(CC_FLAG_PLEASE_PANIC) --static init.c -o init

rootfs.img: init
	dd if=/dev/zero of=tmp-rootfs.img bs=1M count=100
	mkfs -t ext4 tmp-rootfs.img
	mkdir -p mount/rootfs
	mount tmp-rootfs.img mount/rootfs
	mkdir mount/rootfs/sbin
	cp init mount/rootfs/sbin
	mkdir mount/rootfs/proc
	mkdir mount/rootfs/sys
	mkdir mount/rootfs/dev
#	umount mount/rootfs
	mv tmp-rootfs.img rootfs.img

.PHONY: prepare
prepare: vmlinuz initrd.img rootfs.img

.PHONY: run-with-initramfs
run-with-initramfs: vmlinuz initrd.img rootfs.img
##	Default: hang on kernel panic
#	qemu-system-x86_64 -m 2G -kernel vmlinuz -initrd initrd.img -hda rootfs.img -append "root=/dev/sda console=ttyS0" -nographic
##	Reboot on kernel panic
#	qemu-system-x86_64 -m 2G -kernel vmlinuz -initrd initrd.img -hda rootfs.img -append "root=/dev/sda console=ttyS0 panic=-1" -nographic
##	Stop qemu on kernel panic
#	qemu-system-x86_64 -m 2G -kernel vmlinuz -initrd initrd.img -hda rootfs.img -append "root=/dev/sda console=ttyS0 panic=-1" -nographic --no-reboot

.PHONY: run
run: vmlinuz rootfs.img
	qemu-system-x86_64 -m 2G -kernel vmlinuz -hda rootfs.img -append "root=/dev/sda console=ttyS0 panic=-1" -nographic --no-reboot

.PHONY: clean
clean:
	rm -f vmlinuz
	rm -f initrd.img
	rm -f rootfs.img
	rm -f init
