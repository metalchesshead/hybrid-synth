#include <MIDI.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define samplesPerCycle 761
uint16_t uartdata[1024]; 
//int sizee;
// data table for one cycle of sine wave
int sineData[samplesPerCycle]  = {
    

 32, 40, 56, 104, 112, 128, 152, 176, 184, 200, 208, 224, 232, 240, 248, 264, 264, 280, 288, 304, 320, 328, 352, 360, 368, 384, 400, 416, 432, 448, 456, 480, 496, 512, 552, 568, 608, 640, 672, 704, 736, 768, 824, 848, 888, 912, 944, 968, 984, 1000, 1008, 1016, 1032, 1040, 1048, 1080, 1120, 1144, 1176, 1216, 1272, 1320, 1360, 1416, 1456, 1504, 1544, 1584, 1624, 1664, 1704, 1736, 1768, 1792, 1808, 1816, 1824, 1832, 1840, 1848, 1856, 1864, 1872, 1880, 1896, 1904, 1912, 1920, 1928, 1936, 1952, 1960, 1976, 2008, 2048, 2088, 2136, 2192, 2240, 2312, 2360, 2416, 2456, 2488, 2512, 2536, 2552, 2560, 2568, 2576, 2592, 2592, 2600, 2616, 2632, 2648, 2656, 2680, 2696, 2704, 2720, 2728, 2736, 2744, 2752, 2760, 2776, 2800, 2816, 2856, 2896, 2960, 3000, 3040, 3096, 3160, 3200, 3248, 3280, 3312, 3328, 3336, 3344, 3352, 3368, 3376, 3392, 3416, 3424, 3432, 3448, 3456, 3472, 3480, 3488, 3504, 3528, 3568, 3616, 3640, 3672, 3728, 3784, 3840, 3904, 3968, 4048, 4112, 4176, 4240, 4280, 4288, 4296, 4312, 4320, 4328, 4328, 4352, 4376, 4392, 4400, 4440, 4456, 4496, 4528, 4560, 4576, 4592, 4608, 4616, 4632, 4632, 4640, 4648, 4656, 4664, 4672, 4680, 4688, 4696, 4704, 4712, 4720, 4728, 4736, 4744, 4752, 4760, 4768, 4776, 4784, 4792, 4800, 4800, 32, 40, 48, 56, 56, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 56, 48, 40, 40, 40, 32, 16, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 72, 72, 64, 64, 64, 64, 64, 64, 56, 40, 24, 64, 64, 64, 64, 64, 64, 72, 72, 72, 72, 72, 72, 72, 72, 72, 88, 96, 104, 112, 128, 128, 128, 136, 144, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 136, 128, 120, 120, 120, 112, 104, 104, 104, 96, 88, 88, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 72, 64, 64, 64, 64, 64, 64, 64, 64, 64, 80, 88, 112, 136, 168, 200, 240, 272, 304, 320, 344, 368, 392, 432, 456, 480, 504, 528, 560, 584, 616, 640, 664, 704, 728, 752, 776, 792, 816, 840, 864, 888, 912, 936, 960, 984, 1016, 1040, 1072, 1120, 1200, 1224, 1248, 1256, 1264, 1280, 1288, 1304, 1328, 1344, 1352, 1376, 1392, 1416, 1432, 1456, 1464, 1472, 1480, 1488, 1496, 1504, 1496, 1496, 1496, 1488, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1480, 1520, 1544, 1560, 1568, 1568, 1568, 1568, 1560, 1544, 1528, 1496, 1464, 1432, 1408, 1384, 1328, 1280, 1248, 1192, 1128, 1088, 1024, 960, 832, 752, 688, 624, 576, 520, 480, 448, 424, 408, 392, 384, 368, 360, 344, 336, 328, 312, 288, 272, 248, 224, 184, 168, 144, 112, 104, 96, 88, 72, 72, 64, 56, 56, 64, 72, 88, 104, 136, 152, 200, 224, 248, 272, 296, 312, 328, 360, 392, 424, 440, 472, 504, 512, 544, 568, 592, 664, 720, 784, 832, 880, 952, 1008, 1064, 1096, 1112, 1120, 1136, 1144, 1152, 1160, 1168, 1192, 1240, 1312, 1376, 1448, 1528, 1592, 1656, 1696, 1768, 1800, 1840, 1856, 1888, 1920, 1952, 1992, 2040, 2088, 2128, 2184, 2248, 2312, 2360, 2424, 2456, 2496, 2520, 2544, 2576, 2600, 2608, 2624, 2632, 2656, 2664, 2672, 2688, 2696, 2728, 2784, 2856, 2936, 3096, 3208, 3336, 3472, 3584, 3704, 3792, 3856, 3928, 3944, 3952, 3960, 3968, 3984, 3992, 4008, 4016, 4024, 4032, 4040, 4048, 4056, 4064, 4072, 4080, 4104, 4136, 4192, 4256, 4368, 4472, 4536, 4576, 4600, 4608, 4616, 4624, 4632, 4640, 4648, 4656, 4664, 4680, 4680, 4680, 4672, 4672, 4664, 4648, 4648, 4640, 4632, 4632, 4624, 4624, 4616, 4608, 4608, 4592, 4584, 4560, 4552, 4528, 4512, 4480, 4448, 4432, 4400, 4384, 4352, 4344, 4288, 4264, 4224, 4176, 4152, 4112, 4080, 4064, 4024, 4016, 3968, 3944, 3920, 3880, 3840, 3808, 3776, 3712, 3544, 3488, 3392, 3304, 3232, 3184, 3120, 3048, 2992, 2896, 2848, 2800, 2768, 2720, 2688, 2640, 2576, 2544, 2504, 2456, 2416, 2384, 2352, 2320, 2280, 2240, 2208, 2176, 2136, 2088, 2032, 1984, 1936, 1880, 1832, 1768, 1712, 1664, 1608, 1576, 1536, 1496, 1432, 1392, 1368, 1328, 1288, 1240, 1200, 1160, 1120, 1080, 1064, 1040, 1000, 976, 928, 904, 824, 792, 744, 712, 688, 672, 648, 616, 592, 568, 536, 528, 520, 472, 448, 432, 400, 392, 376, 376, 352, 328, 304, 272, 240, 200, 160, 144, 128, 120, 96, 72, 56, 48, 40, 32, 24, 24


};

