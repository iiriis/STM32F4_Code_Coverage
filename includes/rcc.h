#include <stdint.h>

#define RCC_BASE_ADDR 0x40023800

#define RCC_CR            (*((volatile uint32_t *)(RCC_BASE_ADDR+0x00)))
#define RCC_PLLCFGR       (*((volatile uint32_t *)(RCC_BASE_ADDR+0x04)))
#define RCC_CFGR          (*((volatile uint32_t *)(RCC_BASE_ADDR+0x08)))
#define RCC_CIR           (*((volatile uint32_t *)(RCC_BASE_ADDR+0x0C)))
#define RCC_AHB1RSTR      (*((volatile uint32_t *)(RCC_BASE_ADDR+0x10)))
#define RCC_AHB2RSTR      (*((volatile uint32_t *)(RCC_BASE_ADDR+0x14)))
#define RCC_APB1RSTR      (*((volatile uint32_t *)(RCC_BASE_ADDR+0x20)))
#define RCC_APB2RSTR      (*((volatile uint32_t *)(RCC_BASE_ADDR+0x24)))
#define RCC_AHB1ENR       (*((volatile uint32_t *)(RCC_BASE_ADDR+0x30)))
#define RCC_AHB2ENR       (*((volatile uint32_t *)(RCC_BASE_ADDR+0x34)))
#define RCC_APB1ENR       (*((volatile uint32_t *)(RCC_BASE_ADDR+0x40)))
#define RCC_APB2ENR       (*((volatile uint32_t *)(RCC_BASE_ADDR+0x44)))
#define RCC_AHB1LPENR     (*((volatile uint32_t *)(RCC_BASE_ADDR+0x50)))
#define RCC_AHB2LPENR     (*((volatile uint32_t *)(RCC_BASE_ADDR+0x54)))
#define RCC_APB1LPENR     (*((volatile uint32_t *)(RCC_BASE_ADDR+0x60)))
#define RCC_APB2LPENR     (*((volatile uint32_t *)(RCC_BASE_ADDR+0x64)))
#define RCC_BDCR          (*((volatile uint32_t *)(RCC_BASE_ADDR+0x70)))
#define RCC_CSR           (*((volatile uint32_t *)(RCC_BASE_ADDR+0x74)))
#define RCC_SSCGR         (*((volatile uint32_t *)(RCC_BASE_ADDR+0x80)))
#define RCC_PLLI2SCFGR    (*((volatile uint32_t *)(RCC_BASE_ADDR+0x84)))
#define RCC_DCKCFGR       (*((volatile uint32_t *)(RCC_BASE_ADDR+0x8C)))


void configureSystemClock();