#include "tim2.h"

#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)
#define TIM3_CR1 (*(volatile uint32_t *)0x40000400)
#define TIM3_DIER (*(volatile uint32_t *)0x4000040C)
#define TIM3_SR (*(volatile uint32_t *)0x40000410)
#define TIM3_CNT (*(volatile uint32_t *)0x40000424)
#define TIM3_PSC (*(volatile uint32_t *)0x40000428)
#define TIM3_ARR (*(volatile uint32_t *)0x4000042C)

volatile uint32_t ms_ticks = 0;

void tim3_millis_init(void)
{
  RCC_APB1ENR |= (1 << 1);

  TIM3_PSC = (8000000 / 1000) - 1;
  TIM3_ARR = 1;
  TIM3_DIER |= (1 << 0);
  TIM3_CR1 |= (1 << 0);
}

void TIM3_IRQHandler(void)
{
  if (TIM3_SR & 0x1)
  {
    TIM3_SR &= ~0x1;
    ms_ticks++;
  }
}

uint32_t millis(void)
{
  return ms_ticks;
}