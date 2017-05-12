/*
  Io.h - Library to manage all input and output devices
  Created by Leo
*/

#include "Arduino.h"
#include "ModuleBus.h"
#include "Animator.h"
#include "InOut.h"

InOut::InOut() {
    this->_moduleBus = new ModuleBus(2);

    // Thermal Signature Module -------------------//
    // Stealth LED's
    this->stealthLEDRed = new Animator(this->_moduleBus, 0, 1); // Gray
    this->stealthLEDGreen = new Animator(this->_moduleBus, 0, 2); // Brown
    this->stealthSwitchLED = new Animator(this->_moduleBus, 0, 3, true); // Black
    this->stealthModeSwitch = false;

    // Auto HeatSink LED's
    this->autoHeatSinkLEDRed = new Animator(this->_moduleBus, 0, 4); // Red
    this->autoHeatSinkLEDGreen = new Animator(this->_moduleBus, 0, 5); // Purple
    this->autoHeatSinkSwitchLED = new Animator(this->_moduleBus, 0, 6, true); // White
    this->autoHeatSinkSwitch = false;

    // Auto HeatSink Binary counter LED's
    this->autoHeatSinkStatus1LEDRed = new Animator(this->_moduleBus, 0, 7); // Grey
    this->autoHeatSinkStatus1LEDGreen = new Animator(this->_moduleBus, 1, 1);

    this->autoHeatSinkStatus2LEDRed = new Animator(this->_moduleBus, 0, 7);
    this->autoHeatSinkStatus2LEDGreen = new Animator(this->_moduleBus, 1, 1);

    this->autoHeatSinkStatus3LEDRed = new Animator(this->_moduleBus, 1, 2);
    this->autoHeatSinkStatus3LEDGreen = new Animator(this->_moduleBus, 1, 3);

    this->autoHeatSinkStatus4LEDRed = new Animator(this->_moduleBus, 1, 4);
    this->autoHeatSinkStatus4LEDGreen = new Animator(this->_moduleBus, 1, 5);

    // Sub System Module --------------------------//

    // Nav Module ---------------------------------//
};

void InOut::clock() {
    // Thermal Signature Module -------------------//
    // Clock LED's
    this->stealthLEDRed->clock();
    this->stealthLEDGreen->clock();
    this->stealthSwitchLED->clock();
    this->autoHeatSinkLEDRed->clock();
    this->autoHeatSinkLEDGreen->clock();
    this->autoHeatSinkSwitchLED->clock();
    this->autoHeatSinkStatus1LEDRed->clock();
    this->autoHeatSinkStatus1LEDGreen->clock();
    this->autoHeatSinkStatus2LEDRed->clock();
    this->autoHeatSinkStatus2LEDGreen->clock();
    this->autoHeatSinkStatus3LEDRed->clock();
    this->autoHeatSinkStatus3LEDGreen->clock();
    this->autoHeatSinkStatus4LEDRed->clock();
    this->autoHeatSinkStatus4LEDGreen->clock();

    // Get Input data
    this->stealthModeSwitch = this->_moduleBus->getInput(0, 1); // Black
    this->autoHeatSinkSwitch = this->_moduleBus->getInput(0, 2); // Brown

    // Sub System Module --------------------------//

    // Nav Module ---------------------------------//

    this->_moduleBus->refreshBusCache(); // reset data input and flush output data
}
