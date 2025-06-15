#include "tim2.h"

void tim2_init(void)
{
  RCC_APB1ENR |= (1 << 0);

  TIM2_PSC = (SystemCoreClock / 1000000) - 1;
  TIM2_CR1 |= (1 << 0);
}

void delay_us(uint32_t us)
{
  uint32_t start = TIM2_CNT;
  while ((TIM2_CNT - start) < us)
    ;
}

void delay_ms(uint32_t ms)
{
  while (ms--)
    delay_us(1000);
}