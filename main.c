#include <MIDI.h>
#include <SPI.h>
#include <Arduino.h>
#define samplesPerCycle 761

// data table for one cycle of sine wave
int sineData[samplesPerCycle]  = {
    

 32, 40, 56, 104, 112, 128, 152, 176, 184, 200, 208, 224, 232, 240, 248, 264, 264, 280, 288, 304, 320, 328, 352, 360, 368, 384, 400, 416, 432, 448, 456, 480, 496, 512, 552, 568, 608, 640, 672, 704, 736, 768, 824, 848, 888, 912, 944, 968, 984, 1000, 1008, 1016, 1032, 1040, 1048, 1080, 1120, 1144, 1176, 1216, 1272, 1320, 1360, 1416, 1456, 1504, 1544, 1584, 1624, 1664, 1704, 1736, 1768, 1792, 1808, 1816, 1824, 1832, 1840, 1848, 1856, 1864, 1872, 1880, 1896, 1904, 1912, 1920, 1928, 1936, 1952, 1960, 1976, 2008, 2048, 2088, 2136, 2192, 2240, 2312, 2360, 2416, 2456, 2488, 2512, 2536, 2552, 2560, 2568, 2576, 2592, 2592, 2600, 2616, 2632, 2648, 2656, 2680, 2696, 2704, 2720, 2728, 2736, 2744, 2752, 2760, 2776, 2800, 2816, 2856, 2896, 2960, 3000, 3040, 3096, 3160, 3200, 3248, 3280, 3312, 3328, 3336, 3344, 3352, 3368, 3376, 3392, 3416, 3424, 3432, 3448, 3456, 3472, 3480, 3488, 3504, 3528, 3568, 3616, 3640, 3672, 3728, 3784, 3840, 3904, 3968, 4048, 4112, 4176, 4240, 4280, 4288, 4296, 4312, 4320, 4328, 4328, 4352, 4376, 4392, 4400, 4440, 4456, 4496, 4528, 4560, 4576, 4592, 4608, 4616, 4632, 4632, 4640, 4648, 4656, 4664, 4672, 4680, 4688, 4696, 4704, 4712, 4720, 4728, 4736, 4744, 4752, 4760, 4768, 4776, 4784, 4792, 4800, 4800, 32, 40, 48, 56, 56, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 56, 48, 40, 40, 40, 32, 16, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 72, 72, 64, 64, 64, 64, 64, 64, 56, 40, 24, 64, 64, 64, 64, 64, 64, 72, 72, 72, 72, 72, 72, 72, 72, 72, 88, 96, 104, 112, 128, 128, 128, 136, 144, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 136, 128, 120, 120, 120, 112, 104, 104, 104, 96, 88, 88, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 72, 64, 64, 64, 64, 64, 64, 64, 64, 64, 80, 88, 112, 136, 168, 200, 240, 272, 304, 320, 344, 368, 392, 432, 456, 480, 504, 528, 560, 584, 616, 640, 664, 704, 728, 752, 776, 792, 816, 840, 864, 888, 912, 936, 960, 984, 1016, 1040, 1072, 1120, 1200, 1224, 1248, 1256, 1264, 1280, 1288, 1304, 1328, 1344, 1352, 1376, 1392, 1416, 1432, 1456, 1464, 1472, 1480, 1488, 1496, 1504, 1496, 1496, 1496, 1488, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1520, 1544, 1560, 1568, 1568, 1568, 1568, 1560, 1544, 1528, 1496, 1464, 1432, 1408, 1384, 1328, 1280, 1248, 1192, 1128, 1088, 1024, 960, 832, 752, 688, 624, 576, 520, 480, 448, 424, 408, 392, 384, 368, 360, 344, 336, 328, 312, 288, 272, 248, 224, 184, 168, 144, 112, 104, 96, 88, 72, 72, 64, 56, 56, 64, 72, 88, 104, 136, 152, 200, 224, 248, 272, 296, 312, 328, 360, 392, 424, 440, 472, 504, 512, 544, 568, 592, 664, 720, 784, 832, 880, 952, 1008, 1064, 1096, 1112, 1120, 1136, 1144, 1152, 1160, 1168, 1192, 1240, 1312, 1376, 1448, 1528, 1592, 1656, 1696, 1768, 1800, 1840, 1856, 1888, 1920, 1952, 1992, 2040, 2088, 2128, 2184, 2248, 2312, 2360, 2424, 2456, 2496, 2520, 2544, 2576, 2600, 2608, 2624, 2632, 2656, 2664, 2672, 2688, 2696, 2728, 2784, 2856, 2936, 3096, 3208, 3336, 3472, 3584, 3704, 3792, 3856, 3928, 3944, 3952, 3960, 3968, 3984, 3992, 4008, 4016, 4024, 4032, 4040, 4048, 4056, 4064, 4072, 4080, 4104, 4136, 4192, 4256, 4368, 4472, 4536, 4576, 4600, 4608, 4616, 4624, 4632, 4640, 4648, 4656, 4664, 4680, 4680, 4680, 4672, 4672, 4664, 4648, 4648, 4640, 4632, 4632, 4624, 4624, 4616, 4608, 4608, 4592, 4584, 4560, 4552, 4528, 4512, 4480, 4448, 4432, 4400, 4384, 4352, 4344, 4288, 4264, 4224, 4176, 4152, 4112, 4080, 4064, 4024, 4016, 3968, 3944, 3920, 3880, 3840, 3808, 3776, 3712, 3544, 3488, 3392, 3304, 3232, 3184, 3120, 3048, 2992, 2896, 2848, 2800, 2768, 2720, 2688, 2640, 2576, 2544, 2504, 2456, 2416, 2384, 2352, 2320, 2280, 2240, 2208, 2176, 2136, 2088, 2032, 1984, 1936, 1880, 1832, 1768, 1712, 1664, 1608, 1576, 1536, 1496, 1432, 1392, 1368, 1328, 1288, 1240, 1200, 1160, 1120, 1080, 1064, 1040, 1000, 976, 928, 904, 824, 792, 744, 712, 688, 672, 648, 616, 592, 568, 536, 528, 520, 472, 448, 432, 400, 392, 376, 376, 352, 328, 304, 272, 240, 200, 160, 144, 128, 120, 96, 72, 56, 48, 40, 32, 24, 24


};
const float sampleRate = 44100.0;    // sample rate 44.1KHz
float fOut, fOut2;                          // target output frequency (Hz)

