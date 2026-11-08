
#include "displaystuff.h"

int dispwaveprev;
int jprev;
bool ismoving;

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1


#define OLED_ADDR 0x3C
#define MAX_STRING_LENGTH 32
#define CHARS_COLS_LENGTH 5
DMAMEM uint32_t dmaText[MAX_STRING_LENGTH * 6];
#define DMA_MAX_WORDS 160
DMAMEM uint32_t dmaWords[DMA_MAX_WORDS];
DMAChannel dma;

  static const uint8_t FONTS[][CHARS_COLS_LENGTH] PROGMEM = {
    { 0x00, 0x00, 0x00, 0x00, 0x00 }, // 20 space
    { 0x81, 0x81, 0x18, 0x81, 0x81 }, // 21 !
    { 0x00, 0x07, 0x00, 0x07, 0x00 }, // 22 "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // 23 #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // 24 $
    { 0x23, 0x13, 0x08, 0x64, 0x62 }, // 25 %
    { 0x36, 0x49, 0x55, 0x22, 0x50 }, // 26 &
    { 0x00, 0x05, 0x03, 0x00, 0x00 }, // 27 '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 }, // 28 (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 }, // 29 )
    { 0x14, 0x08, 0x3e, 0x08, 0x14 }, // 2a *
    { 0x08, 0x08, 0x3e, 0x08, 0x08 }, // 2b +
    { 0x00, 0x50, 0x30, 0x00, 0x00 }, // 2c ,
    { 0x08, 0x08, 0x08, 0x08, 0x08 }, // 2d -
    { 0x00, 0x60, 0x60, 0x00, 0x00 }, // 2e .
    { 0x20, 0x10, 0x08, 0x04, 0x02 }, // 2f /
    { 0x3e, 0x51, 0x49, 0x45, 0x3e }, // 30 0
    { 0x00, 0x42, 0x7f, 0x40, 0x00 }, // 31 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 32 2
    { 0x21, 0x41, 0x45, 0x4b, 0x31 }, // 33 3
    { 0x18, 0x14, 0x12, 0x7f, 0x10 }, // 34 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 35 5
    { 0x3c, 0x4a, 0x49, 0x49, 0x30 }, // 36 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 37 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 38 8
    { 0x06, 0x49, 0x49, 0x29, 0x1e }, // 39 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 }, // 3a :
    { 0x00, 0x56, 0x36, 0x00, 0x00 }, // 3b ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 }, // 3c <
    { 0x14, 0x14, 0x14, 0x14, 0x14 }, // 3d =
    { 0x00, 0x41, 0x22, 0x14, 0x08 }, // 3e >
    { 0x02, 0x01, 0x51, 0x09, 0x06 }, // 3f ?
    { 0x32, 0x49, 0x79, 0x41, 0x3e }, // 40 @
    { 0x7e, 0x11, 0x11, 0x11, 0x7e }, // 41 A
    { 0x7f, 0x49, 0x49, 0x49, 0x36 }, // 42 B
    { 0x3e, 0x41, 0x41, 0x41, 0x22 }, // 43 C
    { 0x7f, 0x41, 0x41, 0x22, 0x1c }, // 44 D
    { 0x7f, 0x49, 0x49, 0x49, 0x41 }, // 45 E
    { 0x7f, 0x09, 0x09, 0x09, 0x01 }, // 46 F
    { 0x3e, 0x41, 0x49, 0x49, 0x7a }, // 47 G
    { 0x7f, 0x08, 0x08, 0x08, 0x7f }, // 48 H
    { 0x00, 0x41, 0x7f, 0x41, 0x00 }, // 49 I
    { 0x20, 0x40, 0x41, 0x3f, 0x01 }, // 4a J
    { 0x7f, 0x08, 0x14, 0x22, 0x41 }, // 4b K
    { 0x7f, 0x40, 0x40, 0x40, 0x40 }, // 4c L
    { 0x7f, 0x02, 0x0c, 0x02, 0x7f }, // 4d M
    { 0x7f, 0x04, 0x08, 0x10, 0x7f }, // 4e N
    { 0x3e, 0x41, 0x41, 0x41, 0x3e }, // 4f O
    { 0x7f, 0x09, 0x09, 0x09, 0x06 }, // 50 P
    { 0x3e, 0x41, 0x51, 0x21, 0x5e }, // 51 Q
    { 0x7f, 0x09, 0x19, 0x29, 0x46 }, // 52 R
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // 53 S
    { 0x01, 0x01, 0x7f, 0x01, 0x01 }, // 54 T
    { 0x3f, 0x40, 0x40, 0x40, 0x3f }, // 55 U
    { 0x1f, 0x20, 0x40, 0x20, 0x1f }, // 56 V
    { 0x3f, 0x40, 0x38, 0x40, 0x3f }, // 57 W
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // 58 X
    { 0x07, 0x08, 0x70, 0x08, 0x07 }, // 59 Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // 5a Z
    { 0x00, 0x7f, 0x41, 0x41, 0x00 }, // 5b [
    { 0x02, 0x04, 0x08, 0x10, 0x20 }, // 5c backslash
    { 0x00, 0x41, 0x41, 0x7f, 0x00 }, // 5d ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 }, // 5e ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 }, // 5f _
    { 0x00, 0x01, 0x02, 0x04, 0x00 }, // 60 `
    { 0x20, 0x54, 0x54, 0x54, 0x78 }, // 61 a
    { 0x7f, 0x48, 0x44, 0x44, 0x38 }, // 62 b
    { 0x38, 0x44, 0x44, 0x44, 0x20 }, // 63 c
    { 0x38, 0x44, 0x44, 0x48, 0x7f }, // 64 d
    { 0x38, 0x54, 0x54, 0x54, 0x18 }, // 65 e
    { 0x08, 0x7e, 0x09, 0x01, 0x02 }, // 66 f
    { 0x0c, 0x52, 0x52, 0x52, 0x3e }, // 67 g
    { 0x7f, 0x08, 0x04, 0x04, 0x78 }, // 68 h
    { 0x00, 0x44, 0x7d, 0x40, 0x00 }, // 69 i
    { 0x20, 0x40, 0x44, 0x3d, 0x00 }, // 6a j
    { 0x7f, 0x10, 0x28, 0x44, 0x00 }, // 6b k
    { 0x00, 0x41, 0x7f, 0x40, 0x00 }, // 6c l
    { 0x7c, 0x04, 0x18, 0x04, 0x78 }, // 6d m
    { 0x7c, 0x08, 0x04, 0x04, 0x78 }, // 6e n
    { 0x38, 0x44, 0x44, 0x44, 0x38 }, // 6f o
    { 0x7c, 0x14, 0x14, 0x14, 0x08 }, // 70 p
    { 0x08, 0x14, 0x14, 0x14, 0x7c }, // 71 q
    { 0x7c, 0x08, 0x04, 0x04, 0x08 }, // 72 r
    { 0x48, 0x54, 0x54, 0x54, 0x20 }, // 73 s
    { 0x04, 0x3f, 0x44, 0x40, 0x20 }, // 74 t
    { 0x3c, 0x40, 0x40, 0x20, 0x7c }, // 75 u
    { 0x1c, 0x20, 0x40, 0x20, 0x1c }, // 76 v
    { 0x3c, 0x40, 0x30, 0x40, 0x3c }, // 77 w
    { 0x44, 0x28, 0x10, 0x28, 0x44 }, // 78 x
    { 0x0c, 0x50, 0x50, 0x50, 0x3c }, // 79 y
    { 0x44, 0x64, 0x54, 0x4c, 0x44 }, // 7a z
    { 0x00, 0x08, 0x36, 0x41, 0x00 }, // 7b {
    { 0x00, 0x00, 0x7f, 0x00, 0x00 }, // 7c |
    { 0x00, 0x41, 0x36, 0x08, 0x00 }, // 7d }
    { 0x10, 0x08, 0x08, 0x10, 0x08 }, // 7e ~
    { 0x00, 0x00, 0x00, 0x00, 0x00 }  // 7f
  };

