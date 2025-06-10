#ifndef __DHT11_H__
#define __DHT11_H__

#include <stdint.h>

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);

#endif