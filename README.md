# barebonOS

This is a very (very very) bare bones OS which can do nothing except printing to the Screen.
It is mostly based on the awesome Tutorial https://wiki.osdev.org/Bare_Bones. Also this 
repository should serve as a sandbox to try different thing e.g setting up a GDT.

### Building

In case you want to built this project and try it inside a VM, you can do so by simply cloning
the repository and executing make (which may or may not work).
Afterwards you can build build a `.iso` file which you can use to boot the OS with qemu.
To build the do the following.

1. Create the following file structure inside the repository

```
isodir
|-- boot
    |-- grub
    |   |--- grub.cfg
```

2. Put the following into the `grub.cfg` file

```
menuentry "bare_bones" {
    multiboot2 /boot/bare_bones.bin
    boot
}
```

3. The move the binary into `isodir/boot`
4. From the repository execute `grub2-mkrescur -o bare_bones.iso isodir`
5. Boot the OS inside QEMU with `qemu-system-i386 -cdrom bare_bones.iso`

However you need an `i686-elf` cross-compiler installed to built the project (although currently
the Makefile just checks if there is an executable in your PATH with the name `i686-elf-gcc`)
