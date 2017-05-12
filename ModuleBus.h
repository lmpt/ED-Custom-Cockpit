/*
  ModuleBase.h - Library for using Leo's data Bus (shift registers).
  Created by Leo
*/

#ifndef ModuleBus_h
#define ModuleBus_h

#include "Arduino.h"

class ModuleBus {
public:
    ModuleBus(int numberOfModules);

    bool getInput(int module, int inputNumber);

    void setOutput(int module, int outputNumber, bool value);

    void refreshBusCache();

    void clear();

private:
    int _latchPin;
    int _buttonReturnPin;
    int _dataPin;
    int _clockPin;
    bool _inputData[3][8];
    int _inputDeBounce[3][8];
    bool _outputData[3][8];
    int _moduleCount;
    int _inputAngle;
    int _moduleAngle;

    bool checkInput(int module, int inputNumber);
};

#endif
