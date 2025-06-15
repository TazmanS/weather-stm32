#include "defines.h"
#include "dht11.h"
#include "usart.h"
// #include "systick.h"
// #include "four_digit_seven_seg.h"
#include "tim2.h"

// int main()
// {
//   RCC_AHBENR |= (1 << 17);
//   RCC_AHBENR |= (1 << 18);
//   RCC_APB1ENR |= (1 << 17);

//   uart_init();
//   tim2_init();
//   systick_init_for_millis();
//   asm volatile("cpsie i");
//   initFourDigitSevenSeg();

//   uint32_t last_read_time = 0;
//   uint8_t temp = 0, hum = 0;
//   uart_send_str("Terminal ready\r\n");

//   while (1)
//   {
//     if (millis() - last_read_time >= 2000)
//     {
//       last_read_time = millis();
//       if (DHT11_Read(&temp, &hum) == 0)
//       {
//         char buf[64];
//         sprintf(buf, "Temp: %d°C, Humidity: %d%%\n", temp, hum);
//         uart_send_str(buf);

//         current_digits[0] = (temp / 1000) % 10;
//         current_digits[1] = (temp / 100) % 10;
//         current_digits[2] = (temp / 10) % 10;
//         current_digits[3] = temp % 10;
//       }
//       else
//       {
//         uart_send_str("Error DHT11\n");
//       }
//     }
//     update_display_once();
//   }
// }

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