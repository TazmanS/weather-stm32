#ifndef __TIM2_H__
#define __TIM2_H__

#include "defines.h"

void tim3_millis_init(void);
uint32_t millis(void);
extern void TIM3_IRQHandler(void);

#endif