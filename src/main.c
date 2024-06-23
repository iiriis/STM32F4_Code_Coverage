
#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "utils.h"
#include "string.h"
#include <stdint.h>
#include <gcov.h>

void delay(uint64_t del);

char arr[5] = {1, 2, 3, 4, 5};
uint32_t gcov_ptr;
extern uint32_t _gcda_start_addr;

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

static volatile __used __section(".gcda_data")  uint32_t gcda_d[1024];
uint8_t *gcda_d_ptr;

int __io_putchar(int ch){
  *gcda_d_ptr = ch;
  gcda_d_ptr++;
}


void _init_array(){

  extern uint32_t __init_array_start, __init_array_end;

  /* create a function pointer for the init_array vectors */
  typedef void (*init_func_ptr)(void);

  /**  
   *  The init array contains list of vectors for the constructors, make a pointer 
   *  to the starting of the vector list. Grab the value from the vector list as 
   *  the address of the function to jump. And Jump by calling the fuction;
  */
  for(volatile uint32_t *vectors = &__init_array_start; vectors < &__init_array_end; vectors++)
    ((init_func_ptr)(*vectors))();

}



int main(void)
{

  gcda_d_ptr = gcda_d;


  enableFPU();
  GPIO_Init();

  
    _init_array();

  gcov_ptr = (uint32_t)(&_gcda_start_addr);

  for (;;)
  {


    memcpy(arr, "Hello", 5);

    volatile float f = 1.005; /* check for disassembly that contains vadd vdiv etc*/
    for (int i = 0; i < 10; i++)
      f = i / f;

    /* blink led on pin C13 */
    GPIOC_ODR = _setBit(GPIOC_ODR, 13);
    // *(volatile uint32_t*)(PERI_BB_ADDRESS_FROM_ABS_ADDRESS(GPIOC_BASE_ADDR + 0x14, 13)) = 1; //using bit addressble locations
    delay(1000000);
    GPIOC_ODR = _clrBit(GPIOC_ODR, 13);
    // *(volatile uint32_t*)(PERI_BB_ADDRESS_FROM_ABS_ADDRESS(GPIOC_BASE_ADDR + 0x14, 13)) = 0; //using bit addressble locations
    delay(1000000);

    arr[2]++;

    if (arr[2] > 10)
    {
      delay(1000000);
      arr[2]--;
    }

    if (arr[2] > 20)
      GPIOC_ODR = _clrBit(GPIOC_ODR, 13);

    if (arr[4] == 125)
      gcov_ptr = __gcov_exit();
  }

  return 0;
}

void delay(uint64_t del)
{
  while (del)
  {
    asm("nop");
    del--;
  }
}