int lfoSaw[1024] = {

        0,     8,    16,    23,    31,    39,    47,
    55,    63,    70,    78,    86,    94,   102,
   109,   117,   125,   133,   141,   148,   156,
   164,   172,   180,   188,   195,   203,   211,
   219,   227,   234,   242,   250,   258,   266,
   273,   281,   289,   297,   305,   313,   320,
   328,   336,   344,   352,   359,   367,   375,
   383,   391,   398,   406,   414,   422,   430,
   438,   445,   453,   461,   469,   477,   484,
   492,   500,   508,   516,   523,   531,   539,
   547,   555,   563,   570,   578,   586,   594,
   602,   609,   617,   625,   633,   641,   648,
   656,   664,   672,   680,   688,   695,   703,
   711,   719,   727,   734,   742,   750,   758,
   766,   773,   781,   789,   797,   805,   813,
   820,   828,   836,   844,   852,   859,   867,
   875,   883,   891,   898,   906,   914,   922,
   930,   938,   945,   953,   961,   969,   977,
   984,   992,  1000,  1008,  1016,  1023,  1031,
  1039,  1047,  1055,  1063,  1070,  1078,  1086,
  1094,  1102,  1109,  1117,  1125,  1133,  1141,
  1148,  1156,  1164,  1172,  1180,  1188,  1195,
  1203,  1211,  1219,  1227,  1234,  1242,  1250,
  1258,  1266,  1273,  1281,  1289,  1297,  1305,
  1313,  1320,  1328,  1336,  1344,  1352,  1359,
  1367,  1375,  1383,  1391,  1398,  1406,  1414,
  1422,  1430,  1438,  1445,  1453,  1461,  1469,
  1477,  1484,  1492,  1500,  1508,  1516,  1523,
  1531,  1539,  1547,  1555,  1563,  1570,  1578,
  1586,  1594,  1602,  1609,  1617,  1625,  1633,
  1641,  1648,  1656,  1664,  1672,  1680,  1688,
  1695,  1703,  1711,  1719,  1727,  1734,  1742,
  1750,  1758,  1766,  1773,  1781,  1789,  1797,
  1805,  1813,  1820,  1828,  1836,  1844,  1852,
  1859,  1867,  1875,  1883,  1891,  1898,  1906,
  1914,  1922,  1930,  1938,  1945,  1953,  1961,
  1969,  1977,  1984,  1992,  2000,  2008,  2016,
  2023,  2031,  2039,  2047,  2055,  2062,  2070,
  2078,  2086,  2094,  2102,  2109,  2117,  2125,
  2133,  2141,  2148,  2156,  2164,  2172,  2180,
  2187,  2195,  2203,  2211,  2219,  2227,  2234,
  2242,  2250,  2258,  2266,  2273,  2281,  2289,
  2297,  2305,  2312,  2320,  2328,  2336,  2344,
  2352,  2359,  2367,  2375,  2383,  2391,  2398,
  2406,  2414,  2422,  2430,  2437,  2445,  2453,
  2461,  2469,  2477,  2484,  2492,  2500,  2508,
  2516,  2523,  2531,  2539,  2547,  2555,  2562,
  2570,  2578,  2586,  2594,  2602,  2609,  2617,
  2625,  2633,  2641,  2648,  2656,  2664,  2672,
  2680,  2687,  2695,  2703,  2711,  2719,  2727,
  2734,  2742,  2750,  2758,  2766,  2773,  2781,
  2789,  2797,  2805,  2812,  2820,  2828,  2836,
  2844,  2852,  2859,  2867,  2875,  2883,  2891,
  2898,  2906,  2914,  2922,  2930,  2937,  2945,
  2953,  2961,  2969,  2977,  2984,  2992,  3000,
  3008,  3016,  3023,  3031,  3039,  3047,  3055,
  3062,  3070,  3078,  3086,  3094,  3102,  3109,
  3117,  3125,  3133,  3141,  3148,  3156,  3164,
  3172,  3180,  3187,  3195,  3203,  3211,  3219,
  3227,  3234,  3242,  3250,  3258,  3266,  3273,
  3281,  3289,  3297,  3305,  3312,  3320,  3328,
  3336,  3344,  3352,  3359,  3367,  3375,  3383,
  3391,  3398,  3406,  3414,  3422,  3430,  3437,
  3445,  3453,  3461,  3469,  3477,  3484,  3492,
  3500,  3508,  3516,  3523,  3531,  3539,  3547,
  3555,  3562,  3570,  3578,  3586,  3594,  3602,
  3609,  3617,  3625,  3633,  3641,  3648,  3656,
  3664,  3672,  3680,  3687,  3695,  3703,  3711,
  3719,  3727,  3734,  3742,  3750,  3758,  3766,
  3773,  3781,  3789,  3797,  3805,  3812,  3820,
  3828,  3836,  3844,  3852,  3859,  3867,  3875,
  3883,  3891,  3898,  3906,  3914,  3922,  3930,
  3937,  3945,  3953,  3961,  3969,  3977,  3984,
  3992,  4000,  3992,  3984,  3977,  3969,  3961,
  3953,  3945,  3937,  3930,  3922,  3914,  3906,
  3898,  3891,  3883,  3875,  3867,  3859,  3852,
  3844,  3836,  3828,  3820,  3812,  3805,  3797,
  3789,  3781,  3773,  3766,  3758,  3750,  3742,
  3734,  3727,  3719,  3711,  3703,  3695,  3687,
  3680,  3672,  3664,  3656,  3648,  3641,  3633,
  3625,  3617,  3609,  3602,  3594,  3586,  3578,
  3570,  3562,  3555,  3547,  3539,  3531,  3523,
  3516,  3508,  3500,  3492,  3484,  3477,  3469,
  3461,  3453,  3445,  3437,  3430,  3422,  3414,
  3406,  3398,  3391,  3383,  3375,  3367,  3359,
  3352,  3344,  3336,  3328,  3320,  3312,  3305,
  3297,  3289,  3281,  3273,  3266,  3258,  3250,
  3242,  3234,  3227,  3219,  3211,  3203,  3195,
  3187,  3180,  3172,  3164,  3156,  3148,  3141,
  3133,  3125,  3117,  3109,  3102,  3094,  3086,
  3078,  3070,  3062,  3055,  3047,  3039,  3031,
  3023,  3016,  3008,  3000,  2992,  2984,  2977,
  2969,  2961,  2953,  2945,  2937,  2930,  2922,
  2914,  2906,  2898,  2891,  2883,  2875,  2867,
  2859,  2852,  2844,  2836,  2828,  2820,  2812,
  2805,  2797,  2789,  2781,  2773,  2766,  2758,
  2750,  2742,  2734,  2727,  2719,  2711,  2703,
  2695,  2687,  2680,  2672,  2664,  2656,  2648,
  2641,  2633,  2625,  2617,  2609,  2602,  2594,
  2586,  2578,  2570,  2562,  2555,  2547,  2539,
  2531,  2523,  2516,  2508,  2500,  2492,  2484,
  2477,  2469,  2461,  2453,  2445,  2437,  2430,
  2422,  2414,  2406,  2398,  2391,  2383,  2375,
  2367,  2359,  2352,  2344,  2336,  2328,  2320,
  2312,  2305,  2297,  2289,  2281,  2273,  2266,
  2258,  2250,  2242,  2234,  2227,  2219,  2211,
  2203,  2195,  2187,  2180,  2172,  2164,  2156,
  2148,  2141,  2133,  2125,  2117,  2109,  2102,
  2094,  2086,  2078,  2070,  2062,  2055,  2047,
  2039,  2031,  2023,  2016,  2008,  2000,  1992,
  1984,  1977,  1969,  1961,  1953,  1945,  1938,
  1930,  1922,  1914,  1906,  1898,  1891,  1883,
  1875,  1867,  1859,  1852,  1844,  1836,  1828,
  1820,  1813,  1805,  1797,  1789,  1781,  1773,
  1766,  1758,  1750,  1742,  1734,  1727,  1719,
  1711,  1703,  1695,  1688,  1680,  1672,  1664,
  1656,  1648,  1641,  1633,  1625,  1617,  1609,
  1602,  1594,  1586,  1578,  1570,  1563,  1555,
  1547,  1539,  1531,  1523,  1516,  1508,  1500,
  1492,  1484,  1477,  1469,  1461,  1453,  1445,
  1438,  1430,  1422,  1414,  1406,  1398,  1391,
  1383,  1375,  1367,  1359,  1352,  1344,  1336,
  1328,  1320,  1313,  1305,  1297,  1289,  1281,
  1273,  1266,  1258,  1250,  1242,  1234,  1227,
  1219,  1211,  1203,  1195,  1188,  1180,  1172,
  1164,  1156,  1148,  1141,  1133,  1125,  1117,
  1109,  1102,  1094,  1086,  1078,  1070,  1063,
  1055,  1047,  1039,  1031,  1023,  1016,  1008,
  1000,   992,   984,   977,   969,   961,   953,
   945,   938,   930,   922,   914,   906,   898,
   891,   883,   875,   867,   859,   852,   844,
   836,   828,   820,   813,   805,   797,   789,
   781,   773,   766,   758,   750,   742,   734,
   727,   719,   711,   703,   695,   688,   680,
   672,   664,   656,   648,   641,   633,   625,
   617,   609,   602,   594,   586,   578,   570,
   563,   555,   547,   539,   531,   523,   516,
   508,   500,   492,   484,   477,   469,   461,
   453,   445,   438,   430,   422,   414,   406,
   398,   391,   383,   375,   367,   359,   352,
   344,   336,   328,   320,   313,   305,   297,
   289,   281,   273,   266,   258,   250,   242,
   234,   227,   219,   211,   203,   195,   188,
   180,   172,   164,   156,   148,   141,   133,
   125,   117,   109,   102,    94,    86,    78,
    70,    63,    55,    47,    39,    31,    23,
    16,     8  
};
float lfoFreq = 0.0;
const float sampleRate = 44100.0;    // sample rate 44.1KHz
float fOut, fOut2;                          // target output frequency (Hz)

