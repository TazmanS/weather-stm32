#ifndef __TIM3_H__
#define __TIM3_H__

#include "defines.h"

void tim3_millis_init(void);
uint32_t millis(void);
extern void TIM3_IRQHandler(void);

#endif