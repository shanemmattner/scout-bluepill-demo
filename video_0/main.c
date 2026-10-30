// Minimal STM32F103C8 (Blue Pill) blink: PC13 LED, no CMSIS, no startup .s.
// Adapted from cpq/bare-metal-programming-guide (MIT, commit 4f6b45b,
// https://github.com/cpq/bare-metal-programming-guide, steps/step-0-minimal/main.c)
// and andygoulden/baremetal_bluepill (MIT, commit 1c2ad655,
// https://github.com/andygoulden/baremetal_bluepill, src/main.c: PC13 setup).
// Register addresses: RM0008 (STM32F101/102/103 reference manual).
#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)  // bit 4 = GPIOC clock
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)  // pins 8..15, 4 bits each
#define GPIOC_BSRR  (*(volatile uint32_t *)0x40011010)  // set: bit n, reset: bit n+16

int main(void) {
  RCC_APB2ENR |= 1u << 4;                            // enable GPIOC clock
  GPIOC_CRH = (GPIOC_CRH & ~(0xFu << 20)) | (0x2u << 20);  // PC13: output 2 MHz, push-pull

  for (;;) {
    GPIOC_BSRR = 1u << (13 + 16);                    // PC13 low: LED on (active low)
    for (volatile uint32_t i = 0; i < 500000; i++) (void) 0;
    GPIOC_BSRR = 1u << 13;                           // PC13 high: LED off
    for (volatile uint32_t i = 0; i < 500000; i++) (void) 0;
  }
}

// Reset handler: zero .bss, copy .data from flash to RAM, then call main().
__attribute__((naked, noreturn)) void reset(void) {
  extern uint32_t _sbss, _ebss, _sdata, _edata, _sidata;
  for (uint32_t *p = &_sbss; p < &_ebss; p++) *p = 0;
  for (uint32_t *d = &_sdata, *s = &_sidata; d < &_edata;) *d++ = *s++;
  main();
  for (;;) (void) 0;
}

// Vector table at 0x08000000: entry 0 = initial stack pointer, entry 1 = reset.
extern void _estack(void);  // defined in link.ld
__attribute__((section(".vectors"))) void (*const vectors[2])(void) = {_estack, reset};
