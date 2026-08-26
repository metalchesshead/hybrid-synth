#include <MIDI.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "header.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>



MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




int dacthing = 0;
int i = 0;
int note1;
int iprev = 0;
int jprev = 0;
uint16_t uartdata[960];
int eedata[960];
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

  pinMode(17, INPUT);
  pinMode(20, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Booting...");
    display.display();
    delay(1000);
    display.clearDisplay();

    Serial2.begin(31250);
    eepromread(0, eedata, 960);
      for (int j = 0; j<960; j++) {

    Serial.println(eedata[j]);
        if (j%8 == 0 && j>0){
          display.drawLine(j/8, round(eedata[j]/52), (jprev)/8, round(eedata[jprev]/52), WHITE);
   //display.drawPixel(j/8, round(uartdata[j]/52), WHITE);


    display.display();
    jprev = j;
  }
  }
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


void envelopeeF() {
       CV0F=muxA4;
  alpha1F=0.999*cos((1023-CV0F)/795);
  alpha1F=sqrt(alpha1F);  

//   alphaA1=0.999*cos((1023-CV0)/795);
//   alphaA1=sqrt(alphaA1);  
 
 // CV1=analogRead(1);      
 CV1F = muxA5;                // get the release pole location
  alpha2F=0.999*cos((1023-CV1F)/795);
  alpha2F=sqrt(alpha2F);  
  
//   alphaA2=0.999*cos((1023-CV1)/795);
//   alphaA2=sqrt(alphaA2); 
  
 //CV2=mux2A;                     // get the (integer) sustain level
 CV2F = round((driveF/1023))*muxA6 + 610;
  sustainF=CV2F;
//   sustainA=CV2<<2;



  //CV3=analogRead(3);                     // get the release pole location (potentially closer to 1.0)
  CV3F = muxA7;
  alpha3F=0.99999*cos((1023-CV3F)/795);
  alpha3F=sqrt(alpha3F);

//   alphaA3=0.99999*cos((1023-CV3)/795);
//   alphaA3=sqrt(alphaA3);
envelopeF = ((1.0-alphaF)*driveF+alphaF*envelopeF);
//dacWrite2(round(2700-envelope));
if (envelopeF<4.0) {
  envelopeF = 0.0;
}


if(decayF == false && ((envelopeF>=(driveF-3) && driveF==2701))){// if we are in attack phase and we've reached envelope >4000 with drive= 4096, we must be at the end of attack phase
                                                            // so switch to decay...
      decayF = true;                                         // set decay flag
      driveF=sustainF;                                  // drive toward sustain level
      alphaF=alpha2F;                                         // and set 'time constant' alpha2 for decay phase
      }
}
void loop() {
MIDI.read();
dacthing =round(note1*15.30);
envelopee();
envelopeeF();
mux();
dacWrite1(dacthing, 0);
dacWrite1(430, 1);

dacWrite2(0,0);
digitalWrite(2, LOW);
digitalWrite(3, LOW);



while (Serial2.available()>=64) {
 for (i =0; i<32; i++){

   byte high = Serial2.read();
   byte low = Serial2.read();
uartdata[i + iprev ]= (low << 8) | high;



  }
iprev = iprev + 32;
Serial.println(iprev);

}
if (iprev >= 960) {
  iprev = 0;


  for (int j = 0; j<960; j++) {
    eedata[j] = uartdata[j];
    Serial.println(uartdata[j]);
        if (j%8 == 0 && j>0){
          display.drawLine(j/8, round(eedata[j]/52), (jprev)/8, round(eedata[jprev]/52), WHITE);
   //display.drawPixel(j/8, round(uartdata[j]/52), WHITE);


    display.display();
    jprev = j;
  }
  }
eepromwrite(0, eedata, 960);
}
//Serial.println(envelopeF);

}
