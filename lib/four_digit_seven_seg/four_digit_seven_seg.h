#ifndef FOUR_DIGIT_SEVEN_SEG_H
#define FOUR_DIGIT_SEVEN_SEG_H

#include "defines.h"

void initFourDigitSevenSeg();
void showDigits(uint16_t number);
void update_display_once();
uint8_t current_digits[4];

#endif