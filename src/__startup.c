#include <main.h>
#include <string.h>
#include <__startup.h>

extern uint32_t _MSP;  // Defined in link.ld

#if (__VFP_FP__)
__always_inline void enableFPU();
__always_inline void enableFPU()
{

  asm("LDR.W R0, =0xE000ED88");
  asm("LDR R1, [R0]");
  asm("ORR R1, R1, #(0xF << 20)");
  asm("STR R1, [R0]");
  asm("DSB");
  asm("ISB");
}
#endif

void Reset_Handler(void) {

    extern uint8_t __data_start__, __data_end__, __data_FLASH_start__, __bss_start__, __bss_end__;
    /* Copy the .data from flash to RAM */
    memcpy(&__data_start__, &__data_FLASH_start__, (uint32_t)(&__data_end__ - &__data_start__));
    /* Fill the .bss section in RAM with all Zeros */
    memset(&__bss_start__, 0, (uint32_t)(&__bss_end__ - &__bss_start__));

    __libc_init_array();
    
    enableFPU();

    main();
    for(;;);
}

__attribute__((section(".isr_vector"))) volatile uint32_t vector_table [] = {
    (uint32_t)&_MSP,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
};

void Default_Handler(void)
{
  while(1);
}
