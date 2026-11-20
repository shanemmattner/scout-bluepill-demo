# Third-party code in `hal_mpu9250/start/`

Every file below is a byte-identical copy of the upstream file at the pinned commit, except where "Local changes" says otherwise. Nothing is fetched at build time.

## ST HAL driver

- URL: https://github.com/STMicroelectronics/stm32f1xx-hal-driver (tag v1.1.10)
- Commit: `bd368aa335c529641d2e567574885e02deacc64a`
- License: BSD-3-Clause, copied to `start/Drivers/STM32F1xx_HAL_Driver/LICENSE.md`
- Files, under `start/Drivers/STM32F1xx_HAL_Driver/`:
  - `Src/` and `Inc/`: `stm32f1xx_hal`, `_hal_rcc`, `_hal_rcc_ex`, `_hal_gpio`, `_hal_gpio_ex`, `_hal_cortex`, `_hal_dma`, `_hal_exti`, `_hal_flash`, `_hal_flash_ex`, `_hal_pwr`, `_hal_i2c` (each a `.c` and a `.h`).
  - `Inc/`: `stm32f1xx_hal_def.h`, `stm32f1xx_hal_dma_ex.h`, `Legacy/stm32_hal_legacy.h`.

## ST CMSIS device files

- URL: https://github.com/STMicroelectronics/cmsis-device-f1 (tag v4.3.5)
- Commit: `c8e9a4a4f16b6d2cb2a2083cbe5161025280fb22`
- License: Apache-2.0, copied to `start/Drivers/CMSIS/Device/ST/STM32F1xx/LICENSE.md`
- Files:
  - `Include/stm32f103xb.h`, `Include/stm32f1xx.h`, `Include/system_stm32f1xx.h` -> `start/Drivers/CMSIS/Device/ST/STM32F1xx/Include/`
  - `Source/Templates/system_stm32f1xx.c` -> `start/Core/Src/system_stm32f1xx.c`
  - `Source/Templates/gcc/startup_stm32f103xb.s` -> `start/startup_stm32f103xb.s`
  - `Source/Templates/gcc/linker/STM32F103XB_FLASH.ld` -> `start/STM32F103XB_FLASH.ld`

## Arm CMSIS core headers

- URL: https://github.com/ARM-software/CMSIS_5 (`CMSIS/Core/Include`)
- Commit: `55b19837f5703e418ca37894d5745b1dc05e4c91`
- License: Apache-2.0, copied to `start/Drivers/CMSIS/LICENSE.txt`
- Files, under `start/Drivers/CMSIS/Include/`: `cmsis_compiler.h`, `cmsis_gcc.h`, `cmsis_version.h`, `core_cm3.h`, `mpu_armv7.h`.

## STM32F103 SVD (register file for the Scout Peripherals view)

- URL: https://github.com/modm-io/cmsis-svd-stm32/blob/1761a45d754ac51a1156e17f75932c40dd95e645/stm32f1/STM32F103.svd
- Commit: `1761a45d754ac51a1156e17f75932c40dd95e645`
- License: Apache-2.0, copied to `start/.ohmic/STM32F103.svd.LICENSE`. The SVD has no license header of its own.
- File: `start/.ohmic/STM32F103.svd`, SHA-256 `ff632bd0d75d0bc807d787967cdf62512d6438be53d6a77d2d78ab8ba2110015`.

## Scout flash algorithm

- `start/.ohmic/stm32f103c8.json`: Scout's layout for the F103C8, generated from the installed CMSIS device pack with pyOCD (https://github.com/pyocd/pyOCD/blob/main/pyocd/target/pack/flash_algo.py). Same file as `video_1/stm32f103c8-flm.json`.

## Local changes

- None to any copied file.
- Files written here (MIT, repo `LICENSE`): `Core/Src/main.c`, `Core/Src/stm32f1xx_it.c`, `Core/Inc/stm32f1xx_hal_conf.h` (module list in the shape of ST's `stm32f1xx_hal_conf_template.h`), `Makefile`, and the `.vscode/` and `.ohmic/ohmic.toml` config.
- No code from third-party templates (for example shadowzhz/STM32-Template) is used.