volatile int phInc, phInc2;                  // dds phase increment
volatile unsigned long phAcc, phAcc2;        // dds phase accumulator
unsigned long tuningWord, tuningWord2;            // dds tuning word (M)

byte tableAddrWidth;
int dacData = 0;                     // dac output data


//4 is sck, 5 is miso, 6 is mosi
// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); 
float freq = 0.0;
void dacWrite1(int value, byte dac) {
  //write a 12 bit number to the MCP4921 DAC
  // take the SS pin low to select the chip:
  //PORTB &= ~4; //faster than digitalWrite
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWriteFast(7, LOW);
  //send a value to the DAC
  SPI.transfer((dac & 1) <<7 | 0x30 | ((value >> 8) & 0x0F)); //bits 0..3 are bits 8..11 of 12 bit value, bits 4..7 are control data 
  SPI.transfer(value & 0xFF); //bits 0..7 of 12 bit value
    
     
  
  // take the SS pin high to de-select the chip:
  //PORTB |= 4; //faster than digitalWrite 
  digitalWriteFast(7, HIGH);
  SPI.endTransaction();
}
void dacWrite2(int value) {
  //write a 12 bit number to the MCP4921 DAC
  // take the SS pin low to select the chip:
  //PORTB &= ~4; //faster than digitalWrite
  digitalWrite(8, LOW);
  //send a value to the DAC
  SPI.transfer(0x30 | ((value >> 8) & 0x0F)); //bits 0..3 are bits 8..11 of 12 bit value, bits 4..7 are control data 
  SPI.transfer(value & 0xFF); //bits 0..7 of 12 bit value
  // take the SS pin high to de-select the chip:
  //PORTB |= 4; //faster than digitalWrite 
  digitalWrite(8, HIGH);
}
void dacWrite3(int value) {
  //write a 12 bit number to the MCP4921 DAC
  // take the SS pin low to select the chip:
  //PORTB &= ~4; //faster than digitalWrite
  digitalWrite(9, LOW);
  //send a value to the DAC
  SPI.transfer(0x30 | ((value >> 8) & 0x0F)); //bits 0..3 are bits 8..11 of 12 bit value, bits 4..7 are control data 
  SPI.transfer(value & 0xFF); //bits 0..7 of 12 bit value
  // take the SS pin high to de-select the chip:
  //PORTB |= 4; //faster than digitalWrite 
  digitalWrite(9, HIGH);
}
void dacWrite4(int value) {
  //write a 12 bit number to the MCP4921 DAC
  // take the SS pin low to select the chip:
  //PORTB &= ~4; //faster than digitalWrite
  digitalWrite(10, LOW);
  //send a value to the DAC
  SPI.transfer(0x30 | ((value >> 8) & 0x0F)); //bits 0..3 are bits 8..11 of 12 bit value, bits 4..7 are control data 
  SPI.transfer(value & 0xFF); //bits 0..7 of 12 bit value
  // take the SS pin high to de-select the chip:
  //PORTB |= 4; //faster than digitalWrite 
  digitalWrite(10, HIGH);
}
int note1, note2;
int mux0, mux1, mux2, mux3, mux4, mux5, mux6, mux7;
int cvmux0, cvmux1, cvmux2, cvmux3, cvmux4, cvmux5, cvmux6, cvmux7;
float freq1, freq2;
byte v = 1, w = 1;
int sustain =0;
int sustainA =0;

