#include "header.h"
#include <SPI.h>

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

void dacWrite2(int value, byte dac) {
  //write a 12 bit number to the MCP4921 DAC
  // take the SS pin low to select the chip:
  //PORTB &= ~4; //faster than digitalWrite
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWriteFast(5, LOW);
  //send a value to the DAC
  SPI.transfer((dac & 1) <<7 | 0x30 | ((value >> 8) & 0x0F)); //bits 0..3 are bits 8..11 of 12 bit value, bits 4..7 are control data 
  SPI.transfer(value & 0xFF); //bits 0..7 of 12 bit value
    
     
  
  // take the SS pin high to de-select the chip:
  //PORTB |= 4; //faster than digitalWrite 
  digitalWriteFast(5, HIGH);
  SPI.endTransaction();
}
