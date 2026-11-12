#include "header.h"
#include "displaystuff.h"
#include <Arduino.h>
int A0old, A1old, A2old, A3old;
int B0old, B1old, B2old, B3old;
int C0old, C1old, C2old, C3old;
char bufferthing[4];
int movebuff;
int timethngy;
void mux() {
digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, LOW); //A
digitalWrite(3, LOW); //B
digitalWrite(4, LOW); //C
dacWrite1(2700-envelope, 0);
dacWrite2(dacthing, 0); //vco1_cv
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
muxA0 = analogRead(17);
muxB0 = analogRead(22); //VCF (misc1)
muxC0 = analogRead(16); //vcoshape
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, HIGH); //A
digitalWrite(3, LOW); //B
digitalWrite(4, LOW); //C
dacWrite1(1000 + 1.5*muxB0, 0); //vcf1_cv
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
muxA1 = analogRead(17);
muxB1 = analogRead(22); //res (LFO_Dest)
muxC1 = analogRead(16); //digioscshape
delayMicroseconds(5);


digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, LOW); //A
digitalWrite(3, HIGH); //B
digitalWrite(4, LOW); //C
dacWrite1(muxB1 * 4, 0); //res1+cv
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
muxA2 = analogRead(17);
// muxB0 = analogRead(20);
muxC2 = analogRead(16); //vco_tune
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, HIGH); //A
digitalWrite(3, HIGH); //B
digitalWrite(4, LOW); //C
dacWrite1(1500, 0); //pwm

delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
muxA3 = analogRead(17);
// muxB0 = analogRead(20);
muxC2 = analogRead(16); //digiosc_tune
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, LOW); //A
digitalWrite(3, LOW); //B
digitalWrite(4, HIGH); //C
dacWrite1(0, 0);
dacWrite2(430, 0); //vco1_offset
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
// muxA0 = analogRead(17);
// muxB0 = analogRead(20);
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, HIGH); //A
digitalWrite(3, LOW); //B
digitalWrite(4, HIGH); //C
//dacWrite1(0, 0);
//dacWrite2(430, 0); 
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
// muxA0 = analogRead(17);
// muxB0 = analogRead(20);
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, LOW); //A
digitalWrite(3, HIGH); //B
digitalWrite(4, HIGH); //C
//dacWrite1(0, 0);
//dacWrite2(430, 0); 
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
// muxA0 = analogRead(17);
// muxB0 = analogRead(20);
muxC6 = digitalRead(16);
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, HIGH); //A
digitalWrite(3, HIGH); //B
digitalWrite(4, HIGH); //C
//dacWrite1(0, 0);
//dacWrite2(430, 0); 
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
// muxA0 = analogRead(17);
// muxB0 = analogRead(20);
muxC7 = digitalRead(16);
delayMicroseconds(5);

if ((muxA0> A0old+15) || muxA0<A0old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxA0);
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     A0old = muxA0;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
if ((muxA1> A1old+15) || muxA1<A1old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxA1);
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     A1old = muxA1;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
if ((muxA2> A2old+15) || muxA2<A2old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxA2);
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     A2old = muxA2;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
if ((muxA3> A3old+15) || muxA3<A3old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxA3);
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     A3old = muxA3;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
if ((muxB0> B0old+15) || muxB0<B0old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxB0);
    dmaPrint("VCF:", 0, 0);
    dmaPrint(bufferthing, 0, 1);
    Serial.println(bufferthing);
     B0old = muxB0;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
if ((muxB1> B1old+15) || muxB1<B1old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxB1);
    dmaPrint("Resonance:", 0, 0);
    dmaPrint(bufferthing, 0, 1);
    Serial.println(bufferthing);
     B1old = muxB1;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
if ((muxC0> C0old+15) || muxC0<C0old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    //sprintf(bufferthing, "%4d", muxB1);
    dmaPrint("VCO Shape:", 0, 0);
    if (muxC0<100) {

}
    if (muxC0<100) {
dmaPrint("OFF", 0, 1);
}
else if (muxC0>=100 && muxC0<500)
{
dmaPrint("SAW", 0, 1);
}
else if (muxC0>=500 && muxC0 <750) {
dmaPrint("SQR", 0, 1);

}
else if (muxC0>=750) {
    dmaPrint("TRI", 0, 1);
}
         C0old = muxC0;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}

if ((muxC2> C2old+15) || muxC2<C2old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", int(100*(float)muxC2/1023 - 50));
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     C2old = muxC2;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}

if ((muxC3> C3old+15) || muxC3<C3old-15) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", int(100*(float)muxC3/1023 - 50));
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     C3old = muxC3;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}
}