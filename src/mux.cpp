#include "header.h"
#include "displaystuff.h"
#include <Arduino.h>
int attackold;
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
delayMicroseconds(5);

digitalWrite(1, HIGH); //CV_INH
digitalWrite(2, HIGH); //A
digitalWrite(3, HIGH); //B
digitalWrite(4, LOW); //C
dacWrite1(0, 0);
delayMicroseconds(5);
digitalWrite(1, LOW); //CV_INH
muxA3 = analogRead(17);
// muxB0 = analogRead(20);
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

if ((muxA0> attackold+10) || muxA0<attackold-10) {
    timethngy = millis();
    ismoving = true;
    if (movebuff ==0){
        oledClearDMA();
        movebuff = 1;
    }
    
    sprintf(bufferthing, "%4d", muxA0);
    dmaPrint(bufferthing, 0, 0);
    Serial.println(bufferthing);
     attackold = muxA0;
}
else if ((movebuff ==1) && (millis() - timethngy >500)) {
    ismoving = false;

}


}