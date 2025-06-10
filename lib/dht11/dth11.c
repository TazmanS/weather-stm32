#include "defines.h"
#include "dht11.h"

#define DHT11_PIN_MASK (1 << DHT11_PIN)

static void set_input(void)
{
  GPIOA_MODER &= ~(0b11 << (DHT11_PIN * 2));
}

static void set_output(void)
{
  GPIOA_MODER &= ~(0b11 << (DHT11_PIN * 2));
  GPIOA_MODER |= (0b01 << (DHT11_PIN * 2));
}

static void write_low(void)
{
  GPIOA_ODR &= ~DHT11_PIN_MASK;
}

static void write_high(void)
{
  GPIOA_ODR |= DHT11_PIN_MASK;
}

static uint8_t read_pin(void)
{
  return (GPIOA_IDR & DHT11_PIN_MASK) != 0;
}

static uint8_t read_byte(void)
{
  uint8_t byte = 0;
  for (int i = 0; i < 8; i++)
  {
    while (!read_pin())
      ;
    delay_us(30);
    if (read_pin())
      byte |= (1 << (7 - i));
    while (read_pin())
      ;
  }
  return byte;
}

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity)
{
  set_output();
  write_low();
  delay_us(18000); // 18 ms
  write_high();
  delay_us(20); // 20–40 mks
  set_input();

  // DHT11 response: 80 mks LOW, 80 mks HIGH
  while (read_pin())
    ; // LOW
  while (!read_pin())
    ; // HIGH
  while (read_pin())
    ; // HIGH

  // 5 bites
  uint8_t hum_int = read_byte();
  uint8_t hum_dec = read_byte();
  uint8_t temp_int = read_byte();
  uint8_t temp_dec = read_byte();
  uint8_t checksum = read_byte();

  if ((hum_int + hum_dec + temp_int + temp_dec) != checksum)
    return 1; // error

  *temperature = temp_int;
  *humidity = hum_int;
  return 0; // success
}
