#include "systick.h"

volatile uint32_t ms_ticks = 0;

void SysTick_Handler()
{
  ms_ticks++;
}

uint32_t millis()
{
  return ms_ticks;
}

void systick_init_for_millis()
{
  SYSTICK_LOAD = (SystemCoreClock / 1000) - 1;
  SYSTICK_VAL = 0;
  SYSTICK_CTRL = 7;
}