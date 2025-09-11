CC = gcc
C_FLAGS = -mcmodel=large -ffreestanding -O2 -Wall -Werror -Wextra -I../kernel/include

LD = ld
LD_FLAGS = -nostdlib -T ../kernel/linker.ld

QEMU = qemu-system-x86_64
QEMU_FLAGS = -M q35 -m 2G -monitor stdio -d int -M smm=off

XORRISO_FLAGS = -R -r -J -hfsplus -apm-block-size 2048 --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label

KERNEL_SRC = ../kernel
KERNEL_OBJ = obj/tchos_kernel

BOOTLOADER_SRC = ../bootloader

ISO = tchos.iso

all: $(ISO)

LIMINE_BUILD:
	$(MAKE) -C $(BOOTLOADER_SRC)

KERNEL_BUILD:
	mkdir obj/
	$(CC) $(C_FLAGS) -c $(KERNEL_SRC)/entry/main.c -o obj/main.o
	$(CC) $(C_FLAGS) -c $(KERNEL_SRC)/cpu/gdt.c -o obj/gdt.o
	$(CC) $(C_FLAGS) -c $(KERNEL_SRC)/cpu/sse.c -o obj/sse.o

	$(LD) $(LD_FLAGS) -o $(KERNEL_OBJ) \
		obj/main.o \
		obj/gdt.o \
		obj/sse.o

$(ISO): LIMINE_BUILD KERNEL_BUILD limine.conf
	rm -rf iso_root
	mkdir -p iso_root/EFI/BOOT
	cp -v $(KERNEL_OBJ) iso_root/
	cp -v limine.conf iso_root/
	cp -v $(BOOTLOADER_SRC)/limine-uefi-cd.bin iso_root/
	cp -v $(BOOTLOADER_SRC)/BOOTX64.EFI iso_root/EFI/BOOT
	xorriso -as mkisofs $(XORRISO_FLAGS) iso_root -o $(ISO)
	rm -rf iso_root

run: OVMF.fd
	$(QEMU) $(QEMU_FLAGS) -drive if=pflash,unit=0,format=raw,file=OVMF.fd,readonly=on -cdrom $(ISO)

clean:
	rm -rf obj
	rm $(ISO)
