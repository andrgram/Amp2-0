#pragma once
// External libraries
#include <Arduino.h>
#include <PGA2311.h>
#include <GramRotaryEncoder.h>
#include <LiquidCrystal_I2C.h>
// Local libraries
#include "Channel.h"
#include "lcdCharacters.h"

// Pin defines
#define PGA2311_CLK_PIN     19
#define PGA2311_MISO_PIN    23  // This can be anything. It is NC on the PGA2311_MISO_PIN
#define PGA2311_MOSI_PIN    18
#define PGA2311_SS_PIN      5
#define PGA2311_MUTE_PIN    21

#define ROTARY_ENCODER_A_PIN 25
#define ROTARY_ENCODER_B_PIN 26
#define ROTARY_ENCODER_BUTTON_PIN 27

#define LCD_SDA_PIN 15
#define LCD_SCL_PIN 4


// Global variables
#pragma region globalVariables

// Hardware timer
extern hw_timer_t * timer;
extern portMUX_TYPE timerMux;

// Sampling variables
extern volatile bool updateOutputs;  // The boolean for the ISR to change
extern const int sampleLength;      // Length of one sample period, in milliseconds

// Volume control variables
extern uint8_t volume;
extern uint8_t maxVolume;

// Switching logic variables
extern Channel *outputChannel;
extern Channel *lastOutputChannel;

// Debug LED
const int ledPin = 2;

const int nOfChannels = 2;

#pragma endregion globalVariables


// Setup objects
#pragma region objects

// Setup PGA2311
extern PGA2311 volumeControl;

// Setup Rotary encoder
extern GramRotaryEncoder rotaryEncoder;

// Setup the lcd display
extern LiquidCrystal_I2C lcd;

#pragma endregion objects


// Functions iterating over channels
#pragma region channelFunctions

void takeMeasurements(Channel (&channels)[nOfChannels]);

void updateInputStates(Channel (&channels)[nOfChannels]);

void setOutputs(Channel (&channels)[nOfChannels], int channelNumber);

void clearOutputs(Channel (&channels)[nOfChannels]);

void printInputStates(Channel (&channels)[nOfChannels]);

String getOutputChannelName(Channel *channelPlaying);

Channel* chooseOutput(Channel (&channels)[nOfChannels], Channel *channelPlaying);

#pragma endregion channelFunctions


// Other functions
#pragma region miscFunctions


// The ISR function
void IRAM_ATTR samplePeriodPassed();

// Looping in the rotary shit
void rotaryLoop();

// Two function for printing the volume to the lcd. I think I prefer the second one
void printVolume(int volume, int startX = 0, int startY = 0);
void printVolumeAlt(int volume, int startX = 0, int startY = 0);

#pragma endregion miscFunctions