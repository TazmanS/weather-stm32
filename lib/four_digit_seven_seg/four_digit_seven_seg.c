#include "four_digit_seven_seg.h"

typedef struct
{
  volatile uint32_t *moder;
  volatile uint32_t *odr;
  uint32_t pin;
} SegmentPin;

static SegmentPin segment_pins[8] = {
    {&GPIOA_MODER, &GPIOA_ODR, 0}, // A
    {&GPIOA_MODER, &GPIOA_ODR, 1}, // B
    {&GPIOA_MODER, &GPIOA_ODR, 9}, // C
    {&GPIOA_MODER, &GPIOA_ODR, 8}, // D
    {&GPIOA_MODER, &GPIOA_ODR, 4}, // E
    {&GPIOA_MODER, &GPIOA_ODR, 5}, // F
    {&GPIOA_MODER, &GPIOA_ODR, 6}, // G
    {&GPIOA_MODER, &GPIOA_ODR, 7}, // DP
};

static SegmentPin digit_pins[4] = {
    {&GPIOB_MODER, &GPIOB_ODR, 0}, // 1
    {&GPIOB_MODER, &GPIOB_ODR, 1}, // 2
    {&GPIOB_MODER, &GPIOB_ODR, 2}, // 3
    {&GPIOB_MODER, &GPIOB_ODR, 3}, // 4
};

static const uint8_t digit_segments[10] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111  // 9
};

static void initSegmentPins()
{
  for (int i = 0; i < 8; ++i)
  {
    *(segment_pins[i].moder) &= ~(0b11 << (segment_pins[i].pin * 2));
    *(segment_pins[i].moder) |= (0b01 << (segment_pins[i].pin * 2));
  }
}

static void initDigitPins()
{
  for (int i = 0; i < 4; ++i)
  {
    *(digit_pins[i].moder) &= ~(0b11 << (digit_pins[i].pin * 2));
    *(digit_pins[i].moder) |= (0b01 << (digit_pins[i].pin * 2));
  }
}

static void delay_ms(volatile uint32_t ms)
{
  for (volatile uint32_t i = 0; i < ms * 8000; ++i)
    ;
}

static void seven_seg_display(uint8_t digit)
{
  if (digit > 9)
    return;
  uint8_t segs = digit_segments[digit];
  for (int i = 0; i < 8; ++i)
  {
    if (segs & (1 << i))
    {
      *(segment_pins[i].odr) &= ~(1 << segment_pins[i].pin);
    }
    else
    {
      *(segment_pins[i].odr) |= (1 << segment_pins[i].pin);
    }
  }
}

static void four_digit_display(uint8_t four_digit)
{
  if (four_digit > 4)
    return;
  for (int i = 0; i < 4; ++i)
  {
    *(digit_pins[i].odr) &= ~(1 << digit_pins[i].pin);
  }
  int digit_index = four_digit - 1;
  *(digit_pins[digit_index].odr) |= (1 << digit_pins[digit_index].pin);
}

void showDigits(uint16_t number)
{
  if (number > 9999)
    number = 9999;

  uint8_t digits[4] = {
      (number / 1000) % 10,
      (number / 100) % 10,
      (number / 10) % 10,
      number % 10};
  for (int i = 0; i < 4; ++i)
  {
    four_digit_display(i + 1);
    seven_seg_display(digits[i]);
    delay_ms(2);
  }
}

uint8_t current_digits[4] = {0, 0, 0, 0};

void update_display_once()
{
  static int i = 0;
  four_digit_display(i + 1);
  seven_seg_display(current_digits[i]);
  delay_ms(2);
  i = (i + 1) % 4;
}

void initFourDigitSevenSeg()
{
  initSegmentPins();
  initDigitPins();
}