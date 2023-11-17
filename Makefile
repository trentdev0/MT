CC := clang
LD := lld

CFLAGS := -ffreestanding -MMD -mno-red-zone -target x86_64-unknown-windows
LDFLAGS := -flavor link -subsystem:efi_application -entry:Main

SRCDIR := bootloader
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.cpp,%.d,$(SRCS))

default: all

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

BOOTX64.EFI: $(OBJS)
	$(LD) $(LDFLAGS) $^ -out:$@

-include $(DEPS)

.PHONY: clean all default

all: BOOTX64.EFI

clean:
	rm -f $(OBJS) BOOTX64.EFI $(DEPS)
