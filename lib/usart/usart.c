#include "usart.h"

void uart_init(void)
{
  GPIOA_MODER &= ~((0b11 << (USART2_PIN_1 * 2)) | (0b11 << (USART2_PIN_2 * 2)));
  GPIOA_MODER |= (0b10 << (USART2_PIN_1 * 2)) | (0b10 << (USART2_PIN_2 * 2));
  GPIOA_AFRL &= ~((0xF << (USART2_PIN_1 * 4)) | (0xF << (USART2_PIN_2 * 4)));
  GPIOA_AFRL |= (0x7 << (USART2_PIN_1 * 4)) | (0x7 << (USART2_PIN_2 * 4));

  // 8 MG -> 9600 = 8000000 / 9600 = ~833
  USART2_BRR = 833;

  USART2_CR1 = (1 << 2) | (1 << 3) | (1 << 0);
}

char uart_receive(void)
{
  while (!(USART2_ISR & (1 << 5)))
    ;
  return (char)USART2_RDR;
}

void uart_send(char c)
{
  while (!(USART2_ISR & (1 << 7)))
    ;
  USART2_TDR = c;
}

void uart_send_str(const char *s)
{
  while (*s)
    uart_send(*s++);
}