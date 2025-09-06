C_COMPILER = gcc
C_FLAGS = -mcmodel=large -ffreestanding -O2 -Wall -Werror -Wextra

LD = ld
LD_FLAGS = -nostdlib -T ../tchux/linker.ld

XORRISO_FLAGS = -R -r -J -hfsplus -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label
QEMU_FLAGS = -M q35 -m 2G -monitor stdio -d int -M smm=off
