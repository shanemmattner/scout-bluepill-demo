# scout-bluepill-demo

STM32F103C8 Blue Pill demo code for the Scout demo videos. ST's startup file (`startup_stm32f103xb.s`) for reset and vectors; no CMSIS headers, no submodules.

## Layout

- One self-contained, buildable folder per step.
- `video_0/`: minimal program, a global `counter` incremented in `while(1)`, no LED, 4 files (`main.c`, `startup_stm32f103xb.s`, `link.ld`, `Makefile`). Start of video 1.
- `video_1/`: `video_0` plus `read_counter.py`: flash the binary, read `counter` for a few seconds through the Scout Python API, write `counter.csv`, plot `counter.png`.
- `video_2/`, ...: each is a full copy of the previous folder plus that video's new code.
- Copy one folder and build it; no folder needs files from another.

## Build

```
cd video_0 && make
```

- `make` builds `build/demo.elf` and `build/demo.bin`; `make clean` removes them.
- Use `arm-none-eabi-gcc` on PATH, or `make TOOLCHAIN=/path/to/arm-none-eabi/bin`.
- The build uses `-O0 -g` so globals stay visible in a debugger.

## Run video_1

```
cd video_1 && make
python3 read_counter.py --host <probe name or IP> --seconds 5 --hz 5
```

- Needs `arm-none-eabi-nm` on PATH, `matplotlib`, and the `ohmic` Python binding (Scout `sdk/host/py`, `maturin develop --release`).
- `--host` defaults to env `SCOUT_HOST`. Output: `counter.csv` (`t_s,value`) and `counter.png`.
- The flash algorithm for the F103C8 is `stm32f103c8-flm.json` (copied from Scout `sdk/vscode/flm/`).

## Sources and licenses

- https://github.com/cpq/bare-metal-programming-guide at 4f6b45b (MIT): linker script and Makefile shape, `counter` program.
- https://github.com/STMicroelectronics/cmsis-device-f1 at c8e9a4a4f16b6d2cb2a2083cbe5161025280fb22, `Source/Templates/gcc/startup_stm32f103xb.s` (Apache-2.0; ST copyright header kept in the file): reset handler and vector table.
- Local changes to ST's file (also listed in a comment at its top): removed `bl SystemInit` (no system file, runs on 8 MHz HSI) and `bl __libc_init_array` (`-nostdlib`, no constructors). Nothing else.
- Local changes to the cpq files: F103 memory map, Cortex-M3 flags, `ENTRY(Reset_Handler)` and `.isr_vector` to match ST's file, `counter` loop in place of the original blink.

MIT, see `LICENSE`. `startup_stm32f103xb.s` stays under ST's Apache-2.0 terms (https://github.com/STMicroelectronics/cmsis-device-f1/blob/c8e9a4a4f16b6d2cb2a2083cbe5161025280fb22/LICENSE.md).

Made for Scout demo videos.
