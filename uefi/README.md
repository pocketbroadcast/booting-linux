## Prerequisites

### Firmware

Install OVMF which is an open implementation of UEFI firmware

```
sudo apt-get install ovmf
whereis ovmf
```

If the path does not match adapt qemu invocation in `Makefile` (parameter: `bios`)

### Development Dependencies

Install gnu-efi libraries for more convenient UEFI programming experience.
```
sudo apt-get install gnu-efi
```

## Sample Applications

To run the sample applications just type

```
sudo make run TARGET=hello
```

or

```
sudo make run TARGET=read
```


## Sources

https://wiki.osdev.org/GNU-EFI

https://www.rodsbooks.com/efi-programming/hello.html

https://packages.ubuntu.com/focal/amd64/gnu-efi/filelist