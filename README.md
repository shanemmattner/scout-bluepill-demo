# scout-bluepill-demo

The most minimal STM32F103C8 Blue Pill blink: `main.c`, `link.ld`, `Makefile`.
No CMSIS, no startup `.s`, no submodules. Start point for the Scout demo videos.

- `main.c`: vector table, reset handler, RCC/GPIOC registers, PC13 blink loop.
- `link.ld`: flash at 0x08000000 (128 KB), RAM at 0x20000000 (20 KB).
- `Makefile`: `make` builds `build/blink.elf` and `build/blink.bin`; `make clean`.

Build with `arm-none-eabi-gcc` on PATH, or `make TOOLCHAIN=/path/to/arm-none-eabi/bin`.
The build uses `-O0 -g` so globals stay visible in a debugger.

Tags: `videoN-start`, `videoN-step-M`, `videoN-end`. Start of video 1: `video1-start`.

## Sources and licenses

- https://github.com/cpq/bare-metal-programming-guide at 4f6b45b (MIT): C vector table, reset handler, linker script and Makefile shape.
- https://github.com/andygoulden/baremetal_bluepill at 1c2ad655 (MIT): PC13 blink setup for the F103.
- Local changes: F103 memory map, Cortex-M3 flags, only two vector entries, register addresses from RM0008 instead of headers.

MIT, see `LICENSE`.
