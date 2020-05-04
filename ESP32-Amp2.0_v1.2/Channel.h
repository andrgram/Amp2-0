#pragma once
#include <Arduino.h>


class Channel {
public:
    Channel(int inputPin, int outputPin, int channelNumber, String channelName);

    // Take measurement function. Most useless comment ever!
    void takeMeasurement();
    void updateInputState();
    void calibrateThreshold();

    // Return functions
    bool getInputState()    {return _inputState;}
    bool getPrevInputState(){return _prevInputState;}
    bool getOutputState()   {return _outputState;}
    int getInputPin()       {return _inputPin;}         // Information/debug function. Not to be removed
    int getOutputPin()      {return _outputPin;}        // Information/debug function. Not to be removed
    int getChannelNumber()  {return _channelNumber;}
    String getChannelName() {return _channelName;}
    int getThreshold()      {return _threshold;}        // Probably only a debug function

    // Change state functions
    void setThreshold(int newThreshold);
    void setHighOutput();
    void setLowOutput();

private:
    int _inputPin;
    int _outputPin;
    int _channelNumber;
    String _channelName;
    bool _inputState;
    bool _prevInputState;   // Use this for switching logic
    bool _outputState;      // Is this one unnecessary?

    int _threshold = 5;         // This one should either be set by an automatic calibrarion function which runs on initialization, or in the constructor

    // Measurement variables
    int _maxValue = 0;
    int _minValue = 4095;
    int _peakToPeak = 0;
    static const int averagingLength = 10;
    int averagingBuffer[averagingLength];
    int averagingPosition = 0;
    int _average = 0;

};