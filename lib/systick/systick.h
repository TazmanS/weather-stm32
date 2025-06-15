#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "defines.h"

void systick_init_for_millis();
uint32_t millis();
void SysTick_Handler();

#endif