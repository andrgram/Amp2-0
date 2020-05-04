// Utility file containing all the custom lcd characters I might be enticed to draw.
// Every function here overwrites the RAM of custom characters. BEWARE!

#pragma once
#include "utilities.h"

// extern LiquidCrystal_I2C lcd;

// Uses 6 characters
void drawSpeaker(LiquidCrystal_I2C lcd, int startX);

// Uses 4 characters
void drawLineIn(LiquidCrystal_I2C lcd, int startX);

// Uses 4 characters
void drawBluetooth(LiquidCrystal_I2C lcd, int startX);

// Uses 6 characters
void drawVinyl(LiquidCrystal_I2C lcd, int startX);

// Uses 6 characters
void drawGoogle(LiquidCrystal_I2C lcd, int startX);

// Uses 8 characters
void loadVolumeCharacters(LiquidCrystal_I2C lcd);
