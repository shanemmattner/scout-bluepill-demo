/* Linker script for STM32F103C8 (Blue Pill): flash at 0x08000000, 20 KB RAM at 0x20000000.
   Adapted from cpq/bare-metal-programming-guide (MIT, commit 4f6b45b,
   https://github.com/cpq/bare-metal-programming-guide, steps/step-0-minimal/link.ld).
   Changes: F103 memory sizes (the board reads 128 KB flash); entry and section
   names match ST's startup_stm32f103xb.s (.isr_vector, Reset_Handler, _sidata, ...). */
ENTRY(Reset_Handler)
MEMORY {
  flash (rx)  : ORIGIN = 0x08000000, LENGTH = 128k
  sram  (rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}
_estack = ORIGIN(sram) + LENGTH(sram);   /* initial stack pointer: 0x20005000 */

SECTIONS {
  .isr_vector : { KEEP(*(.isr_vector)) } > flash
  .text    : { *(.text*) }         > flash
  .rodata  : { *(.rodata*) }       > flash
  .data : {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > sram AT > flash
  _sidata = LOADADDR(.data);
  .bss : {
    _sbss = .;
    *(.bss*) *(COMMON)
    _ebss = .;
  } > sram
}
