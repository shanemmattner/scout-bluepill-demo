# Blank Blue Pill HAL blink. Uses arm-none-eabi-* from PATH, or: make TOOLCHAIN=/path/to/arm-none-eabi/bin
# Same TOOLCHAIN override as ../../video_0/Makefile. Newlib (nano) comes with the Arm GNU toolchain.
PREFIX  := $(if $(TOOLCHAIN),$(TOOLCHAIN)/)arm-none-eabi-
BUILD   := build
HALDIR  := Drivers/STM32F1xx_HAL_Driver
CMSIS   := Drivers/CMSIS

SRCS := $(wildcard Core/Src/*.c) $(wildcard $(HALDIR)/Src/*.c)
OBJS := $(patsubst %.c,$(BUILD)/%.o,$(SRCS)) $(BUILD)/startup_stm32f103xb.o

INCS    := -ICore/Inc -I$(HALDIR)/Inc -I$(HALDIR)/Inc/Legacy -I$(CMSIS)/Device/ST/STM32F1xx/Include -I$(CMSIS)/Include
CPU     := -mcpu=cortex-m3 -mthumb
CFLAGS  := $(CPU) -DSTM32F103xB -DUSE_HAL_DRIVER -g -O0 -Wall -ffunction-sections -fdata-sections $(INCS)
ASFLAGS := $(CPU) -g -x assembler-with-cpp
LDFLAGS := $(CPU) -TSTM32F103XB_FLASH.ld -specs=nano.specs -Wl,--gc-sections -Wl,--no-warn-rwx-segments -Wl,-Map=$(BUILD)/blink.map

all: $(BUILD)/blink.bin $(BUILD)/blink.hex
	$(PREFIX)size $(BUILD)/blink.elf

$(BUILD)/blink.elf: $(OBJS) STM32F103XB_FLASH.ld
	$(PREFIX)gcc $(OBJS) $(LDFLAGS) -o $@

$(BUILD)/%.bin: $(BUILD)/%.elf
	$(PREFIX)objcopy -O binary $< $@

$(BUILD)/%.hex: $(BUILD)/%.elf
	$(PREFIX)objcopy -O ihex $< $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(PREFIX)gcc $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.s
	@mkdir -p $(dir $@)
	$(PREFIX)gcc $(ASFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean
