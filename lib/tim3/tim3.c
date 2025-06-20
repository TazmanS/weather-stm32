#include "tim3.h"

volatile uint32_t ms_ticks = 0;

void tim3_millis_init(void)
{
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