volatile int phInc, phInc2, phIncLFO;                  // dds phase increment
volatile unsigned long phAcc, phAcc2, phAccLFO;        // dds phase accumulator
unsigned long tuningWord, tuningWord2, tuningWordLFO;            // dds tuning word (M)

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
  digitalWriteFast(6, LOW);
  //send a value to the DAC
  SPI.transfer((dac & 1) <<7 | 0x30 | ((value >> 8) & 0x0F)); //bits 0..3 are bits 8..11 of 12 bit value, bits 4..7 are control data 
  SPI.transfer(value & 0xFF); //bits 0..7 of 12 bit value
    
     
  
  // take the SS pin high to de-select the chip:
  //PORTB |= 4; //faster than digitalWrite 
  digitalWriteFast(6, HIGH);
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
int mux0A, mux1A, mux2A, mux3A, mux4A, mux5A, mux6A, mux7A;
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

int velocity1, velocity2 = 0;

boolean decay = false;
boolean decayA = false;

int dacthing = 0;
int dacthing2 = 0;

float tempvolt = 0.0;
float tempscale = 0.0;
float totaltemp = 0.0;
float avgtemp = 0.0;
int starttime = 0;

float lfoamp = 1.0;

void myNoteOn(byte channel, byte note, byte velocity) {
  
  Serial.println(note);
  Serial.println("hi");
 
  //freq = 440.00*(pow(2,((note-69.00)/12.00)));
  

  v = v+1;
   if (v>1){
   
v = 1;
  }
  switch (v) {
    case 1:
    velocity1 = velocity;
    note1 = note; //'- 1;
    freq1 = 440.00*(pow(2,(((note+60.00)-69.00)/12.00)));
    //Serial.println(round(freq1));
    //Serial.println(velocity);
    


    //drive=2701;
    drive=(21*velocity1);
    alpha=alpha1; 
    decay = false;


    break;
    
    case 2: 
    velocity2 = velocity;
    note2 = note; //note - 2;
    freq2 = 440.00*(pow(2,((note-69.00)/12.00)));

       // driveA=(21*velocity2);
       driveA = 2700; 
    alphaA=alphaA1; 
    decayA = false;
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
    //digitalWrite(2, LOW);
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


            driveA=0;                              // drive towards zero
    alphaA=alphaA3;                         // set 'time constant' alpha3 for release phase

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
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    pinMode(17, INPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(21, INPUT);
    pinMode(22, INPUT);
    //pinMode(0, INPUT);
  digitalWrite(6, HIGH);
    //pinMode(7, OUTPUT);
     MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(31250);
  //Serial2.begin(31250);
    SPI.begin();
    
  SPI.setMOSI(11);
  SPI.setSCK(13);

  

   tableAddrWidth = numBits(samplesPerCycle - 1);  // (samples -1) because we index from 0 to (samples -1)

fOut = 1000.0;                                  // set output frequency in Hz
  tuningWord = pow(2, 32) * fOut / sampleRate;    // DDS tuning word for target frequency
   fOut2 = 500.0;                                  // set output frequency in Hz
  tuningWord2 = pow(2, 32) * fOut2 / sampleRate;


  //if (analogRead(21)<500)  {
    Serial2.begin(31250);

  //}


    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
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

}


//int tempbuffer= 0;
void mux() {

  

  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16,  LOW);   

     dacWrite1(dacthing, 0);

 dacWrite1(2780, 1);
 mux0 = analogRead(22);
 mux0A = analogRead(23);


   digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16,  LOW);   



     dacWrite1(dacthing, 0);


 dacWrite1(2780, 1);
 mux0 = analogRead(22);
 mux0A = analogRead(23);



   digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16,  LOW);   
  //dacWrite1(dacthing2, 0);//vco2 cv or smth


 mux1 = analogRead(22); 
 mux1A = analogRead(23);

    digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16,  LOW);   
 // dacWrite1(dacthing2, 0);//vco2 cv or smth


 mux1 = analogRead(22); 
 mux1A = analogRead(23);

  //vco1
 //dacWrite1((round(lfoamp/1000)*dacthing), 0);
