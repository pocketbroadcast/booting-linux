BUSYBOX_VERSION=1.36.1
#BUSYBOX_BUILDDIR=busybox-builddir

vmlinuz:
	cp /boot/vmlinuz-$(shell uname -r) vmlinuz

busybox-$(BUSYBOX_VERSION).tar.bz2:
	wget https://busybox.net/downloads/busybox-$(BUSYBOX_VERSION).tar.bz2
	
busybox-${BUSYBOX_VERSION}: busybox-$(BUSYBOX_VERSION).tar.bz2
	tar -xf busybox-$(BUSYBOX_VERSION).tar.bz2
	
busybox-builddir-${BUSYBOX_VERSION}/_install: busybox-${BUSYBOX_VERSION}
	mkdir busybox-builddir-${BUSYBOX_VERSION}
	cd busybox-${BUSYBOX_VERSION} && $(MAKE) O=../busybox-builddir-${BUSYBOX_VERSION} defconfig
	
	cd busybox-builddir-${BUSYBOX_VERSION} && sed "/# CONFIG_STATIC/s/.*/CONFIG_STATIC=y/" -i .config && $(MAKE) -j8
	cd busybox-builddir-${BUSYBOX_VERSION} && $(MAKE) install

.PHONY: busybox
busybox: busybox-builddir-${BUSYBOX_VERSION}/_install
	@echo "Build busybox"

rootfs.img: busybox-builddir-${BUSYBOX_VERSION}/_install rcS
	dd if=/dev/zero of=tmp-rootfs.img bs=1M count=100
	mkfs -t ext4 tmp-rootfs.img
	mkdir -p mount/rootfs
	mount tmp-rootfs.img mount/rootfs
	cp -a busybox-builddir-${BUSYBOX_VERSION}/_install/* mount/rootfs
	mkdir mount/rootfs/proc
	mkdir mount/rootfs/sys
	mkdir mount/rootfs/dev
	mkdir -p mount/rootfs/etc/init.d/
	cp rcS mount/rootfs/etc/init.d/
	umount mount/rootfs
	mv tmp-rootfs.img rootfs.img

.PHONY: run
run: vmlinuz rootfs.img
	qemu-system-x86_64 -m 2G -kernel vmlinuz -hda rootfs.img -append "root=/dev/sda console=ttyS0 panic=-1" -nographic --no-reboot

.PHONY: clean
clean:
	rm -f vmlinuz
	rm -f rootfs.img
	rm -rf mount
	rm -rf busybox-builddir-${BUSYBOX_VERSION}
	rm -rf busybox-$(BUSYBOX_VERSION)
	rm -rf busybox-$(BUSYBOX_VERSION).tar.bz2


.PHONY: inspect-rootfs
inspect-rootfs: rootfs.img
	mkdir -p mount/rootfs
	mount rootfs.img mount/rootfs