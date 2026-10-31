#include <MIDI.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "header.h"
#include <HardwareSerial.h>
#include <usb_serial.h>
#include "DmaSerial.h"

#include <Audio.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

AudioSynthWaveform    waveform1;
AudioOutputPT8211        pt8211_output; 
AudioConnection       patchCord1(waveform1, 0, pt8211_output, 0);
AudioConnection       patchCord2(waveform1, 0, pt8211_output, 1);
AudioControlSGTL5000  sgtl5000_1;

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int16_t lut[256] = {
     1,     2,     2,     2,     2,     2,     2,
     3,     3,     3,     3,     4,     4,     4,
     4,     5,     5,     6,     6,     7,     7,
     8,     8,     9,    10,    10,    11,    12,
    13,    14,    15,    17,    18,    20,    21,
    23,    25,    27,    29,    31,    34,    37,
    40,    43,    46,    50,    54,    58,    63,
    68,    74,    80,    86,    93,   101,   109,
   118,   127,   138,   149,   161,   174,   188,
   203,   219,   237,   256,   277,   299,   323,
   349,   377,   407,   440,   475,   513,   554,
   598,   646,   698,   753,   813,   877,   946,
  1020,  1101,  1187,  1279,  1379,  1486,  1601,
  1724,  1856,  1998,  2150,  2312,  2486,  2671,
  2869,  3080,  3305,  3545,  3800,  4070,  4357,
  4661,  4982,  5321,  5678,  6054,  6449,  6864,
  7297,  7750,  8222,  8712,  9221,  9747, 10290,
 10850, 11424, 12012, 12612, 13224, 13844, 14472,
 15106, 15744, 16383, 17023, 17661, 18295, 18923,
 19543, 20155, 20755, 21343, 21917, 22477, 23020,
 23546, 24055, 24545, 25017, 25470, 25903, 26318,
 26713, 27089, 27446, 27785, 28106, 28410, 28697,
 28967, 29222, 29462, 29687, 29898, 30096, 30281,
 30455, 30617, 30769, 30911, 31043, 31166, 31281,
 31388, 31488, 31580, 31666, 31747, 31821, 31890,
 31954, 32014, 32069, 32121, 32169, 32213, 32254,
 32292, 32327, 32360, 32390, 32418, 32444, 32468,
 32490, 32511, 32530, 32548, 32564, 32579, 32593,
 32606, 32618, 32629, 32640, 32649, 32658, 32666,
 32674, 32681, 32687, 32693, 32699, 32704, 32709,
 32713, 32717, 32721, 32724, 32727, 32730, 32733,
 32736, 32738, 32740, 32742, 32744, 32746, 32747,
 32749, 32750, 32752, 32753, 32754, 32755, 32756,
 32757, 32757, 32758, 32759, 32759, 32760, 32760,
 32761, 32761, 32762, 32762, 32763, 32763, 32763,
 32763, 32764, 32764, 32764, 32764, 32765, 32765,
 32765, 32765, 32765, 32765 };
int dacthing = 0;
int i = 0;
int note1;
int iprev = 0;
int jprev = 0;
 uint16_t uartdata[256];
 int16_t lu67[256];
 int eedata[256];
// const float sampleRate = 44100.0;    // sample rate 44.1KHz
// volatile int phInc, phInc2, phIncLFO;                  // dds phase increment
// volatile unsigned long phAcc, phAcc2, phAccLFO;        // dds phase accumulator
// unsigned long tuningWord, tuningWord2, tuningWordLFO;            // dds tuning word (M)
// float lfoFreq = 0.0;
// float fOut, fOut2;      
// byte tableAddrWidth;
int dacData = 0;                     // dac output data
int rec = '0';
uint8_t bigserialbuffer[4096];

