#include "defines.h"
#include "dht11.h"
#include "usart.h"
#include "systick.h"

int main()
{
  RCC_AHBENR |= (1 << 17);
  RCC_APB1ENR |= (1 << 17);

  uart_init();

  uint8_t temp = 0, hum = 0, status;
  uart_send_str("Terminal ready\r\n");

  while (1)
  {
    status = DHT11_Read(&temp, &hum);
    if (status == 0)
    {
      char buf[64];
      sprintf(buf, "Temp: %d°C, Humidity: %d%%\n", temp, hum);
      uart_send_str(buf);
    }
    else
    {
      uart_send_str("Error DHT11\n");
    }

    delay_ms(2000);
  }
}