# Adapted from cpq/bare-metal-programming-guide (MIT, commit 4f6b45b), steps/step-0-minimal/Makefile.
# Uses arm-none-eabi-* from PATH, or: make TOOLCHAIN=/path/to/arm-none-eabi/bin
PREFIX  := $(if $(TOOLCHAIN),$(TOOLCHAIN)/)arm-none-eabi-
CFLAGS  := -mcpu=cortex-m3 -mthumb -g -O0 -Wall -Wextra -ffreestanding
LDFLAGS := -Tlink.ld -nostdlib -Wl,-Map=build/blink.map

all: build/blink.bin
	$(PREFIX)size build/blink.elf

build/blink.elf: main.c link.ld
	mkdir -p build
	$(PREFIX)gcc $(CFLAGS) main.c $(LDFLAGS) -o $@

build/blink.bin: build/blink.elf
	$(PREFIX)objcopy -O binary $< $@

clean:
	rm -rf build

.PHONY: all clean
