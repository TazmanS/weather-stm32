#include "dht11.h"

#define DHT11_PIN_MASK (1 << DHT11_PIN)

void dht_set_output(void)
{
  GPIOA_MODER &= ~(0b11 << (DHT11_PIN * 2));
  GPIOA_MODER |= (0b01 << (DHT11_PIN * 2));
}

void dht_set_input(void)
{
  GPIOA_MODER &= ~(0b11 << (DHT11_PIN * 2));
}

void dht_write_high(void)
{
  GPIOA_ODR |= DHT11_PIN_MASK;
}

void dht_write_low(void)
{
  GPIOA_ODR &= ~DHT11_PIN_MASK;
}

uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum)
{
  uint8_t data[5] = {0};

  dht_set_output();
  dht_write_low();
  delay_ms(18);
  dht_write_high();
  delay_us(30);
  dht_set_input();

  delay_us(40);
  if (GPIOA_IDR & (1 << DHT11_PIN))
    return 1;
  delay_us(80);
  if (!(GPIOA_IDR & (1 << DHT11_PIN)))
    return 2;
  delay_us(80);

  for (int i = 0; i < 40; i++)
  {
    while (!(GPIOA_IDR & (1 << DHT11_PIN)))
      ;
    delay_us(30);
    if (GPIOA_IDR & (1 << DHT11_PIN))
      data[i / 8] = (data[i / 8] << 1) | 1;
    else
      data[i / 8] = (data[i / 8] << 1);
    while (GPIOA_IDR & (1 << DHT11_PIN))
      ;
  }

  uint8_t sum = data[0] + data[1] + data[2] + data[3];
  if (sum != data[4])
    return 3;

  *hum = data[0];
  *temp = data[2];
  return 0;
}