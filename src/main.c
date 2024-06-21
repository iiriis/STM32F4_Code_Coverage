
#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "utils.h"
#include "string.h"

void delay(uint64_t del);

char arr[5] = {1,2,3,4,5};

#if (__VFP_FP__)
__always_inline void enableFPU();
__always_inline void enableFPU(){

  asm("LDR.W R0, =0xE000ED88");
  asm("LDR R1, [R0]");
  asm("ORR R1, R1, #(0xF << 20)");
  asm("STR R1, [R0]");
  asm("DSB");
  asm("ISB");
}
#endif

int main(void) {

  enableFPU();
  GPIO_Init();

  for(;;)
  {
      memcpy(arr, "Hello", 5);
     
      volatile float f = 1.005; /* check for disassembly that contains vadd vdiv etc*/
      for(int i=0;i<10;i++)
        f =  i / f;
      
      /* blink led on pin C13 */
      GPIOC_ODR = _setBit(GPIOC_ODR, 13);
      // *(volatile uint32_t*)(PERI_BB_ADDRESS_FROM_ABS_ADDRESS(GPIOC_BASE_ADDR + 0x14, 13)) = 1; //using bit addressble locations
      delay(1000000);
      GPIOC_ODR = _clrBit(GPIOC_ODR, 13);
      // *(volatile uint32_t*)(PERI_BB_ADDRESS_FROM_ABS_ADDRESS(GPIOC_BASE_ADDR + 0x14, 13)) = 0; //using bit addressble locations
      delay(1000000);
  }

  return 0;
}


void delay(uint64_t del)
{
  while(del)
  {
    asm("nop");
    del--;
  }
}