all: tchux.iso

include config.mk

tchboot_build:
	$(MAKE) -C  ../tchboot

tchux_build:
	mkdir -p obj
	$(C_COMPILER) $(C_FLAGS) -c ../tchux/entry/main.c -o obj/main.o
    
	$(LD) $(LD_FLAGS) -o obj/tchux_kernel \
		obj/main.o \

tchux.iso: tchboot_build tchux_build obj/tchux_kernel ../tchux/init/limine.conf
	rm -rf iso_root
	mkdir -p iso_root/boot/limine iso_root/EFI/BOOT
	cp -v obj/tchux_kernel  iso_root/boot/kernel
	cp -v ../tchux/init/limine.conf iso_root/boot/limine/
	cp -v ../tchboot/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v ../tchboot/BOOTX64.EFI iso_root/EFI/BOOT/
	xorriso -as mkisofs $(XORRISO_FLAGS) iso_root -o tchux.iso
	rm -rf iso_root obj

run-x86_64: ovmf-code-x86_64.fd tchux.iso
	qemu-system-x86_64 $(QEMU_FLAGS) \
	-drive if=pflash,unit=0,format=raw,file=ovmf-code-x86_64.fd,readonly=on  \
	-cdrom tchux.iso   
