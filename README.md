# barebonOS

This is a very (very very) bare bones OS which can do nothing except printing to the Screen.
It is mostly based on the awesome Tutorial https://wiki.osdev.org/Bare_Bones. Also this 
repository should serve as a sandbox to try different thing e.g setting up a GDT.

### Building

In case you want to built this project and try it inside a VM, you can do so by simply cloning
the repository and executing make (which may or may not work). Afterward you can use 
`qemu-system-i386 -kernel bare_bones.bin` to run the kernel inside QEMU. 
However you need an `i686-elf` cross-compiler installed to built the project (although currently
the Makefile just checks if there is an executable in your PATH with the name `i686-elf`)
