#include "defines.h"
#include "dht11.h"
#include "usart.h"
#include "systick.h"
#include "four_digit_seven_seg.h"
#include "tim3.h"

#define NVIC_ISER0 (*(volatile uint32_t *)0xE000E100)

void NVIC_EnableIRQ_manual(uint8_t irq_num)
{
  NVIC_ISER0 |= (1 << irq_num);
}

int main()
{
  RCC_AHBENR |= (1 << 17);
  RCC_AHBENR |= (1 << 18);
  RCC_APB1ENR |= (1 << 17);
  RCC_APB1ENR |= (1 << 1);

  uart_init();
  tim3_millis_init();
  NVIC_EnableIRQ_manual(29);
  asm volatile("cpsie i");
  initFourDigitSevenSeg();

  uint32_t last_read_time = 0;
  uint8_t temp = 0, hum = 0;
  uart_send_str("Terminal ready\r\n");

  while (1)
  {
    if (millis() - last_read_time >= 2000)
    {
      last_read_time = millis();
      if (DHT11_Read(&temp, &hum) == 0)
      {
        char buf[64];
        sprintf(buf, "Temp: %d°C, Humidity: %d%%\n", temp, hum);
        uart_send_str(buf);

        current_digits[0] = (temp / 1000) % 10;
        current_digits[1] = (temp / 100) % 10;
        current_digits[2] = (temp / 10) % 10;
        current_digits[3] = temp % 10;
      }
      else
      {
        uart_send_str("Error DHT11\n");
      }
    }
    update_display_once();
  }
}