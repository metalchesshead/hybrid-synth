#include <Arduino.h> 
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
void myNoteOn(byte channel, byte note, byte velocity);
void myNoteOff(byte channel, byte note, byte velocity); 
void dacWrite1(int value, byte dac);
void dacWrite2(int value, byte dac);
void mux();
void eepromwrite(int address, int numbers[], int arraySize);
void eepromread(int address, int numbers[], int arraySize);
void lfo(int lut[256]);
//int note1;
//int mux0, mux1, mux2, mux3, mux4, mux5, mux6, mux7;

#ifndef GLOBALS_H
#define GLOBALS_H



extern int note1;
extern int dacthing;
inline int muxB0, muxB1, muxB2, muxB3, muxB4, muxB5, muxB6, muxB7;
inline int muxA0, muxA1, muxA2, muxA3, muxA4, muxA5, muxA6, muxA7;
inline int muxC0, muxC1, muxC2, muxC3, muxC4, muxC5, muxC6, muxC7;

inline int sustain =0;
inline int sustainF =0;

inline float envelope = 0.0;
inline float CV0 = 0.0;       // result of reads from potentiometers (yes - it will only be an int, but helps with the casting!)
inline float CV1 = 0.0;
inline int CV2 = 0;
inline float CV3 = 0.0;
inline float alpha=0.7;
inline int drive = 0;
inline double alpha1=0.9;  // initial value for attack
inline double alpha2=0.9;  // initial value for decay
inline double alpha3=0.95; // initial value for release

inline float envelopeF = 0.0;
inline float CV0F = 0.0;       // result of reads from potentiometers (yes - it will only be an int, but helps with the casting!)
inline float CV1F = 0.0;
inline int CV2F = 0;
inline float CV3F = 0.0;
inline float alphaF=0.7;
inline int driveF = 0;
inline double alpha1F=0.9;  // initial value for attack
inline double alpha2F=0.9;  // initial value for decay
inline double alpha3F=0.95; // initial value for release


inline boolean decay = false;
inline boolean decayF = false;
inline int velocity1= 0;
inline float freq1  =0.0;

inline float tempamp = 0.0;
                    // target output frequency (Hz)


#endif
