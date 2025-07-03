#!/bin/bash
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/bbOS.kernel isodir/boot/bbOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "bbOS" {
	multiboot2 /boot/bbOS.kernel
}
EOF
grub2-mkrescue -o bbOS.iso isodir

