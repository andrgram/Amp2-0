#include "Channel.h"


Channel::Channel(int inputPin, int outputPin, int channelNumber, String channelName) :
    _inputPin{ inputPin },
    _outputPin{ outputPin },
    _channelNumber{ channelNumber },
    _channelName{ channelName }
{
    _inputState = false;
    _outputState = false;
    pinMode(_inputPin, INPUT);
    pinMode(_outputPin, OUTPUT);
    this->setLowOutput();
    // _peakToPeak = 0;
    // _maxValue = 0;
    // _minValue = 4095;
}

// Updates the _minValue and _maxValue if the measurement exceeds any of them
void Channel::takeMeasurement() {
    int reading = analogRead(_inputPin);
    // _inputState += bool(reading > _threshold);

    if (reading > _maxValue) _maxValue = reading;
    if (reading < _minValue) _minValue = reading;
}

// Updates the input state and clears the _minValue and _maxValue to prepare for new measurements.
void Channel::updateInputState() {
    _peakToPeak = _maxValue - _minValue;
    _minValue = 4095;
    _maxValue = 0;

    // Switches the last element in the averaging buffer and updates the average
    _average = _average - (averagingBuffer[averagingPosition] + _peakToPeak) / averagingLength;
    averagingBuffer[averagingPosition] = _peakToPeak;
    averagingPosition = (averagingPosition + 1) % averagingLength;

    // Sets the current and previous input state
    _prevInputState = _inputState;
    _inputState = _average > _threshold;
}

// Calibrates the threshold variable. Not sure that it works...
void Channel::calibrateThreshold() {
    int samples = 100;
    int largestMeasurement = 0;
    for (int i = 0; i < samples; i++) {
        uint32_t startMillis = millis();
        while (millis() - startMillis < 50) {
            this->takeMeasurement();
        }
        this->updateInputState();
        // Will only compare after the averaging buffer is filled
        if (_average > largestMeasurement && i > 10) largestMeasurement = _average;
    }
    _threshold = largestMeasurement;
}

void Channel::setHighOutput() {
    digitalWrite(_outputPin, HIGH);
    _outputState = true;
}

void Channel::setLowOutput() {
    digitalWrite(_outputPin, LOW);
    _outputState = false;
}

void Channel::setThreshold(int newThreshold){
    _threshold = newThreshold;
}