// H character: 5 columns + 1 spacing column
const uint8_t fontH[6] = {
    0x7F,
    0x08,
    0x08,
    0x08,
    0x7F,
    0x00
};

// DMA source: each 32-bit word contains one data byte
DMAMEM uint32_t dmaGlyph[6];

// --------------------------------------------------
// OLED initialization using normal I2C
// --------------------------------------------------
bool dmaPrint(const char *str, uint8_t column, uint8_t page)
{
    const uint16_t MAX_CHARS = 21;

    uint8_t textData[MAX_CHARS * 6];

    uint16_t count = 0;

    while (*str && count < MAX_CHARS * 6)
    {
        uint8_t c = (uint8_t)*str++;

        if (c < 0x20 || c > 0x7F)
            c = '?';

        uint8_t index = c - 0x20;

        for (uint8_t i = 0; i < 5; i++)
        {
            textData[count++] =
                pgm_read_byte(&FONTS[index][i]);
        }

        textData[count++] = 0x00;
    }

    if (count == 0)
        return true;

    if (column + count > 128 || page > 3)
        return false;

    // Set display position using DMA
    uint8_t address[] = {
        0x21,
        column,
        (uint8_t)(column + count - 1),
        0x22,
        page,
        page
    };

    if (!dmaI2CWrite(0x00, address, sizeof(address)))
        return false;

    // Send entire string using DMA
    return dmaI2CWrite(0x40, textData, count);
}
bool dmaI2CWrite(uint8_t control,
                 const uint8_t *data,
                 uint16_t length)
{
    uint16_t words = length + 3;

    if (words > DMA_MAX_WORDS)
        return false;

    // Build complete LPI2C transaction
    dmaWords[0] = 0x0400 | (OLED_ADDR << 1); // START + address
    dmaWords[1] = control;                   // SSD1306 control byte

    for (uint16_t i = 0; i < length; i++)
        dmaWords[i + 2] = data[i];

    dmaWords[words - 1] = 0x0200;            // STOP

    arm_dcache_flush(dmaWords, words * sizeof(uint32_t));

    // Prepare LPI2C
    LPI2C1_MDER = 0;

    LPI2C1_MCR |= LPI2C_MCR_RTF | LPI2C_MCR_RRF;

    LPI2C1_MSR = 0x1F00;

    LPI2C1_MFCR = 0;

    // Configure DMA
    dma.sourceBuffer(dmaWords, words * sizeof(uint32_t));

    dma.destination(
        (volatile uint32_t&)LPI2C1_MTDR
    );

    dma.transferSize(4);

    dma.triggerAtHardwareEvent(DMAMUX_SOURCE_LPI2C1);

    dma.clearComplete();
    dma.clearError();

    // DMA sends the entire transaction
    dma.enable();

    LPI2C1_MDER = LPI2C_MDER_TDDE;

    uint32_t timeout = micros();

    while (!dma.complete() && !dma.error())
    {
        if (micros() - timeout > 200000)
        {
            LPI2C1_MDER = 0;
            dma.disable();
            return false;
        }
    }

    LPI2C1_MDER = 0;

    if (dma.error())
    {
        dma.disable();
        return false;
    }

    // Wait until STOP has actually completed
    timeout = micros();

    while (LPI2C1_MSR & LPI2C_MSR_MBF)
    {
        if (micros() - timeout > 200000)
        {
            dma.disable();
            return false;
        }
    }

    dma.disable();

    // Check for I2C NACK
    if (LPI2C1_MSR & LPI2C_MSR_NDF)
    {
        LPI2C1_MSR = LPI2C_MSR_NDF;
        return false;
    }

    return true;
}
bool drawPixelDMA(uint8_t x, uint8_t y, bool color = true)
{
    if (x >= 128 || y >= 32)
        return false;

    uint8_t page = y / 8;
    uint8_t bit = y % 8;

    // Set the pixel bit
    uint8_t pixelData = color ? (1 << bit) : 0;

    // Set display position
    uint8_t address[] = {
        0x21, x, x,
        0x22, page, page
    };

    if (!dmaI2CWrite(0x00, address, sizeof(address)))
        return false;

    // Write pixel data
    return dmaI2CWrite(0x40, &pixelData, 1);
}
bool oledInitDMA()
{
    const uint8_t init[] = {
        0xAE,
        0xD5, 0x80,
        0xA8, 0x1F,
        0xD3, 0x00,
        0x40,
        0x8D, 0x14,
        0x20, 0x00,
        0xA1,
        0xC8,
        0xDA, 0x02,
        0x81, 0x8F,
        0xD9, 0xC2,
        0xDB, 0x40,
        0xA4,
        0xA6,
        0x2E,
        0xAF
    };

    return dmaI2CWrite(0x00, init, sizeof(init));
}

