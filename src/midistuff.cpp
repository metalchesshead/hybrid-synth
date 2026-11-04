#include "header.h"

// float freq1;
//int note1;
byte v = 1, w = 1;

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
    //freq1 = 440.00*(pow(2,(((note-12+60.00)-69.00)/12.00)));
    freq1 = 440.00*(pow(2,(((note-24+60.00)-69.00)/12.00)));
    tempamp = 0.9;
    //Serial.println(round(freq1));
    //Serial.println(velocity);
    


    //drive=2701;
    drive=(21*velocity1);
    alpha=alpha1; 
    decay = false;

    driveF=(2701);
    alphaF=alpha1F; 
    decayF = false;
    break;

  }
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
   
    tempamp = 0;

        driveF=0;                              // drive towards zero
    alphaF=alpha3F;      
    
    break;

  }
   
}