//dacWrite1(dacthing, 0);
 //dacWrite1(4000, 0);
  //dacWrite1(4000, 1);
 //dacWrite2(0);



 digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16,  HIGH);   
 //dacWrite1(100, 0);
  mux3 = analogRead(22);
  //dacWrite1(mux2*4, 0); //res cv1??
 //dacWrite1((4*mux5 - round(lfoamp/5)), 0); 
 digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16,  LOW);   
   //dacWrite1(2700 - envelopeA, 0); //vca cv1??
 mux2 = analogRead(22);
 mux2A = analogRead(23);
 //dacWrite1((4*mux4 - round(lfoamp/5)), 0); 




 digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16,  HIGH);   
 //dacWrite1(100, 0);
  mux3 = analogRead(22);
  //dacWrite1(mux2*4, 0); //res cv1??
 //dacWrite1((4*mux5 - round(lfoamp/5)), 0); 

   
  //dacWrite1(4000, 1);
  //dacWrite1(2225, 0); //offset
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16,  HIGH);   
  //dacWrite1(0, 1);
  if (mux1<400) {
   dacWrite1(round(1700+(1.5*mux4)*lfoamp/2000), 0); //vcf2 cv
    //dacWrite1(dacData, 1);
  }
  else {
dacWrite1(1000+1.5*mux4, 0);
  }
 mux5 = analogRead(22);
 //dacWrite1(dacthing2, 1); //voice 2 vco
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16,  HIGH);   
 mux4 = analogRead(22);
 //dacWrite1(1000+1.5*mux4, 0); //vcf cv1??
 dacWrite1(0, 0);
 //dacWrite1(4000, 0);
 //dacthing = 2600;
 //dacWrite1(dacData, 1);
  //dacWrite1(round(2700-envelope), 0);
 //dacWrite1(4000, 0);
 //dacWrite1(2500, 1);

 
 digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16,  LOW);  
 dacWrite1(2700 - envelope, 0); //vca2 cv 
  mux3A = analogRead(23);
 mux6 = analogRead(22);
 


 digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16,  HIGH);   
  dacWrite1(mux2*4, 0); //rescv i think
 mux7 = analogRead(22);

 digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16,  HIGH);   
  dacWrite1(0, 0); //res cv1??
  //Serial.println(mux2*4);
 //dacWrite1(100, 0);
  mux3 = analogRead(22);
  

 


}




