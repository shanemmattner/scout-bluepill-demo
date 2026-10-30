# scout-bluepill-demo

STM32F103C8 Blue Pill demo code for the Scout demo videos. No CMSIS, no startup `.s`, no submodules.

## Layout

- One self-contained, buildable folder per step.
- `video_0/`: minimal program, a global `counter` incremented in `while(1)`, no LED, 3 files (`main.c`, `link.ld`, `Makefile`). Start of video 1.
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

- https://github.com/cpq/bare-metal-programming-guide at 4f6b45b (MIT): C vector table, reset handler, linker script and Makefile shape.
- Local changes: F103 memory map, Cortex-M3 flags, only two vector entries, `counter` loop in place of the original blink.

MIT, see `LICENSE`.

Made for Scout demo videos.