// --------------------------------------------------
// Clear OLED using normal I2C
// --------------------------------------------------

bool oledClearDMA()
{
    uint8_t zeros[128] = {0};

    for (uint8_t page = 0; page < 4; page++)
    {
        uint8_t address[] = {
            0x21, 0, 127,
            0x22, page, page
        };

        // Set page and column
        if (!dmaI2CWrite(0x00, address, sizeof(address)))
            return false;

        // Clear page using DMA
        if (!dmaI2CWrite(0x40, zeros, sizeof(zeros)))
            return false;
    }

    return true;
}

// --------------------------------------------------
// Set character position using normal I2C
// --------------------------------------------------



// --------------------------------------------------
// Send six character bytes using DMA
// --------------------------------------------------

bool sendCharacterDMA()
{
    // Prepare DMA data
    for (int i = 0; i < 6; i++)
    {
        dmaGlyph[i] = fontH[i];
    }

    arm_dcache_flush(dmaGlyph, sizeof(dmaGlyph));

    // Disable DMA requests
    LPI2C1_MDER = 0;

    // Flush FIFOs
    LPI2C1_MCR |= LPI2C_MCR_RTF | LPI2C_MCR_RRF;

    // Clear status
    LPI2C1_MSR = 0x1F00;

    // TX/RX watermark = 0
    LPI2C1_MFCR = 0;

    // Configure DMA
    dma.sourceBuffer(dmaGlyph, sizeof(dmaGlyph));

    dma.destination(
        (volatile uint32_t&)LPI2C1_MTDR
    );

    // Each transfer writes one 32-bit word
    dma.transferSize(4);

    dma.triggerAtHardwareEvent(DMAMUX_SOURCE_LPI2C1);

    dma.clearComplete();
    dma.clearError();

    // START + OLED address
    LPI2C1_MTDR = 0x0400 | (OLED_ADDR << 1);

    uint32_t timeout = micros();

    while (!(LPI2C1_MSR & LPI2C_MSR_TDF))
    {
        if (micros() - timeout > 100000)
            return false;
    }

    // SSD1306 DATA control byte
    LPI2C1_MTDR = 0x0040;

    // Enable DMA
    dma.enable();

    LPI2C1_MDER = LPI2C_MDER_TDDE;

    // Wait for all six DMA transfers
    timeout = micros();

    while (!dma.complete() && !dma.error())
    {
        if (micros() - timeout > 100000)
        {
            LPI2C1_MDER = 0;
            dma.disable();
            return false;
        }
    }

    LPI2C1_MDER = 0;

    if (dma.error())
    {
        dma.disable();
        return false;
    }

    // Wait for FIFO space
    timeout = micros();

    while (!(LPI2C1_MSR & LPI2C_MSR_TDF))
    {
        if (micros() - timeout > 100000)
        {
            dma.disable();
            return false;
        }
    }

    // STOP
    LPI2C1_MTDR = 0x0200;

    // Wait for transaction completion
    timeout = micros();

    while (LPI2C1_MSR & LPI2C_MSR_MBF)
    {
        if (micros() - timeout > 100000)
        {
            dma.disable();
            return false;
        }
    }

    dma.disable();

    return true;
}
void drawLineDMA(int x0, int y0, int x1, int y1, bool color = true)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        drawPixelDMA(x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
// void displaystart() {
//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;); // Don't proceed, loop forever
//   }
//     display.clearDisplay();

//     display.setTextSize(1);
//     display.setTextColor(WHITE);
//     display.setCursor(0, 0);
//     display.println("Booting...");
//     display.display();
//     delay(1000);
//     display.clearDisplay();
// }
    void drawcurrentwave(int16_t lu67[256], int16_t lut[256]) {
          for (int j = 0; j<256; j++) {
            
        int dispwavebuff = 32768-(lu67[j] + lut[j])/2;
       // int dispwavebuff = 32768-(lu67[j]);
   // Serial.println(eedata[j]);
        if (j%2 == 0 &&j>0){
            drawPixelDMA(j/2, dispwavebuff/1024);
         // display.drawLine(j, round(dispwavebuff/510), jprev, round(dispwaveprev/510), WHITE);
//drawLineDMA(j/2, round(dispwavebuff/1024), jprev, round(dispwaveprev/1024));

    //display.display();
    jprev = j/2;
    dispwaveprev = dispwavebuff;
    
  }
 
  }
}

//   void attack() {
//     display.clearDisplay();
//     display.setCursor(0, 0);
//     Serial.println(muxA0);
//     display.print(muxA0);
//     display.display();
//   }

//   void homescreen() {
//     display.clearDisplay();
//     display.setCursor(0, 0);
//     display.print("homescreen");
//     display.display();



//   }