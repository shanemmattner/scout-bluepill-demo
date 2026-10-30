# scout-bluepill-demo

STM32F103C8 Blue Pill demo code for the Scout demo videos. No CMSIS, no startup `.s`, no submodules.

## Layout

- One self-contained, buildable folder per step.
- `video_0/`: PC13 blink, 3 files (`main.c`, `link.ld`, `Makefile`). Start of video 1.
- `video_1/`, `video_2/`, ...: each is a full copy of the previous folder plus that video's new code.
- Copy one folder and build it; no folder needs files from another.

## Build

```
cd video_0 && make
```

- `make` builds `build/blink.elf` and `build/blink.bin`; `make clean` removes them.
- Use `arm-none-eabi-gcc` on PATH, or `make TOOLCHAIN=/path/to/arm-none-eabi/bin`.
- The build uses `-O0 -g` so globals stay visible in a debugger.

## Sources and licenses

- https://github.com/cpq/bare-metal-programming-guide at 4f6b45b (MIT): C vector table, reset handler, linker script and Makefile shape.
- https://github.com/andygoulden/baremetal_bluepill at 1c2ad655 (MIT): PC13 blink setup for the F103.
- Local changes: F103 memory map, Cortex-M3 flags, only two vector entries, register addresses from RM0008 instead of headers.

MIT, see `LICENSE`.

Made for Scout demo videos.