float envelope = 0.0;
float CV0 = 0.0;       // result of reads from potentiometers (yes - it will only be an int, but helps with the casting!)
float CV1 = 0.0;
int CV2 = 0;
float CV3 = 0.0;
float alpha=0.7;
int drive = 0;
double alpha1=0.9;  // initial value for attack
double alpha2=0.9;  // initial value for decay
double alpha3=0.95; // initial value for release


float envelopeA = 0.0;
float alphaA=0.7;
int driveA = 0;
double alphaA1=0.9;  // initial value for attack
double alphaA2=0.9;  // initial value for decay
double alphaA3=0.95; // initial value for release

int velocity1 = 0;

boolean decay = false;
boolean decayA = false;

int dacthing = 0;
int dacthing2 = 0;

float tempvolt = 0.0;
float tempscale = 0.0;
float totaltemp = 0.0;
float avgtemp = 0.0;
int starttime = 0;

void myNoteOn(byte channel, byte note, byte velocity) {
  
  Serial.println(note);
  //freq = 440.00*(pow(2,((note-69.00)/12.00)));
  

  v = v+1;
   if (v>1){
   
v = 1;
  }
  switch (v) {
    case 1:
    velocity1 = velocity;
    note1 = note;
    freq1 = 440.00*(pow(2,(((note+60.00)-69.00)/12.00)));
    //Serial.println(round(freq1));
    //Serial.println(velocity);
    


    //drive=2703;
    drive=(21*velocity1);
    alpha=alpha1; 
    decay = false;


    break;
    
    case 2: 
    note2 = note - 2;
    freq2 = 440.00*(pow(2,((note-69.00)/12.00)));
    break;
    /*
    case 2: 
    note2 = note;
    freq2 = 440.00*(pow(2,((note-69.00)/12.00)));
    Serial.println(round(freq2));

    driveA=4000;
    alphaA=alphaA1; 
    decayA = false;
if(decayA == false && ((envelopeA>3999 && driveA==4000) || (envelopeA<96 && driveA==0))){// if we are in attack phase and we've reached envelope >4000 with drive= 4096, we must be at the end of attack phase
                                                            // so switch to decay...
      decayA = true;                                         // set decay flag
      driveA=sustainA;                                  // drive toward sustain level
      alphaA=alphaA2;                                         // and set 'time constant' alpha2 for decay phase
      }

    break;

    */
  }
 
  
  //freq2 = 0;

//tempbuffer =1; 



}


void myNoteOff(byte channel, byte note, byte velocity) {
    digitalWrite(2, LOW);
  w = w +1;
  if (w>1) {
    w=1;
  }
  switch (w) {
   
    case 1:
    //freq1 = 0;
     
        drive=0;                              // drive towards zero
    alpha=alpha3;                         // set 'time constant' alpha3 for release phase
    

    
    break;
     case 2: 
                            // set 'time constant' alpha3 for release phase

break;
    /*
    case 2: 
    //freq2=0;
       driveA=0;                              // drive towards zero
    alphaA=alphaA3;                         // set 'time constant' alpha3 for release phase
    break;
    */

  }

  

  
   
}

uint8_t numBits(uint32_t num) {
 uint8_t width = 32;                // maximum bit width of number being tested

 while (width) {
    width--;
    if (num & (1 << width)) break;  // look for bit position of first "1" from MSB toward LSB
  }                                 // that eliminates leading zeroes and the number bit width is found
 return (width+1);
 }