void loop()
{

if (analogRead(21) >1000) {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}
else if (analogRead(21) >750 && analogRead(21)<1000){
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

}
else if (analogRead(21) >500 && analogRead(21)<750){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);

}
else {

//delay(500);

}
 if (Serial2.available() >=50) {
  for (int i =0; i<25; i++){

    byte high = Serial2.read();
    byte low = Serial2.read();
uartdata[i]= (low << 8) | high;
Serial.println(uartdata[i]);



  }
}
delay(500);
    if (Serial2.available() >=50) {
  for (int i =25; i<50; i++){

    byte high = Serial2.read();
    byte low = Serial2.read();
uartdata[i]= (low << 8) | high;
Serial.println(uartdata[i]);


  }
}
delay(500);

 if (Serial2.available() >=50) {
  for (int i =50; i<75; i++){

    byte high = Serial2.read();
    byte low = Serial2.read();
uartdata[i]= (low << 8) | high;
Serial.println(uartdata[i]);



  }
}
delay(500);

    if (Serial2.available() >=50) {
  for (int i =75; i<100; i++){

    byte high = Serial2.read();
    byte low = Serial2.read();
uartdata[i]= (low << 8) | high;
Serial.println(uartdata[i]);


  }
}
  //Serial.println(Serial2.read());
  
 //display.clearDisplay();
  //int sizee = Serial2.read();
  /*
  for (int i =0; i<1024; i++) {
    
    //while (Serial2.available()==0) {

    //}
    //uartdata[i] = Serial2.read();
  Serial.println(uartdata[i] );
  }

  for (int i =0; i<1024; i++) {
    if (i%8 == 0){
   display.drawPixel(i/8, round(uartdata[i]/52), WHITE);
    display.display();
  }
    // Serial.println(uartdata[i] );
  }
*/


 

 mux();


 //Serial.println(analogRead(21));
  //muxPot();
   //delay(5);
 //dacWrite1((round(lfoamp/1000)*dacthing), 0);
