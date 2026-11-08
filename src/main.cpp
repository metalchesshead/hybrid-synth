#include <MIDI.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>

#include <EEPROM.h>
#include "header.h"
#include "lut.h"
#include "displaystuff.h"
#include <HardwareSerial.h>
#include <usb_serial.h>
#include <Adafruit_SSD1306.h>

#include <Audio.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 


AudioSynthWaveform    waveform1;
AudioOutputPT8211        pt8211_output; 
AudioConnection       patchCord1(waveform1, 0, pt8211_output, 0);
AudioConnection       patchCord2(waveform1, 0, pt8211_output, 1);
AudioControlSGTL5000  sgtl5000_1;
#define DISPLAY_WIDTH    128
#define DISPLAY_HEIGHT   64
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);

 int dacData;
 int dacthing;
int i = 0;
int note1;
int iprev = 0;
int returndispbuff = 0;
// int jprev = 0;
 uint16_t uartdata[256];
 int eedata[256];
const float sampleRate = 44100.0;    // sample rate 44.1KHz
volatile int phInc, phInc2, phIncLFO;                  // dds phase increment
volatile unsigned long phAcc, phAcc2, phAccLFO;        // dds phase accumulator
unsigned long tuningWord, tuningWord2, tuningWordLFO;            // dds tuning word (M)
float lfoFreq = 6.7;
float fOut, fOut2;      
byte tableAddrWidth;
int rec = '0';
uint8_t bigserialbuffer[4096];
uint8_t numBits(uint32_t num) {
 uint8_t width = 32;                // maximum bit width of number being tested
 while (width) {
    width--;
    if (num & (1 << width)) break;  // look for bit position of first "1" from MSB toward LSB
  }                                 // that eliminates leading zeroes and the number bit width is found
 return (width+1);
 }
 void lfo() {
  tableAddrWidth = numBits(256 - 1); 
  tuningWordLFO = pow(2, 32) * lfoFreq / sampleRate;
  phAccLFO += tuningWordLFO;
  phIncLFO = phAccLFO >> (32 - tableAddrWidth);
  dacData = (lfothingy[phIncLFO] >> 1);
}

void setup() {
    // Wire.setClock(1000000);
    // Wire.begin();
            Serial.begin(31250);

    Serial3.begin(31250);
    Serial3.addMemoryForRead(&bigserialbuffer, sizeof(bigserialbuffer)); //resizebuffer
        Wire.begin();
    Wire.setClock(400000);
    delay(1000);
    dma.begin(true);

    delay(20);

    // Initialize OLED using DMA
    oledInitDMA();
    oledClearDMA();
drawcurrentwave(lu67, lut);
 //dmaPrint("HELLO WORLD", 0, 0);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  EEPROM.get(0, lu67);
  waveform1.arbitraryWaveform(lu67, 1000);
  waveform1.begin(WAVEFORM_ARBITRARY);


  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

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

    
//displaystart();
//drawcurrentwave(lu67, lut);

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
  oledClearDMA();
  drawcurrentwave(lu67, lut);
}  

}
void loop() {
    if (!ismoving) {
              if (movebuff ==1) {
                oledClearDMA();
                movebuff = 0;
                drawcurrentwave(lu67, lut);
              }
  
  }
 // dmatst();

  // for (int i=0; i<256; i++){
  //   Serial.print(32768-(lu67[i] + lut[i])/2);
  //   Serial.print(",");

  // }
  // Serial.println();
  //   Serial.println("------------------------------");
// if (ismoving == true){ 
//   //attack();
//   returndispbuff +=1;
// }
// else {
//   if (returndispbuff >0) {
//     //homescreen();
//     //drawcurrentwave(lu67, lut);
//     returndispbuff = 0;
//   }
// }
  serialstuffs();
  if (muxC1<100) {
waveform1.amplitude(0);

}
else {
waveform1.amplitude(0.9);
}
      
   waveform1.frequency(freq1);
MIDI.read();
lfo();
//Serial.println(dacData);
//dacthing =round(((float)dacData/16384)*note1*14.67);
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