void setup()
{
     analogReadResolution(10);

    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    pinMode(17, INPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    //pinMode(0, INPUT);
  
    //pinMode(7, OUTPUT);
     MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(31250);
  //Serial2.begin(31250);
    SPI.begin();
    



   tableAddrWidth = numBits(samplesPerCycle - 1);  // (samples -1) because we index from 0 to (samples -1)

fOut = 1000.0;                                  // set output frequency in Hz
  tuningWord = pow(2, 32) * fOut / sampleRate;    // DDS tuning word for target frequency
   fOut2 = 500.0;                                  // set output frequency in Hz
  tuningWord2 = pow(2, 32) * fOut2 / sampleRate;
}


//int tempbuffer= 0;
void mux() {
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16,  LOW);   
 mux0 = analogRead(17);
 dacWrite1(dacthing, 0);

 //dacWrite2(0);
 digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16,  HIGH);   
 mux1 = analogRead(17);
 //dacthing = 2600;
 //dacWrite1(dacthing, 0);
  dacWrite1(round(2700-envelope), 0);
 // dacWrite1(0, 0);

 digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16,  LOW);   
 mux2 = analogRead(17);
 dacWrite1(4*mux4, 0); //filter cutoff
 
 digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16,  HIGH);   
 mux3 = analogRead(17);
 dacWrite1(4*mux5, 0); //filter resonance
 digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16,  LOW);   
 mux4 = analogRead(17);
  dacWrite1(2225, 0); //offset
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16,  HIGH);   
 mux5 = analogRead(17);
 //dacWrite1(dacthing2, 1); //voice 2 vco
 digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16,  LOW);   
 mux6 = analogRead(17);

 digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16,  HIGH);   
 mux7 = analogRead(17);



 


}


void loop()
{
  
   mux();
   /*
  Serial.println("mux0 ");
Serial.println(mux0);
Serial.println("mux1 ");
Serial.println(mux1);
Serial.println("mux6 ");

Serial.println("mux7 ");
Serial.println(mux7);
*/
//Serial.println(sustain);
     //CV0=analogRead(0);                     // get the attack pole location
     CV0=mux0;
  alpha1=0.999*cos((1023-CV0)/795);
  alpha1=sqrt(alpha1);  

  alphaA1=0.999*cos((1023-CV0)/795);
  alphaA1=sqrt(alphaA1);  
 
 // CV1=analogRead(1);      
 CV1 = mux1;                // get the release pole location
  alpha2=0.999*cos((1023-CV1)/795);
  alpha2=sqrt(alpha2);  
  
  alphaA2=0.999*cos((1023-CV1)/795);
  alphaA2=sqrt(alphaA2); 
  
 // CV2=analogRead(2);                     // get the (integer) sustain level
 CV2 = round((drive/1023))*mux6 + 610;
  sustain=CV2;
  sustainA=CV2<<2;



  //CV3=analogRead(3);                     // get the release pole location (potentially closer to 1.0)
  CV3 = mux7;
  alpha3=0.99999*cos((1023-CV3)/795);
  alpha3=sqrt(alpha3);

  alphaA3=0.99999*cos((1023-CV3)/795);
  alphaA3=sqrt(alphaA3);

MIDI.read();
//dacthing =round(note1*68.26);




//dacthing =note1*68.4; //add temperature sensor thing
/*
if (note1<21) {
  dacthing = round((note1-1)*66.4+10);
}
*/
dacthing = round(note1*83.5);
if (dacthing > 4095) {
  dacthing = dacthing - 83.5;
}

dacthing2 = round(note2*83.5);
if (dacthing2 > 4095) {
  dacthing2 = dacthing - 83.5;
}


//dacWrite1(dacthing, 0);
//dacWrite1(round(2700-envelope), 1);
envelope= ((1.0-alpha)*drive+alpha*envelope);
//dacWrite2(round(2700-envelope));
if (envelope<4.0) {
  envelope = 0.0;
}
dacWrite3(round(freq2*0.97783686));
envelopeA=((1.0-alphaA)*driveA+alphaA*envelopeA);
//dacWrite4(round(envelopeA));
//Serial.println(envelope);




if(decay == false && ((envelope>=(drive-3) && drive==21*velocity1))){// if we are in attack phase and we've reached envelope >4000 with drive= 4096, we must be at the end of attack phase
                                                            // so switch to decay...
      decay = true;                                         // set decay flag
      drive=sustain;                                  // drive toward sustain level
      alpha=alpha2;                                         // and set 'time constant' alpha2 for decay phase
      }




       fOut = freq1;
  tuningWord = pow(2, 32) * fOut / sampleRate;

  fOut2 = freq2;
  tuningWord2 = pow(2, 32) * fOut2 / sampleRate;
  phAcc += tuningWord;
  phInc = phAcc >> (32 - tableAddrWidth);

  phAcc2 += tuningWord2;
  phInc2 = phAcc2 >> (32 - tableAddrWidth);
  // put your main code here, t run repeatedly:
  dacData = (sineData[phInc] >> 1) + (sineData[phInc2] >> 1);
dacWrite1(dacData, 1);
  }
  
