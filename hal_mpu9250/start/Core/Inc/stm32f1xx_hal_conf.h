/* HAL module selection for the blank Blue Pill start point.
 * Shape follows ST's template: Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_conf_template.h
 * (https://github.com/STMicroelectronics/stm32f1xx-hal-driver, BSD-3-Clause).
 * Only the modules vendored in Drivers/ are enabled. I2C is here for the end point (MPU-9250). */
#ifndef STM32F1xx_HAL_CONF_H
#define STM32F1xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED

#if !defined(HSE_VALUE)
#define HSE_VALUE    8000000U   /* Blue Pill crystal */
#endif
#if !defined(HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT    100U
#endif
#if !defined(HSI_VALUE)
#define HSI_VALUE    8000000U
#endif
#if !defined(LSI_VALUE)
#define LSI_VALUE    40000U
#endif
#if !defined(LSE_VALUE)
#define LSE_VALUE    32768U
#endif
#if !defined(LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT    5000U
#endif

#define VDD_VALUE                    3300U
#define TICK_INT_PRIORITY            0x0FU
#define USE_RTOS                     0U
#define PREFETCH_ENABLE              1U

#define USE_HAL_I2C_REGISTER_CALLBACKS 0U
#define USE_HAL_DMA_REGISTER_CALLBACKS 0U

#define USE_FULL_ASSERT              0U   /* shortcut: no assert_failed; set 1 and add one to debug HAL misuse */

#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32f1xx_hal_rcc.h"
#endif
#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f1xx_hal_gpio.h"
#endif
#ifdef HAL_DMA_MODULE_ENABLED
#include "stm32f1xx_hal_dma.h"
#endif
#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32f1xx_hal_cortex.h"
#endif
#ifdef HAL_EXTI_MODULE_ENABLED
#include "stm32f1xx_hal_exti.h"
#endif
#ifdef HAL_FLASH_MODULE_ENABLED
#include "stm32f1xx_hal_flash.h"
#endif
#ifdef HAL_I2C_MODULE_ENABLED
#include "stm32f1xx_hal_i2c.h"
#endif
#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32f1xx_hal_pwr.h"
#endif

#if (USE_FULL_ASSERT == 1U)
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif

#ifdef __cplusplus
}
#endif
#endif /* STM32F1xx_HAL_CONF_H */
