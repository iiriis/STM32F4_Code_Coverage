
#include "gpio.h"
#include "rcc.h"
#include "utils.h"


void GPIO_Init()
{
  RCC_AHB1ENR |= _bit(2); //enabling clock for GPIO Bank C

  /*USER LED on Pin C13*/
  GPIOC_MODER = _clrBit(GPIOC_MODER, 26); //clear the bit status
  GPIOC_MODER = _clrBit(GPIOC_MODER, 27); //clear the bit status
  GPIOC_MODER = _setBit(GPIOC_MODER, 26); //set the 13th GPIO with 01 status; i.e OUTPUT

  GPIOC_OTYPER = _clrBit(GPIOC_MODER, 13); //set the 13th GPIO as Push, Pull

  GPIOC_OSPEEDR = _setBit(GPIOC_MODER, 26); //set the 13th GPIO as very high speed Output
  GPIOC_OSPEEDR = _setBit(GPIOC_MODER, 27);

}