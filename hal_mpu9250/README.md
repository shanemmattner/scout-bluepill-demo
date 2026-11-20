# hal_mpu9250

Two points of the Scout HAL video series on a Blue Pill (STM32F103C8). Each point is a full, buildable folder.

- `start/`: blank project with ST's HAL. 72 MHz from the 8 MHz crystal, PC13 LED toggles every 500 ms, global `volatile uint32_t blink_count` to watch in Memory View.
- `end/` (planned, clip 2): `start/` plus an I2C read of the MPU-9250 `WHO_AM_I` register, expected `0x71`.

## Build

```
cd hal_mpu9250/start && make
```

- Output: `build/blink.elf`, `blink.bin`, `blink.hex`. `make clean` removes `build/`.
- Use `arm-none-eabi-gcc` with newlib on PATH, or `make TOOLCHAIN=/path/to/arm-none-eabi/bin`. Built with Arm GNU 15.3.rel1.
- The build uses `-O0 -g` so globals stay visible in the debugger.

## Open in VS Code with Scout

1. Install the Scout extension and open `hal_mpu9250/start`.
2. Build with the default build task (`Ctrl/Cmd+Shift+B`, runs `make`).
3. Pick your probe in the Scout view, then Connect. `.ohmic/probes.toml` is not in the repo: Scout writes it for your probe.
4. Flash Image, then F5 (`.vscode/launch.json`, `type: "scout"`).
5. Memory View: watch `blink_count`, or GPIOC ODR bit 13 (`0x4001100C`) for the LED.

Chip, ELF, flash algorithm and register file are in `.ohmic/ohmic.toml`. Sources and licenses: [`THIRD_PARTY.md`](THIRD_PARTY.md).
