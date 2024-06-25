
#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "utils.h"
#include "string.h"
#include <stdint.h>
#include <gcov.h>
#include <errno.h>
#include <stdio.h>


void delay(uint64_t del);

uint32_t arr[5] = {1, 2, 3, 4, 5};



volatile uint8_t gcda_d[4096];
uint32_t gcda_d_idx;

int __io_putchar(int ch){
  gcda_d[gcda_d_idx++] = ch;

  return ch;
}


int main(void)
{


  uint32_t gcda_start_addr, gcda_end_addr;
  gcda_start_addr = (uint32_t)(&gcda_d[0]);


  GPIO_Init();


  for (;;)
  {
    arr[4]++;
    
    if(arr[4] > 9)
      arr[4] = 0;
    
    if(arr[4] > 100)
      arr[0] = arr[4];

    if(arr[0] == 9){
      __gcov_exit();
      gcda_end_addr = gcda_start_addr + gcda_d_idx;
    }

    /* blink led on pin C13 */
    GPIOC_ODR = _setBit(GPIOC_ODR, 13);
    delay(100000);
    GPIOC_ODR = _clrBit(GPIOC_ODR, 13);
    delay(100000);

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