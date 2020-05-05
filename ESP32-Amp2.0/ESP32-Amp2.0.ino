/*
* TODO:
* - Rotary encoder for volume control
*   - Volume control finished
*   - Possibilize multiple operations with the same encoder
* - Integration with the PGA2311 volume control
*   - Finished
* - Integration with WiFi
*   - OTA updates
*   - Controllable from Google assistant
*   - Controllable from the web?
* - Bluetooth Integration
*   - Find suitable Bluetooth board (check!) (sorta...)
*   - Communication between ESP and Bluetooth
* - Input buttons?
*   - Enough pins without being creative?
*   - Analog reading with several resistors
* - 16x2 char I2C LCD display
*   - More UI
*   - 
* - Web remote
*   - A remote on the network that can pass channel/volume orders
* - LED light strip/ring
*   - WS2812
* - Channel class
*   - Implement an automatic calibrate offset function to run on start. Or force a nice value.
* 
* - MISC
*   - Can I use a multiplexer on the analogRead?
*   - Probably not neccesary
*/


#include <Arduino.h>
#include <PGA2311.h>
#include <GramRotaryEncoder.h>
#include <LiquidCrystal_I2C.h>

#include "utilities.h"
#include "Channel.h"
#include "lcdCharacters.h"

bool debug = false;



// Possibly renaming this to simply "channels"
// Input channels are good. Filling all the ADC1 channels
// Output channels may be changed based on design simplicity
// (or pin requirements)
// Channel: {inputPin. outputPin, channelNumber, channelName}
Channel channelList[] = {
  Channel(36, 22, 1, "Bluetooth"),
  // {39, 22, 2, "Chromecast"},
  // {34,  1, 3, "Vinyl"},
  // {35,  3, 4, "RCA1"},
  // {32, 21, 5, "RCA2"},
  Channel(33, 19, 6, "AUX")
};

void setup() {

  // Initialize serial communication
  Serial.begin(115200);

  // Timer interrupt for the ESP32
  // Interrupts may not be neccesary now that I am not taking measurements thousands of times per second, but they´re neat and powerful.
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &samplePeriodPassed, true);
  timerAlarmWrite(timer, 1000*sampleLength, true);
  timerAlarmEnable(timer);

  // Initiates the PGA2311 with maxVolume and unmutes it
  volumeControl.setMaxVolume(maxVolume);
  volumeControl.unmute();

  // Initiates the rotary encoder with boundaries and 
  rotaryEncoder.begin();
  rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
  // rotaryEncoder.setBoundaries(0, maxVolume, false);

  // Inititates the LCD on SDA_pin and SCA_pin
  lcd.init(LCD_SDA_PIN, LCD_SCL_PIN);
  lcd.backlight();

  // Setup debug LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Every sample period:
  //  Finds the correct output channel and changes to it
  if (updateOutputs) {
    portENTER_CRITICAL(&timerMux);
    updateOutputs = false;
    portEXIT_CRITICAL(&timerMux);
    
    updateInputStates(channelList);
    outputChannel = chooseOutput(channelList, outputChannel);
    setOutputs(channelList, outputChannel->getChannelNumber());
  }
  // Checks for new max or min readings
  takeMeasurements(channelList);


  // Volume change region
  volume += rotaryEncoder.encoderChanged();
  // volume += volumeChangeFromWebService();   // Example pseudocode for volume change from web service
  if (volume > maxVolume) volume = maxVolume;
  if (volume < 0)         volume = 0;
  volumeControl.setVolume(volume);

  // Mechanism for registering change in the input channel. This may be used to implement some sort of change animation on the display.
  if (outputChannel != lastOutputChannel) {
    lcd.clear();
    lastOutputChannel = outputChannel;
  }

  // LCD print region
  printVolumeAlt(volume);
  lcd.setCursor(8,0);
  if (volume < 100) lcd.print(" ");
  if (volume <  10) lcd.print(" ");
  lcd.print(volume);

  lcd.setCursor(0,1);
  lcd.print(getOutputChannelName(outputChannel));

  rotaryLoop();
}


// ISR function. Runs every sampleLength milliseconds
void IRAM_ATTR samplePeriodPassed() {
  portENTER_CRITICAL_ISR(&timerMux);
  updateOutputs = true;
  portEXIT_CRITICAL_ISR(&timerMux);
}