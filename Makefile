CC := clang
LD := lld

CFLAGS := -ffreestanding -MMD -mno-red-zone -target x86_64-unknown-windows
LDFLAGS := -flavor link -subsystem:efi_application -entry:Main

SRCDIR := bootloader
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.c,%.d,$(SRCS))

default: all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

root/efi/boot/BOOTX64.EFI: $(OBJS)
	$(LD) $(LDFLAGS) $^ -out:$@

-include $(DEPS)

.PHONY: clean all default

all: root/efi/boot/BOOTX64.EFI

run:
	qemu-system-x86_64 -drive if=pflash,format=raw,file=OVMF.fd -drive format=raw,file=fat:rw:root

clean:
	rm -f $(OBJS) root/efi/boot/BOOTX64.EFI $(DEPS)
