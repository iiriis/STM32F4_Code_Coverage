ENTRY(Reset_Handler);

MEMORY {
  FLASH(rx)  : ORIGIN = 0x08000000, LENGTH = 256k
  SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 64k  /* remaining 64k in a separate address space */
}

_MSP = ORIGIN(SRAM) + LENGTH(SRAM);

_stack_size = 30k;
_heap_size = 2k;

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    /* this will show individual text sections like text.xx */
    /* *(.text) */ 
    *(.text*)
  } > FLASH

  .init : 
  {
    *(.init)
  } > FLASH

  .fini : 
  {
    *(.fini)
  } > FLASH

  .rodata :
  {
    *(.rodata*)
  } > FLASH

  .ARM.exidx :
  {
    *(.ARM.exidx*)
  } > FLASH

  .data : 
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(.data*)
    . = ALIGN(4);
    __data_end__   = .;
  } > SRAM AT> FLASH
  __data_FLASH_start__ = LOADADDR(.data);

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss*)
    __bss_end__ = .;
    . = ALIGN(4);
    _end = .; /* this is provided for the _sbrk to provide end of statically allocated memory so that heap can start */
    end = .;  /* this is provided for the _sbrk to provide end of statically allocated memory so that heap can start */
  } > SRAM

  .heap :
  {
    . = ALIGN(4);
    _heap_start = .;
    . = . + _heap_size;
    . = ALIGN(4);
  } > SRAM  

}

ASSERT(((_heap_start + _heap_size) <= (_MSP - _stack_size)), "Heap and Stack may collide !!!");