/*
  Animator.h - Library for animating outputs, uses PWM with shift registers (Module Bus)
  Created by Leo
*/

#include "Arduino.h"
#include "ModuleBus.h"
#include "Animator.h"

#define EASERATE 4; // Speed in witch the Ease Animation plays
#define PULSERATE 1; // Speed in witch the Pulse Animation plays

Animator::Animator(ModuleBus *moduleBus, int moduleId, int outputId, bool invert = false) {
    // setup module data and set default animation state
    this->_moduleBus = moduleBus;
    this->_moduleId = moduleId;
    this->_outputId = outputId;
    this->_animation = INSTANT_LOW;
    this->_lastState = INSTANT_LOW;
    this->_inverted = invert; // Some LED's (like switch LED's) are active LOW, Set to true for Active Low LED's
    this->_clock = 0; // 0 - 1024, this is used to determine the position of the animations time line (used for PWM)
    this->_lightLevel = 0; // 0 - 800, this is the brightness of this LED
    this->_bitAngle = 1; // 1 - 8, used in PWM calculation for LED brightness control, used in PWM and Clock functions

    this->_pulseRise = false; // Used to determine of the Pulse animation is currently rising or lowering
    this->_resolotion = 800; // 0 - 800, the resolution of our light brightness. default 0 - 800
    this->_depth = 16; // Brightness PWM depth, used in PWM calculation for LED brightness
}

void Animator::setAnimation(animationType animation) {
    this->_lastState = this->_animation; // Set Last Animation State
    this->_animation = animation;

    if (animation == PULSE) { // Always Start Pulse animation on a rise (as it is a one time pule animation)
        this->_pulseRise = true;
    }
}

// Clock command, should be called once per loop for software PWM to work
void Animator::clock() {
    calculateLightLevel(); // Run next animation frame

    // Get PWM value and send it to the moduleBus
    this->_moduleBus->setOutput(this->_moduleId, this->_outputId, getPwmValue());

    // Increment Clock, reset if over CLOCKLIMIT
    this->_clock++;
    if (this->_clock >= 1024) {
        this->_clock = 0;
    }

    // Increment bit angle, reset if over brightness depth
    this->_bitAngle++;
    if (this->_bitAngle >= this->_depth) {
        this->_bitAngle = 1;
    }
}

// Calculate PWM value for current Clock and LED brightness level
bool Animator::getPwmValue() {
        if (this->_inverted) {
            return !(this->_lightLevel > ((this->_resolotion / this->_depth) * this->_bitAngle));
        } else {
            return (this->_lightLevel > ((this->_resolotion / this->_depth) * this->_bitAngle));
        }
}

// Run next animation frame and calculate the current LED brightness
void Animator::calculateLightLevel() {
    switch (this->_animation) {
        case EASE_HIGH: // Ease to max brightness
            if (this->_lastState == INSTANT_HIGH) {
                // Last state was INSTANT_HIGH so keep light HIGH
                this->_lightLevel = this->_resolotion;
            } else {
                if (this->_lightLevel < this->_resolotion) {
                    this->_lightLevel += EASERATE;
                }
            }
            break;
        case EASE_LOW: // Ease to min brightness
            if (this->_lastState == INSTANT_LOW) {
                // Last state was INSTANT_LOW so keep light LOW
                this->_lightLevel = 0;
            } else {
                if (this->_lightLevel > 0) {
                    this->_lightLevel -= EASERATE;
                }
            }
            break;
        case PULSE: // Pulse once (ease to high then low)
            if (this->_lightLevel >= this->_resolotion) {
                this->_pulseRise = false; // Pulse over max brightness start lowering pulse brightness
            }

            if (this->_pulseRise) {
                this->_lightLevel += PULSERATE;
            } else {
                this->_lightLevel -= PULSERATE;
            }

            if (this->_lightLevel < 0) {
                this->_lightLevel = 0;
            }
            break;
        case PULSE_LOOP: // Pulse continually (ease to high then low)
            if (this->_lightLevel >= this->_resolotion) {
                this->_pulseRise = false; // Pulse over max brightness start lowering pulse brightness
            } else if (this->_lightLevel <= 0) {
                this->_pulseRise = true; // Pulse under min brightness start increasing pulse brightness
            }

            if (this->_pulseRise) {
                this->_lightLevel += PULSERATE;
            } else {
                this->_lightLevel -= PULSERATE;
            }
            break;
        case INSTANT_HIGH: // Set LED to Max brightness
            this->_lightLevel = this->_resolotion; // Set light to max brightness
            break;
        case INSTANT_LOW: // Set LED to Min brightness
        default:
            this->_lightLevel = 0; // Set light to min brightness
            break;
    }
}
