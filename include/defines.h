#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdint.h>
#include <stdio.h>

extern uint32_t SystemCoreClock;

// RCC
#define RCC_AHBENR (*(volatile uint32_t *)0x40021014)
#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)

// MODER
#define GPIOA_MODER (*(volatile uint32_t *)0x48000000)
#define GPIOB_MODER (*(volatile uint32_t *)0x48000400)

// ODR
#define GPIOA_ODR (*(volatile uint32_t *)0x48000014)
#define GPIOB_ODR (*(volatile uint32_t *)0x48000414)

// IDR
#define GPIOA_IDR (*(volatile uint32_t *)0x48000010)

// AFRL
#define GPIOA_AFRL (*(volatile uint32_t *)0x48000020)

// DHT11
#define DHT11_PIN 10

// USART
#define USART2_CR1 (*(volatile uint32_t *)0x40004400)
#define USART2_BRR (*(volatile uint32_t *)0x4000440C)
#define USART2_ISR (*(volatile uint32_t *)0x4000441C)
#define USART2_RDR (*(volatile uint32_t *)0x40004424)
#define USART2_TDR (*(volatile uint32_t *)0x40004428)
#define USART2_PIN_1 2
#define USART2_PIN_2 3

// SysTick
#define SYSTICK_CTRL (*(volatile uint32_t *)0xE000E010)
#define SYSTICK_LOAD (*(volatile uint32_t *)0xE000E014)
#define SYSTICK_VAL (*(volatile uint32_t *)0xE000E018)

#define SYSTICK_CLKSOURCE (1 << 2)
#define SYSTICK_ENABLE (1 << 0)
#define SYSTICK_COUNTFLAG (1 << 16)

// TIM2
#define TIM2_PSC (*(volatile uint32_t *)0x40000028)
#define TIM2_CR1 (*(volatile uint32_t *)0x40000000)
#define TIM2_CNT (*(volatile uint32_t *)0x40000024)

#endif