//dacWrite1(dacthing, 0);
// dacWrite1(4000, 0);
  //dacWrite1(2000, 1);
  
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
     CV0=mux0A;
  alpha1=0.999*cos((1023-CV0)/795);
  alpha1=sqrt(alpha1);  

  alphaA1=0.999*cos((1023-CV0)/795);
  alphaA1=sqrt(alphaA1);  
 
 // CV1=analogRead(1);      
 CV1 = mux1A;                // get the release pole location
  alpha2=0.999*cos((1023-CV1)/795);
  alpha2=sqrt(alpha2);  
  
  alphaA2=0.999*cos((1023-CV1)/795);
  alphaA2=sqrt(alphaA2); 
  
 //CV2=mux2A;                     // get the (integer) sustain level
 CV2 = round((drive/1023))*mux2A + 610;
  sustain=CV2;
  sustainA=CV2<<2;



  //CV3=analogRead(3);                     // get the release pole location (potentially closer to 1.0)
  CV3 = mux3A;
  alpha3=0.99999*cos((1023-CV3)/795);
  alpha3=sqrt(alpha3);

  alphaA3=0.99999*cos((1023-CV3)/795);
  alphaA3=sqrt(alphaA3);

MIDI.read();
//dacthing =round(note1*68.26);

//dacthing =round(note1*70.26);
if (note1 >= 24) {
if (mux1>400 && mux1 < 800) {
    dacthing =round(note1*75.26*(0.5 + lfoamp/4000));
}
else {
     dacthing =round(note1*75.00);

}
}
else if (note1>10 && note1<24) {
  if (mux1>400 && mux1 < 800) {
    dacthing =round(note1*75.26*(0.5 + lfoamp/4000));
}
else {
     dacthing =round(note1*73.00 + 50);

}
}
else {
  if (mux1>400 && mux1 < 800) {
    dacthing =round(note1*75.26*(0.5 + lfoamp/4000));
}
else {
     dacthing =round(note1*69.00 + 75);

}
}

