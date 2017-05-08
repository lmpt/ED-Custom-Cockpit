#include "Animator.h"
#include "InOut.h"
#include "moduleBus.h"
#include "UnoJoy.h"

InOut *inOut = new InOut();
int autoHeatSinkTimer = 0; // Track current auto heat sink interval
int autoHeatSinkInterval = 10000; // Amount of time before auto heat sink will redeploy (in cycles)
dataForController_t controllerData;


void setup() {
    //setupUnoJoy();
    controllerData = getBlankDataForController();
}

void loop() {

    if (inOut->stealthModeSwitch) {
        // Stealth switch enabled, set stealth lights and auto heat sink prompt
        inOut->stealthLEDGreen->setAnimation(EASE_HIGH);
        inOut->stealthLEDRed->setAnimation(EASE_LOW);
        inOut->stealthSwitchLED->setAnimation(INSTANT_HIGH);

        inOut->autoHeatSinkLEDRed->setAnimation(EASE_HIGH);
        inOut->autoHeatSinkLEDGreen->setAnimation(PULSE_LOOP);
    } else {
        // Stealth switch disabled, reset stealth and auto heat sink prompt
        inOut->stealthLEDGreen->setAnimation(EASE_LOW);
        inOut->stealthLEDRed->setAnimation(EASE_HIGH);

        inOut->autoHeatSinkLEDRed->setAnimation(EASE_HIGH);
        inOut->autoHeatSinkLEDGreen->setAnimation(EASE_LOW);
        inOut->stealthSwitchLED->setAnimation(INSTANT_LOW);
    }

    if (inOut->autoHeatSinkSwitch) {
        // Auto heat sink enabled
        inOut->autoHeatSinkLEDRed->setAnimation(EASE_LOW);
        inOut->autoHeatSinkLEDGreen->setAnimation(EASE_HIGH);

        // Line Timer for auto heat sink deployment
        if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.1)) {
            inOut->autoHeatSinkStatus1LEDRed->setAnimation(EASE_HIGH);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.2)) {
            inOut->autoHeatSinkStatus2LEDRed->setAnimation(EASE_HIGH);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.3)) {
            inOut->autoHeatSinkStatus3LEDRed->setAnimation(EASE_HIGH);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.4)) {
            inOut->autoHeatSinkStatus4LEDRed->setAnimation(EASE_HIGH);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.5)) {
            inOut->autoHeatSinkStatus1LEDGreen->setAnimation(PULSE_LOOP);
            inOut->autoHeatSinkStatus2LEDGreen->setAnimation(PULSE_LOOP);
            inOut->autoHeatSinkStatus3LEDGreen->setAnimation(PULSE_LOOP);
            inOut->autoHeatSinkStatus4LEDGreen->setAnimation(PULSE_LOOP);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.8)) {
            inOut->autoHeatSinkStatus1LEDGreen->setAnimation(EASE_LOW);
            inOut->autoHeatSinkStatus1LEDRed->setAnimation(EASE_LOW);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.82)) {
            inOut->autoHeatSinkStatus2LEDGreen->setAnimation(EASE_LOW);
            inOut->autoHeatSinkStatus2LEDRed->setAnimation(EASE_LOW);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.84)) {
            inOut->autoHeatSinkStatus3LEDGreen->setAnimation(EASE_LOW);
            inOut->autoHeatSinkStatus3LEDRed->setAnimation(EASE_LOW);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.86)) {
            inOut->autoHeatSinkStatus4LEDGreen->setAnimation(EASE_LOW);
            inOut->autoHeatSinkStatus4LEDRed->setAnimation(EASE_LOW);
        } else if (autoHeatSinkTimer < (autoHeatSinkInterval * 0.9)) {
            // Send controller input
            controllerData.crossOn;
        }

        // Iterate autoHeatSinkTimer
        autoHeatSinkTimer++;
        if (autoHeatSinkTimer > autoHeatSinkInterval) {
            autoHeatSinkTimer = 0;
        }
    } else {
        // Auto heat sink disabled reset timer and LED's
        autoHeatSinkTimer = 0;

        // Don't reset Auto heat sink Prompt LED so previous logic continues, only set switch LED and Status LED's
        inOut->autoHeatSinkSwitchLED->setAnimation(INSTANT_LOW);

        inOut->autoHeatSinkStatus1LEDGreen->setAnimation(EASE_LOW);
        inOut->autoHeatSinkStatus1LEDRed->setAnimation(PULSE);

        inOut->autoHeatSinkStatus2LEDGreen->setAnimation(EASE_LOW);
        inOut->autoHeatSinkStatus2LEDRed->setAnimation(PULSE);

        inOut->autoHeatSinkStatus3LEDGreen->setAnimation(EASE_LOW);
        inOut->autoHeatSinkStatus3LEDRed->setAnimation(PULSE);

        inOut->autoHeatSinkStatus4LEDGreen->setAnimation(EASE_LOW);
        inOut->autoHeatSinkStatus4LEDRed->setAnimation(PULSE);
    }

    // Setup controller data
    controllerData.circleOn = inOut->stealthModeSwitch;

    // Centre controller
    controllerData.leftStickX = 128;
    controllerData.leftStickY = 128;
    controllerData.rightStickX = 128;
    controllerData.rightStickY = 128;

    //setControllerData(controllerData);

    // Iterate Clock for our Inputs and Outputs (this will process animations and get the next output value)
    inOut->clock();
}



