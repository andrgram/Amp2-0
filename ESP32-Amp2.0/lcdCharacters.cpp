
#include "lcdCharacters.h"

// Uses 6 characters
void drawSpeaker(LiquidCrystal_I2C lcd, int startX) {
    byte a0[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00010,
        B00111,
        B11111,
        B11111
    };
    byte b0[] = {
        B11111,
        B11111,
        B00111,
        B00010,
        B00000,
        B00000,
        B00000,
        B00000
    };
    byte a1[] = {
        B00000,
        B00000,
        B01100,
        B00010,
        B01001,
        B00100,
        B00010,
        B01010
    };
    byte b1[] = {
        B01010,
        B00010,
        B00100,
        B01001,
        B00010,
        B01100,
        B00000,
        B00000
    };
    byte a2[] {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B10000,
        B10000,
        B10000
    };
    byte b2[] = {
        B10000,
        B10000,
        B10000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
    };
    lcd.createChar(0,a0);
    lcd.createChar(1,a1);
    lcd.createChar(2,a2);
    lcd.createChar(3,b0);
    lcd.createChar(4,b1);
    lcd.createChar(5,b2);

    lcd.setCursor(startX, 0);
    lcd.write(0);
    lcd.setCursor(startX+1, 0);
    lcd.write(1);
    lcd.setCursor(startX+2, 0);
    lcd.write(2);

    lcd.setCursor(startX, 1);
    lcd.write(3);
    lcd.setCursor(startX+1, 1);
    lcd.write(4);
    lcd.setCursor(startX+2, 1);
    lcd.write(5);
}

// Uses 4 characters
void drawLineIn(LiquidCrystal_I2C lcd, int startX) {
    byte a0[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11000,
        B11000,
        B11000
    };
    byte a1[] = {
        B00100,
        B01010,
        B01110,
        B01010,
        B01110,
        B01010,
        B11111,
        B10001
    };
    byte b0[] = {
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11100,
        B01111,
        B00111
    };
    byte b1[] = {
        B10001,
        B10001,
        B10001,
        B11111,
        B01110,
        B11100,
        B11000,
        B10000
    };

    lcd.createChar(0,a0);
    lcd.createChar(1,a1);
    lcd.createChar(3,b0);
    lcd.createChar(4,b1);

    lcd.setCursor(startX, 0);
    lcd.write(0);
    lcd.setCursor(startX+1, 0);
    lcd.write(1);

    lcd.setCursor(startX, 1);
    lcd.write(3);
    lcd.setCursor(startX+1, 1);
    lcd.write(4);
}

// Uses 4 characters
void drawBluetooth(LiquidCrystal_I2C lcd, int startX) {
    byte a0[] = {
        B00001,
        B00001,
        B00001,
        B00001,
        B11001,
        B01101,
        B00111,
        B00011
    };
    byte a1[] = {
        B10000,
        B11000,
        B01100,
        B00110,
        B00011,
        B00110,
        B01100,
        B11000
    };
    byte b0[] = {
        B00011,
        B00111,
        B01101,
        B11001,
        B00001,
        B00001,
        B00001,
        B00001
    };
    byte b1[] = {
        B11000,
        B01100,
        B00110,
        B00011,
        B00110,
        B01100,
        B11000,
        B10000
    };

    lcd.createChar(0,a0);
    lcd.createChar(1,a1);
    lcd.createChar(3,b0);
    lcd.createChar(4,b1);

    lcd.setCursor(startX, 0);
    lcd.write(0);
    lcd.setCursor(startX+1, 0);
    lcd.write(1);

    lcd.setCursor(startX, 1);
    lcd.write(3);
    lcd.setCursor(startX+1, 1);
    lcd.write(4);
}

