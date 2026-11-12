#pragma once
#ifndef DISPLAYSTUFF_H
#define DISPLAYSTUFF_H
#include "header.h"


extern int attackold;
extern bool ismoving;


extern DMAChannel dma;

// void drawcurrentwave(int16_t lu67[256], int16_t lut[256]);
// void displaystart();
// void attack();
// void homescreen();


bool dmaPrint(const char *str, uint8_t column, uint8_t page);
bool dmaI2CWrite(uint8_t control, const uint8_t *data, uint16_t length);
bool oledInitDMA();
bool oledClearDMA();
bool sendCharacterDMA();
bool drawPixelDMA(uint8_t x, uint8_t y, bool color = true);
void drawcurrentwave(int16_t lu67[256], int16_t lut[256]);
void drawLineDMA(int x0, int y0, int x1, int y1, bool color = true);
bool oledDisplayBufferDMA();

#endif
