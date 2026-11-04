
#include "displaystuff.h"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int dispwaveprev;
int jprev;
void displaystart() {
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
    void drawcurrentwave(int16_t lu67[256], int16_t lut[256]) {
          for (int j = 0; j<256; j++) {
            
        int dispwavebuff = 32768-(lu67[j] + lut[j])/2;
   // Serial.println(eedata[j]);
        if (j%2 == 0 &&j>0){
          display.drawLine(j, round(dispwavebuff/510), jprev, round(dispwaveprev/510), WHITE);


    display.display();
    jprev = j;
    dispwaveprev = dispwavebuff;
    
  }
 
  }
}