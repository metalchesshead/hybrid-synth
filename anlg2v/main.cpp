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
     0,   256,   512,   768,  1024,  1280,  1536,
  1792,  2048,  2304,  2560,  2816,  3072,  3328,
  3584,  3840,  4096,  4352,  4608,  4864,  5120,
  5376,  5632,  5888,  6144,  6400,  6656,  6912,
  7168,  7424,  7680,  7936,  8192,  8448,  8704,
  8960,  9216,  9472,  9728,  9984, 10240, 10496,
 10752, 11008, 11264, 11520, 11776, 12032, 12288,
 12544, 12800, 13056, 13312, 13568, 13824, 14080,
 14336, 14592, 14848, 15104, 15360, 15616, 15872,
 16128, 16384, 16639, 16895, 17151, 17407, 17663,
 17919, 18175, 18431, 18687, 18943, 19199, 19455,
 19711, 19967, 20223, 20479, 20735, 20991, 21247,
 21503, 21759, 22015, 22271, 22527, 22783, 23039,
 23295, 23551, 23807, 24063, 24319, 24575, 24831,
 25087, 25343, 25599, 25855, 26111, 26367, 26623,
 26879, 27135, 27391, 27647, 27903, 28159, 28415,
 28671, 28927, 29183, 29439, 29695, 29951, 30207,
 30463, 30719, 30975, 31231, 31487, 31743, 31999,
 32255, 32511, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767, 32767, 32767, 32767,
 32767, 32767, 32767, 32767 };


 int lfothingy[256] = {
  935, 1213, 1423, 1665, 1944, 2256, 2604, 2917, 3201, 3543, 3804, 4123, 4432, 4833, 5182, 5480, 5811, 6091, 6369, 6621, 6853, 7105, 7378, 7627, 7884, 8239, 8539, 8865, 9103, 9440, 9765, 10190, 10626, 11347, 11854, 12231, 12485, 12878, 13226, 13530, 13791, 14009, 14445, 14741, 14976, 15298, 15638, 15891, 16185, 16631, 16910, 17105, 17488, 17879, 18212, 18420, 18862, 19228, 19395, 19651, 19958, 20184, 20485, 20952, 21178, 21521, 21970, 22283, 22659, 23014, 23321, 23579, 23826, 24104, 24364, 24572, 24677, 24867, 25006, 25145, 25266, 25301, 25353, 25405, 25440, 25458, 25510, 25510, 25510, 25510, 25510, 25510, 25494, 25424, 25304, 25127, 25025, 24836, 24574, 24397, 24061, 23881, 23540, 23268, 22875, 22403, 21872, 21489, 21002, 20514, 20131, 19584, 19051, 18615, 18070, 17536, 16996, 16338, 15569, 14956, 14441, 14018, 13536, 12816, 12107, 11540, 10834, 10086, 9537, 9137, 8779, 8423, 7885, 7216, 6728, 6445, 6069, 5512, 5139, 4845, 4636, 4427, 4218, 4119, 3980, 3800, 3702, 3584, 3475, 3392, 3345, 3306, 3188, 3166, 3097, 3083, 3083, 3120, 3244, 3364, 3471, 3662, 3802, 3905, 4027, 4115, 4254, 4395, 4638, 4847, 5074, 5387, 5597, 5753, 5979, 6223, 6433, 6642, 6817, 7007, 7216, 7425, 7634, 7895, 8169, 8418, 8665, 8867, 9146, 9333, 9620, 9829, 10038, 10247, 10456, 10690, 10979, 11188, 11408, 11687, 11920, 12278, 12737, 13063, 13290, 13541, 13795, 14303, 14640, 14893, 15251, 15633, 15842, 16060, 16338, 16574, 16723, 16862, 16959, 17253, 17486, 17682, 17768, 17883, 17994, 18128, 18197, 18307, 18389, 18459, 18528, 18597, 18668, 18737, 18807, 18855, 18894, 18963, 19013, 19050, 19120, 19190, 19260, 19277, 19406, 19573, 19697, 19836, 19939, 20010, 20131, 20201, 20270, 20340, 20409, 20480
 };
 int dacData;
 int dacthing;
int i = 0;
int note1;
int iprev = 0;
int jprev = 0;
 uint16_t uartdata[256];
 int16_t lu67[256];
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
  for (int i=0; i<256; i++){
    Serial.print(32768-(lu67[i] + lut[i])/2);
    Serial.print(",");

  }
  Serial.println();
    Serial.println("------------------------------");

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