//dacthing =note1*68.4; //add temperature sensor thing
/*
if (note1<21) {
  dacthing = round((note1-1)*66.4+10);
}
*/
//dacthing = round(note1*83.5);


dacthing2 = round(note2*75.00 -10);
if (dacthing2 > 4095) {
  dacthing2 = dacthing - 75.00;
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
//Serial.println(mux1);




if(decay == false && ((envelope>=(drive-3) && drive==21*velocity1))){// if we are in attack phase and we've reached envelope >4000 with drive= 4096, we must be at the end of attack phase
                                                            // so switch to decay...
      decay = true;                                         // set decay flag
      drive=sustain;                                  // drive toward sustain level
      alpha=alpha2;                                         // and set 'time constant' alpha2 for decay phase
      }




       fOut = freq1;
       //fOut = 2000;
  tuningWord = pow(2, 32) * fOut / sampleRate;

  fOut2 = freq2;
  //fOut2 = 30;
  tuningWord2 = pow(2, 32) * fOut2 / sampleRate;
  phAcc += tuningWord;
  phInc = phAcc >> (32 - tableAddrWidth);

  phAcc2 += tuningWord2;
  phInc2 = phAcc2 >> (32 - tableAddrWidth);
  // put your main code here, t run repeatedly:
  //dacData = (sineData[phInc] >> 1) + (sineData[phInc2] >> 1);
  
  
  lfoFreq = mux0/5;
  tuningWordLFO = pow(2, 32) * lfoFreq / sampleRate;
  phAccLFO += tuningWordLFO;
  phIncLFO = phAccLFO >> (32 - tableAddrWidth);
  lfoamp = (lfoSaw[phIncLFO] >> 1);
  dacData = (sineData[phInc] >> 1);
//dacWrite1(dacData, 1);

  }
  
