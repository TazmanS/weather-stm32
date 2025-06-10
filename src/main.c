#include "defines.h"
#include "dht11.h"

#include <stdio.h>

int main()
{
  RCC_AHBENR |= (1 << 17);

  uint8_t temp = 0, hum = 0;
  while (1)
  {
    if (DHT11_Read(&temp, &hum) == 0)
    {
      printf("Temp: %d°C, Humidity: %d%%\n", temp, hum);
    }
    else
    {
      printf("Error DHT11\n");
    }

    delay_us(2000);
  }
}