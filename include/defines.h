#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdint.h>

#define RCC_AHBENR (*(volatile uint32_t *)0x40021014)
#define GPIOA_MODER (*(volatile uint32_t *)0x48000000)
#define GPIOA_ODR (*(volatile uint32_t *)0x48000014)
#define GPIOA_IDR (*(volatile uint32_t *)0x48000010)

// DHT11
#define DHT11_PIN 9

static inline void delay_us(uint32_t us)
{
  for (volatile uint32_t i = 0; i < us * 8; i++)
    ;
}

#endif