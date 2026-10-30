// Minimal STM32F103C8 (Blue Pill) program: a global counter incremented in while(1).
// Startup and vector table: ST's startup_stm32f103xb.s (see README). No CMSIS headers, no GPIO.
// Read `counter` over SWD to see the core run.
// Adapted from cpq/bare-metal-programming-guide (MIT, commit 4f6b45b,
// https://github.com/cpq/bare-metal-programming-guide, steps/step-0-minimal/main.c)
#include <stdint.h>

volatile uint32_t counter;

int main(void) {
  while (1) {
    counter++;
  }
}
