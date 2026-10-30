// Minimal STM32F103C8 (Blue Pill) program: a global counter incremented in while(1).
// No CMSIS, no startup .s, no GPIO. Read `counter` over SWD to see the core run.
// Adapted from cpq/bare-metal-programming-guide (MIT, commit 4f6b45b,
// https://github.com/cpq/bare-metal-programming-guide, steps/step-0-minimal/main.c)
#include <stdint.h>

volatile uint32_t counter;

int main(void) {
  while (1) {
    counter++;
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
