#include "rcc.h"
#include "utils.h"

void configureSystemClock()
{
  RCC_CR = _setBit(RCC_CR, 16); //Select HSE as main clock
  while(!_chkBit(RCC_CR, 17));  //wait for HSE to stabilize
  /*configure PLL*/
  RCC_PLLCFGR |= _bit(22);      //select HSE as the PLL clock
  RCC_PLLCFGR |= 25;            //divide the HSE clock with 25 PLLM
  RCC_PLLCFGR |= (336<<6);      //VCO multiplication factor, PLLN
  RCC_PLLCFGR &= ~_bit(13);     //clear 13th bit, initially it was set by the reset value; required for the Multiplication factor
  RCC_PLLCFGR |= (1<<16);       //PLL out div factor 4(PLLP: 01) (336/4 = 84)
  RCC_PLLCFGR |= (7<<24);       //VCO div factor of 7 for peripherals (336/7=48) , PLLQ

  RCC_CR |= _bit(24);           //PLL ON
  while(!_chkBit(RCC_CR, 25));  //wait for PLL to stabilize

  // RCC_CFGR &= ~_bit(0);
  // RCC_CFGR |= _bit(1);         //Switch clock to PLL
  // while(!((RCC_CFGR & 0b1100) == 0x1000));  //wait until the clock has switched  
}
