# Adapted from cpq/bare-metal-programming-guide (MIT, commit 4f6b45b), steps/step-0-minimal/Makefile.
# Uses arm-none-eabi-* from PATH, or: make TOOLCHAIN=/path/to/arm-none-eabi/bin
PREFIX  := $(if $(TOOLCHAIN),$(TOOLCHAIN)/)arm-none-eabi-
CFLAGS  := -mcpu=cortex-m3 -mthumb -g -O0 -Wall -Wextra -ffreestanding
LDFLAGS := -Tlink.ld -nostdlib -Wl,-Map=build/demo.map

all: build/demo.bin
	$(PREFIX)size build/demo.elf

build/demo.elf: main.c startup_stm32f103xb.s link.ld
	mkdir -p build
	$(PREFIX)gcc $(CFLAGS) main.c startup_stm32f103xb.s $(LDFLAGS) -o $@

build/demo.bin: build/demo.elf
	$(PREFIX)objcopy -O binary $< $@

clean:
	rm -rf build

.PHONY: all clean
