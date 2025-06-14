#ifndef __USART_H__
#define __USART_H__

#include "defines.h"

void uart_init();
void uart_send_str(const char *s);
char uart_receive();

#endif