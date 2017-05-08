/*
  InOut.h - Library to manage all input and output devices
  Created by Leo
*/

#ifndef InOut_h
#define InOut_h

#include "Arduino.h"
#include "ModuleBus.h"
#include "Animator.h"

class InOut {
public:
    InOut();

    void clock();

    // Thermal Signature Module -------------------//

    // Stealth Switch and LED's
    bool stealthModeSwitch;
    Animator *stealthLEDRed;
    Animator *stealthLEDGreen;
    Animator *stealthSwitchLED;

    // Auto HeatSink Switch and LED's
    bool autoHeatSinkSwitch;
    Animator *autoHeatSinkLEDRed;
    Animator *autoHeatSinkLEDGreen;
    Animator *autoHeatSinkSwitchLED;

    // Auto HeatSink Binary counter LED's
    Animator *autoHeatSinkStatus1LEDRed;
    Animator *autoHeatSinkStatus1LEDGreen;

    Animator *autoHeatSinkStatus2LEDRed;
    Animator *autoHeatSinkStatus2LEDGreen;

    Animator *autoHeatSinkStatus3LEDRed;
    Animator *autoHeatSinkStatus3LEDGreen;

    Animator *autoHeatSinkStatus4LEDRed;
    Animator *autoHeatSinkStatus4LEDGreen;

    // Sub System Module --------------------------//

    // Nav Module ---------------------------------//

private:
    ModuleBus *_moduleBus;
};

#endif
