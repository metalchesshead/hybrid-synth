#pragma once
#ifndef DISPLAYSTUFF_H
#define DISPLAYSTUFF_H
#include "header.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

void drawcurrentwave(int16_t lu67[256], int16_t lut[256]);
void displaystart();
#endif
