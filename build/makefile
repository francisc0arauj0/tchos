all: tchos.iso

include config.mk

bootloader_build:
	$(MAKE) -C  ../bootloader

kernel_build:
	mkdir -p obj
	$(C_COMPILER) $(C_FLAGS) -c ../kernel/entry/main.c -o obj/main.o
    
	$(LD) $(LD_FLAGS) -o obj/tchos_kernel \
		obj/main.o \

tchos.iso: bootloader_build kernel_build obj/tchos_kernel ../kernel/init/limine.conf
	rm -rf iso_root
	mkdir -p iso_root/boot/limine iso_root/EFI/BOOT
	cp -v obj/tchos_kernel  iso_root/boot/kernel
	cp -v ../kernel/init/limine.conf iso_root/boot/limine/
	cp -v ../bootloader/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v ../bootloader/BOOTX64.EFI iso_root/EFI/BOOT/
	xorriso -as mkisofs $(XORRISO_FLAGS) iso_root -o tchos.iso
	rm -rf iso_root obj

run-x86_64: ovmf-code-x86_64.fd tchos.iso
	qemu-system-x86_64 $(QEMU_FLAGS) \
	-drive if=pflash,unit=0,format=raw,file=ovmf-code-x86_64.fd,readonly=on  \
	-cdrom tchos.iso   
