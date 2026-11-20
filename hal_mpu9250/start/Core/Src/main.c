/* Blank Blue Pill (STM32F103C8) with ST's HAL: 72 MHz from the 8 MHz crystal, PC13 LED toggles every 500 ms.
 * Start point of the Scout HAL video; the end point adds the MPU-9250 over I2C.
 * Clock setup follows ST's CubeMX output for F103 (HSE, PLL x9, APB1 /2, flash latency 2).
 * Sources: https://github.com/STMicroelectronics/stm32f1xx-hal-driver (BSD-3-Clause). */
#include "stm32f1xx_hal.h"

/* Watch this in Scout Memory View or the live plot: it grows by 1 per LED toggle. */
volatile uint32_t blink_count;

static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc.HSEState = RCC_HSE_ON;
    osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    osc.PLL.PLLState = RCC_PLL_ON;
    osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    osc.PLL.PLLMUL = RCC_PLL_MUL9;                 /* 8 MHz x 9 = 72 MHz */
    if (HAL_RCC_OscConfig(&osc) != HAL_OK) {
        for (;;) {}                                /* no crystal: park here */
    }

    RCC_ClkInitTypeDef clk = {0};
    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV2;            /* APB1 max 36 MHz */
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2) != HAL_OK) {
        for (;;) {}
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef led = {0};
    led.Pin = GPIO_PIN_13;
    led.Mode = GPIO_MODE_OUTPUT_PP;
    led.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &led);

    for (;;) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);    /* Blue Pill LED is active low */
        blink_count++;
        HAL_Delay(500);
    }
}
