/*
  ModuleBase.h - Library for using Leo's data Bus (shift registers).
  Created by Leo
*/

#include "Arduino.h"
#include "ModuleBus.h"
#include "Wire.h"

ModuleBus::ModuleBus(int numberOfModules) {
    this->_latchPin = 8;
    this->_buttonReturnPin = 9;
    this->_dataPin = 11;
    this->_clockPin = 12;
    this->_moduleCount = numberOfModules;
    this->_inputAngle = 0; // Value used to store witch Input (0 - 7) we are checking at this time

    // Set pin modes
    pinMode(this->_latchPin, OUTPUT);
    pinMode(this->_buttonReturnPin, INPUT);
    pinMode(this->_dataPin, OUTPUT);
    pinMode(this->_clockPin, OUTPUT);
}

// Get stored input cache
bool ModuleBus::getInput(int module, int inputNumber) {
    return this->_inputData[module][inputNumber];
}

// Set output to cache, will be sent to shift registers the next time the bush cache is refreshed
void ModuleBus::setOutput(int module, int outputNumber, bool value) {
    this->_outputData[module][outputNumber] = value;
}

// Update out button cache (also sets output values to the values stored in the output cache)
void ModuleBus::refreshBusCache() {
    // Loop through each module
    for (int module = 0; module < this->_moduleCount; module++) {
        // Loop through each input on module and update the data bus cache with it's state
        this->_inputData[module][this->_inputAngle] = checkInput(module, this->_inputAngle);
        // TO DO: Add software de-bounce here using the '_inputDeBounce' buffer
    }

    this->_inputAngle++; // Increment Input Angle so next time we refresh bus cache we will get the next button input
    if (this->_inputAngle >= 8) {
        this->_inputAngle = 0;
    }
}

// Set all Input, Input de-bounce and output data to false / 0
void ModuleBus::clear() {
    // Loop through each module
    for (int m = 0; m < this->_moduleCount; m++) {
        // Loop through each input on module and clear it
        for (int i = 0; i < 8; i++) {
            this->_inputData[m][i] = false;
        }
        // Loop through each output on module and clear it
        for (int id = 0; id < 8; id++) {
            this->_inputDeBounce[m][id] = false;
        }

        // Loop through each output on module and clear it
        for (int o = 0; o < 8; o++) {
            this->_outputData[m][o] = false;
        }
    }

    // Flush cache data to the shift registers
    refreshBusCache();
}

// Check input for a given module / Input. Also sets output pins with values in the output cache data
bool ModuleBus::checkInput(int module, int inputNumber) {
    int shiftBuffer = 0; // Used to store out shift buffer value for this check

    // Binary map reference each array value represents the address of a single pin on a shift register
    int binaryMap[8];
    binaryMap[0] = 1;
    binaryMap[1] = 2;
    binaryMap[2] = 4;
    binaryMap[3] = 8;
    binaryMap[4] = 16;
    binaryMap[5] = 32;
    binaryMap[6] = 64;
    binaryMap[7] = 128;

    // Set Latch Low to turn off output while shifting data
    digitalWrite(this->_latchPin, LOW);

    // Loop through each module
    for (int m = this->_moduleCount;
         m >= 0; m--) { // Loop through backwards as bus data is fed backwards
        // Reset shift buffer for output use
        shiftBuffer = 0;

        // Set output register data
        for (int o = 0; o < 8; o++) {
            if (this->_outputData[m][o]) {
                shiftBuffer += binaryMap[o];
            }
        }

        // Flush Output Data
        shiftOut(this->_dataPin, this->_clockPin, MSBFIRST, shiftBuffer);

        // Reset shift buffer for later use
        shiftBuffer = 0;

        // Set input register data
        for (int i = 0; i < 8; i++) {
            if (m == module && i == inputNumber) {
                // Input is value we are checking, set shift buffer value
                shiftBuffer += binaryMap[i];
            }
        }

        // Flush Input Data
        shiftOut(this->_dataPin, this->_clockPin, MSBFIRST, shiftBuffer);
    }

    // Set Latch High to turn output data back on
    digitalWrite(this->_latchPin, HIGH);

    // Return button return data
    return digitalRead(this->_buttonReturnPin);
}