void setup() {
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  EEPROM.get(0, lu67);
  waveform1.arbitraryWaveform(lu67, 1000);
  waveform1.begin(WAVEFORM_ARBITRARY);


  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//Serial.begin(31250);

    SPI.begin();
    pinMode(1, OUTPUT); //CV_INH
    pinMode(2, OUTPUT); //A
    pinMode(3, OUTPUT); //B
    pinMode(4, OUTPUT); //C
    pinMode(5, OUTPUT); //wavesel A
    pinMode(8, OUTPUT); //wavesel B

    pinMode(6, OUTPUT); //CS1
    pinMode(12, OUTPUT);

    pinMode(22, INPUT); //mux2
    pinMode(17, INPUT); //mux1
    pinMode(16, INPUT); //mux3
  SPI.setMOSI(11);
  SPI.setSCK(13);
        Serial.begin(31250);
    // dmaSerial1.begin(115200);
    // dmaSerial2.begin(115200);
    //dmaSerial3.begin(31250);
    // dmaSerial4.begin(115200);
    // dmaSerial5.begin(115200);
    Serial3.begin(31250);
    Serial3.addMemoryForRead(&bigserialbuffer, sizeof(bigserialbuffer));
    

}
void envelopee() {
       CV0=muxA0;
  alpha1=0.999*cos((1023-CV0)/795);
  alpha1=sqrt(alpha1);  

//   alphaA1=0.999*cos((1023-CV0)/795);
//   alphaA1=sqrt(alphaA1);  
 
 // CV1=analogRead(1);      
 CV1 = muxA1;                // get the release pole location
  alpha2=0.999*cos((1023-CV1)/795);
  alpha2=sqrt(alpha2);  
  
//   alphaA2=0.999*cos((1023-CV1)/795);
//   alphaA2=sqrt(alphaA2); 
  
 //CV2=mux2A;                     // get the (integer) sustain level
 CV2 = round((drive/1023))*muxA2 + 610;
  sustain=CV2;
//   sustainA=CV2<<2;



  //CV3=analogRead(3);                     // get the release pole location (potentially closer to 1.0)
  CV3 = muxA3;
  alpha3=0.99999*cos((1023-CV3)/795);
  alpha3=sqrt(alpha3);

//   alphaA3=0.99999*cos((1023-CV3)/795);
//   alphaA3=sqrt(alphaA3);
envelope= ((1.0-alpha)*drive+alpha*envelope);
//dacWrite2(round(2700-envelope));
if (envelope<4.0) {
  envelope = 0.0;
}

if(decay == false && ((envelope>=(drive-3) && drive==21*velocity1))){// if we are in attack phase and we've reached envelope >4000 with drive= 4096, we must be at the end of attack phase
                                                            // so switch to decay...
      decay = true;                                         // set decay flag
      drive=sustain;                                  // drive toward sustain level
      alpha=alpha2;                                         // and set 'time constant' alpha2 for decay phase
      }



}
void serialstuffs() {

  while (Serial3.available()>=514) {
        byte startbit2 = Serial3.read();

    byte startbit1 = Serial3.read();
    if (((startbit1 << 8) | startbit2) !=5) {
      Serial.println("error");
    }
  
  //Serial.println("23232");

 for (i =0; i<256; i++){
byte low = Serial3.read();
   byte high = Serial3.read();
   
//uartdata[i + iprev ]= (low << 8) | high;
uartdata[i]= (high << 8) | low;


  }
  rec = rec + 1;
  //Serial3.println((uint8_t)rec);
iprev = iprev + 32;

//Serial.println((iprev));

}


 
if (iprev>0) {

  for (int j = 0; j<256; j++) {
    
    Serial.println(uartdata[j]);
lu67[j] = uartdata[j];

  }
  EEPROM.put(0, lu67);
    waveform1.arbitraryWaveform(lu67, 1000);
  waveform1.begin(WAVEFORM_ARBITRARY);
  //eepromwrite(0, eedata, 256);
  iprev = 0;
}  

}
void loop() {
  serialstuffs();
  if (muxC1<100) {
waveform1.amplitude(0);

}
else {
waveform1.amplitude(0.9);
}
      
   waveform1.frequency(freq1);
MIDI.read();
dacthing =round(note1*14.67);
if (muxC0<100) {
digitalWrite(5, LOW);
digitalWrite(8, LOW);
}
else if (muxC0>=100 && muxC0<500)
{
  digitalWrite(5, HIGH);
digitalWrite(8, HIGH);
}
else if (muxC0>=500 && muxC0 <750) {
  digitalWrite(5, HIGH);
digitalWrite(8, HIGH);
}
else if (muxC0>=750) {
  digitalWrite(5, HIGH);
digitalWrite(8, HIGH);
}

mux();
envelopee();
  //   waveform1.amplitude(tempamp);
  //  waveform1.frequency(freq1);
//dacWrite1(dacthing, 0);
//dacWrite1(430, 1);

//digitalWrite(1, HIGH); //CV_INH

//digitalWrite(1, LOW); //CV_INH
// muxA0 = analogRead(17);
// muxB0 = analogRead(20);
//delayMicroseconds(5);



}
