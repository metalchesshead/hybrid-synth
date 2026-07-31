#include <Arduino.h>
void myNoteOn(byte channel, byte note, byte velocity);
void myNoteOff(byte channel, byte note, byte velocity); 
void dacWrite1(int value, byte dac);
void dacWrite2(int value, byte dac);
//int note1;
//int mux0, mux1, mux2, mux3, mux4, mux5, mux6, mux7;

#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h> // Gives access to Arduino types like String or boolean

extern int note1;
extern int dacthing;
#endif
