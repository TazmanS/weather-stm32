#include "systick.h"

void delay_us(uint32_t us)
{
  SYSTICK_LOAD = (8000000 / 1000000 - 1) * us;
  SYSTICK_VAL = 0;
  SYSTICK_CTRL = SYSTICK_CLKSOURCE | SYSTICK_ENABLE;
  while (!(SYSTICK_CTRL & SYSTICK_COUNTFLAG))
    ;
  SYSTICK_CTRL = 0;
}

void delay_ms(uint32_t ms)
{
  while (ms--)
    delay_us(1000);
}