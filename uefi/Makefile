ARCH            = $(shell uname -m | sed s,i[3456789]86,ia32,)

HELLO_OBJS      = hello.o
TARGETS         = hello.efi read.efi

EFIINC          = /usr/include/efi
EFIINCS         = -I$(EFIINC) -I$(EFIINC)/$(ARCH) -I$(EFIINC)/protocol
LIB             = /usr/lib
EFILIB          = /usr/lib
EFI_CRT_OBJS    = $(EFILIB)/crt0-efi-$(ARCH).o
EFI_LDS         = $(EFILIB)/elf_$(ARCH)_efi.lds

CFLAGS          = $(EFIINCS) -fno-stack-protector -fpic \
		  -fshort-wchar -mno-red-zone -Wall 
ifeq ($(ARCH),x86_64)
  CFLAGS += -DEFI_FUNCTION_WRAPPER
endif

LDFLAGS         = -nostdlib -znocombreloc -T $(EFI_LDS) -shared \
		  -Bsymbolic -L $(EFILIB) -L $(LIB) $(EFI_CRT_OBJS) 

all: $(TARGETS)

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@
#	gcc -I/usr/include/efi/ -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c $^ -o $@

hello.so: hello.o
	ld $(LDFLAGS) $^ -o $@ -lefi -lgnuefi
	
read.so: read.o
	ld $(LDFLAGS) $^ -o $@ -lefi -lgnuefi

%.efi: %.so
	objcopy -j .text -j .sdata -j .data -j .dynamic \
		-j .dynsym  -j .rel -j .rela -j .reloc \
		--target=efi-app-$(ARCH) $^ $@

%.img: %.efi
	dd if=/dev/zero of=tmp-disk.img bs=1M count=100
	mkfs -t vfat tmp-disk.img
	mkdir -p mount/disk
	mount tmp-disk.img mount/disk/
	mkdir -p mount/disk/EFI/BOOT
	cp $< mount/disk/EFI/BOOT/BOOTX64.efi
	cp DATA.TXT mount/disk/
	umount mount/disk
	mv tmp-disk.img $@

.PHONY: run
run: TARGET=hello
run: $(TARGET).img 
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -hda $(TARGET).img -nographic
	
.PHONY: clean
clean:
	rm -rf *.so *.o *.img *.efi mount/