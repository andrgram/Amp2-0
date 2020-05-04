#include "utilities.h"


// Global variables
#pragma region globalVariables

// Hardware timer
hw_timer_t *timer = nullptr;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Sampling variables 
volatile bool updateOutputs = false;         // ISR state change variable. Should change name
const int sampleLength = 300;                // Length of one sample period, in milliseconds

// Volume control variables
uint8_t volume = 0;
uint8_t maxVolume = 192;

// Switching logic variables
Channel *outputChannel = nullptr;
Channel *lastOutputChannel = nullptr;

#pragma endregion globalVariables


// Setup objects
#pragma region objects

// Setup PGA2311
PGA2311 volumeControl(PGA2311_CLK_PIN, PGA2311_MISO_PIN, PGA2311_MOSI_PIN, PGA2311_SS_PIN, PGA2311_MUTE_PIN);

// Setup Rotary encoder
GramRotaryEncoder rotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, 1);

// Setup the lcd display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#pragma endregion objects


// Functions iterating over channels
#pragma region channelFunctions

// Updates the minValue and maxValue of all channels, preparing for measuring the amplitude
void takeMeasurements(Channel (&channels)[nOfChannels]) {
    for (Channel& c : channels) {
        c.takeMeasurement();
    }
}

// Updates the peakToPeak value and averages it over the last 10 values, before setting inputState to whether the average is above the threshold.
void updateInputStates(Channel (&channels)[nOfChannels]) {
    for (Channel& c: channels) {
        c.updateInputState();
    }
}

// Sets output channelnumber HIGH, and all other channels LOW
// This one may take a channel pointer instead of a channelNumber as argument
// I need to find out which will work best with external controls (buttons/remote) first.
void setOutputs(Channel (&channels)[nOfChannels], int channelNumber) {
    for (Channel& c : channels) {
        if (c.getChannelNumber() != channelNumber) c.setLowOutput();
    }
    for (Channel& c : channels) {
        if (c.getChannelNumber() == channelNumber) c.setHighOutput();
    }
}

// Sets all outputs low
void clearOutputs(Channel (&channels)[nOfChannels]) {
    for (Channel& c : channels) {
        c.setLowOutput();
    }
}

// Prints the input states of all the channels. For debug purposes
void printInputStates(Channel (&channels)[nOfChannels]) {
    for (Channel& c : channels) {
        Serial.print("Channel ");
        Serial.print(c.getChannelNumber());
        Serial.print(": \t");
        Serial.println(c.getInputState());
    }
}

// Returns the name of the channel currently outputting. If all is quiet, returns "Dead silent"
String getOutputChannelName(Channel* channelPlaying) {
    if (channelPlaying == nullptr) return "Dead silent";
    else return channelPlaying->getChannelName();
}

// Returns a pointer to the channel to be played from
// If this works, then I may actually have understood pointers!
// It feels a bit dirty that I am using the global variable outputChannel. May swap it for an argument
Channel* chooseOutput(Channel (&channels)[nOfChannels], Channel* channelPlaying) {
    // Counts up number of channels turned on
    int nOfchannelsOn = 0;
    for (Channel& c : channels) {
        nOfchannelsOn += (int)c.getInputState();
    }

    // If none are on, returns the nullptr
    // I´m not sure if best to return nullptr or the one which was playing.
    // Returning nullptr may lead to it going silent when it shouldn´t, but it gives
    // the possibility of it knowing nothing is playing
    if (nOfchannelsOn == 0) return nullptr;

    // If one is on, finds and returns that one
    else if (nOfchannelsOn == 1) {
        for (Channel& c : channels) {
            if (c.getInputState()) return &c;
        }
    }

    // If more than one is on, finds whether any have changed. If no change, returns what it was
    else {
        int nOfChanges = 0;
        // Counts up the number of changes
        for (Channel& c : channels) {
            if (c.getInputState() != c.getPrevInputState()) nOfChanges++;
        }

        // If nothing has changed, do not change channels. Sounds terribly obvious when you write it out like that...
        if (nOfChanges == 0) return channelPlaying;

        // If any channels have turned on, switch to that channel
        // This loop is very weak, since it will return the first one it finds
        // Warning to self: This may have unintended consequences with switching channels too easily!
        else {
            for (Channel& c : channels) {
                // Returns the first channel that has changed state from on to off
                // This is more or less OK, I think
                if (c.getInputState() && !c.getPrevInputState()) return &c;
                
                // If the currently playing channel has switched off, returns the first channel that has input
                if (c.getPrevInputState() && !c.getInputState() && channelPlaying == &c) {
                    for (Channel& cc : channels) {
                        if (cc.getInputState()) return &cc;                        
                    }
                }
            }
        }
    }
    // Just in case return statement
    return channelPlaying;
}

#pragma endregion channelFunctions


// Other functions
#pragma region miscFunctions

// Loop function checking for everything related to the rotary encoder
// It is currently not very, very useful.
void rotaryLoop() {
    ButtonState buttonState = rotaryEncoder.currentButtonState();
    if (buttonState == BUT_PUSHED) {
        volumeControl.toggleMute();
        rotaryEncoder.toggle();
    }
}

void printVolume(int volume, int startX, int startY) {
    loadVolumeCharacters(lcd);
    lcd.setCursor(startX, startY);

    int volumeBars = 5;
    int scaledVolume = int( (float)volume/(float)maxVolume*8*volumeBars);
    int filledBars = scaledVolume / 8;
    int lastBar = scaledVolume % 8;
    for (int i = 0; i < filledBars; i++) {
        lcd.setCursor(startX + i, startY);
        lcd.write(7);
    }
    lcd.setCursor(startX + filledBars, startY);
    if (lastBar > 0) lcd.write(lastBar-1);
    for (int j = filledBars + 1; j < volumeBars; j++) {
        lcd.setCursor(startX + j, startY);
        lcd.write((char)32);
    }
}

void printVolumeAlt(int volume, int startX, int startY) {
    loadVolumeCharacters(lcd);
    int filledBars = int( (float)volume/(float)maxVolume*8);
    for (int i = 0; i < 8; i++) {
        lcd.setCursor(startX + i, startY);
        if (i <= filledBars) lcd.write(i);
        else lcd.write((char)32);
    }
}

#pragma endregion miscFunctions