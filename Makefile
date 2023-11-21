CC := clang
LD := lld

CFLAGS := -ffreestanding -MMD -mno-red-zone -target x86_64-unknown-windows
BOOTLOADER_LDFLAGS := -flavor link -subsystem:efi_application -entry:Main
KERNEL_LDFLAGS := -flavor link -subsystem:native -entry:Main

BOOTLOADER_SOURCES := $(wildcard bootloader/*.c)
BOOTLOADER_OBJECTS := $(patsubst %.c,%.o,$(BOOTLOADER_SOURCES))
BOOTLOADER_DEPENDS := $(patsubst %.c,%.d,$(BOOTLOADER_SOURCES))

KERNEL_SOURCES := $(wildcard kernel/*.c)
KERNEL_OBJECTS := $(patsubst %.c,%.o,$(KERNEL_SOURCES))
KERNEL_DEPENDS := $(patsubst %.c,%.d,$(KERNEL_SOURCES))

default: all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

root/efi/boot/BOOTX64.EFI: $(BOOTLOADER_OBJECTS)
	$(LD) $(BOOTLOADER_LDFLAGS) $^ -out:$@

root/efi/boot/ntoskrnl.exe: $(KERNEL_OBJECTS)
	$(LD) $(KERNEL_LDFLAGS) $^ -out:$@

-include $(BOOTLOADER_DEPENDS)
-include $(KERNEL_DEPENDS)

.PHONY: clean all default

all: root/efi/boot/BOOTX64.EFI root/efi/boot/ntoskrnl.exe

run:
	qemu-system-x86_64 -drive if=pflash,format=raw,file=OVMF.fd -drive format=raw,file=fat:rw:root

run-kvm:
	qemu-system-x86_64 -drive if=pflash,format=raw,file=OVMF.fd -drive format=raw,file=fat:rw:root --enable-kvm

clean:
	rm -f $(KERNEL_OBJECTS) root/efi/boot/BOOTX64.EFI $(KERNEL_DEPENDS) $(BOOTLOADER_OBJECTS) root/efi/boot/ntoskrnl.exe $(BOOTLOADER_DEPENDS)
