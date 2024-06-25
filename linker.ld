ENTRY(Reset_Handler);

MEMORY {
  FLASH(rx)  : ORIGIN = 0x08000000, LENGTH = 256k
  SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 64k  /* remaining 64k in a separate address space */
}

_MSP = ORIGIN(SRAM) + LENGTH(SRAM);
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

_Min_Heap_Size = 2k; 
_Min_Stack_Size = 2k;

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    /* this will show individual text sections like text.xx */
    *(.text)
    *(.text*)

    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP(*(.init))
    KEEP(*(.fini))
     _etext = .;
  } > FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

  .ARM.extab   : 
  {
  . = ALIGN(4);
  *(.ARM.extab* .gnu.linkonce.armextab.*)
  . = ALIGN(4);
  } >FLASH

  .ARM : 
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  __data_FLASH_start__ = LOADADDR(.data);
  .data : 
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(.data)
    *(.data*)

    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    __data_end__   = .;
  } > SRAM AT> FLASH
  


  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    . = ALIGN(4);
    _end = .; /* this is provided for the _sbrk to provide end of statically allocated memory so that heap can start */
    end = .;  /* this is provided for the _sbrk to provide end of statically allocated memory so that heap can start */
  } > SRAM

  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >SRAM

  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  
  .ARM.attributes 0 : { *(.ARM.attributes) }

}

ASSERT(((_end + _Min_Heap_Size ) <= (_MSP - _Min_Stack_Size)), "Heap and Stack may collide !!!");