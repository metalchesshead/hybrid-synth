#include <MIDI.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include "header.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>



MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 




float CV0 = 0.0;      
float CV1 = 0.0;
int CV2 = 0;
float CV3 = 0.0;
int dacthing = 0;
int note1;


void setup() {
  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
Serial.begin(31250);
    SPI.begin();
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
  SPI.setMOSI(11);
  SPI.setSCK(13);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);

}

void loop() {
MIDI.read();
dacthing =round(note1*75.00);
dacWrite1(dacthing, 0);
dacWrite1(2000, 1);

digitalWrite(2, LOW);
digitalWrite(3, LOW);

digitalWrite(14, HIGH);
digitalWrite(15, LOW);
digitalWrite(16, HIGH);
dacWrite2(4000, 1);
dacWrite2(4000, 0);
digitalWrite(14, HIGH);
digitalWrite(15, LOW);
digitalWrite(16, LOW);
dacWrite2(4000, 1);
dacWrite2(4000, 0);
digitalWrite(14, LOW);
digitalWrite(15, HIGH);
digitalWrite(16, LOW);
dacWrite2(1000, 1);
dacWrite2(1000, 0);

digitalWrite(14, LOW);
digitalWrite(15, LOW);
digitalWrite(16, LOW);
dacWrite2(0, 1);
dacWrite2(0, 0);
digitalWrite(14, HIGH);
digitalWrite(15, HIGH);
digitalWrite(16, LOW);
dacWrite2(1000, 1);
dacWrite2(1000, 0);

}