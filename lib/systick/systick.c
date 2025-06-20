#include "systick.h"

#define SYSTICK_CLKSOURCE (1 << 2)
#define SYSTICK_ENABLE (1 << 0)
#define SYSTICK_COUNTFLAG (1 << 16)

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