// Uses 6 characters
void drawVinyl(LiquidCrystal_I2C lcd, int startX) {
    byte a0[] = {
        B00000,
        B00001,
        B00111,
        B01100,
        B01001,
        B11010,
        B10100,
        B10101
    };
    byte a1[] = {
        B00000,
        B11111,
        B00001,
        B11110,
        B00001,
        B01100,
        B11110,
        B10011
    };
    byte a2[] = {
        B00000,
        B00000,
        B11000,
        B01100,
        B00100,
        B10110,
        B01010,
        B01010
    };
    byte b0[] = {
        B10101,
        B10100,
        B11010,
        B01001,
        B01100,
        B00111,
        B00001,
        B00000
    };
    byte b1[] = {
        B10011,
        B11110,
        B01100,
        B00001,
        B11110,
        B00001,
        B11111,
        B00000
    };
    byte b2[] = {
        B01010,
        B01010,
        B10110,
        B00100,
        B01100,
        B11000,
        B00000,
        B00000
    };

    lcd.createChar(0,a0);
    lcd.createChar(1,a1);
    lcd.createChar(2,a2);
    lcd.createChar(3,b0);
    lcd.createChar(4,b1);
    lcd.createChar(5,b2);

    lcd.setCursor(startX, 0);
    lcd.write(0);
    lcd.setCursor(startX+1, 0);
    lcd.write(1);
    lcd.setCursor(startX+2, 0);
    lcd.write(2);

    lcd.setCursor(startX, 1);
    lcd.write(3);
    lcd.setCursor(startX+1, 1);
    lcd.write(4);
    lcd.setCursor(startX+2, 1);
    lcd.write(5);
}

// Uses 6 characters
void drawGoogle(LiquidCrystal_I2C lcd, int startX) {
    byte a0[] = {
        B00000,
        B00001,
        B00111,
        B00110,
        B01100,
        B11100,
        B11000,
        B11000
    };
    byte a1[] = {
        B11111,
        B11111,
        B10000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00001
    };
    byte a2[] = {
        B10000,
        B11000,
        B11110,
        B00110,
        B00000,
        B00000,
        B00000,
        B11111
    };

    byte b0[] {
        B11000,
        B11000,
        B11100,
        B01100,
        B00110,
        B00111,
        B00001,
        B00000
    };
    byte b1[] = {
        B00001,
        B00000,
        B00000,
        B00000,
        B00000,
        B10000,
        B11111,
        B11111
    };
    byte b2[] = {
        B11111,
        B00001,
        B00011,
        B00011,
        B00110,
        B11110,
        B11000,
        B10000
    };

    lcd.createChar(0,a0);
    lcd.createChar(1,a1);
    lcd.createChar(2,a2);
    lcd.createChar(3,b0);
    lcd.createChar(4,b1);
    lcd.createChar(5,b2);

    lcd.setCursor(startX, 0);
    lcd.write(0);
    lcd.setCursor(startX+1, 0);
    lcd.write(1);
    lcd.setCursor(startX+2, 0);
    lcd.write(2);

    lcd.setCursor(startX, 1);
    lcd.write(3);
    lcd.setCursor(startX+1, 1);
    lcd.write(4);
    lcd.setCursor(startX+2, 1);
    lcd.write(5);
}

// Uses 8 characters
void loadVolumeCharacters(LiquidCrystal_I2C lcd) {
    byte v1[] {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111
    };
    byte v2[] {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
    };
    byte v3[] {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111,
        B11111
    };
    byte v4[] {
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111,
        B11111,
        B11111
    };
    byte v5[] {
        B00000,
        B00000,
        B00000,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
    };
    byte v6[] {
        B00000,
        B00000,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
    };
    byte v7[] {
        B00000,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
    };
    byte v8[] {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111
    };
    lcd.createChar(0, v1);
    lcd.createChar(1, v2);
    lcd.createChar(2, v3);
    lcd.createChar(3, v4);
    lcd.createChar(4, v5);
    lcd.createChar(5, v6);
    lcd.createChar(6, v7);
    lcd.createChar(7, v8);
}
