/*
  Animator.h - Library for animating outputs, uses PWM with shift registers (Module Bus)
  Created by Leo
*/

#ifndef Animator_h
#define Animator_h

#include "Arduino.h"
#include "ModuleBus.h"

enum animationType {
    INSTANT_HIGH,
    INSTANT_LOW,
    EASE_HIGH,
    EASE_LOW,
    PULSE,
    PULSE_LOOP
};

class Animator {
public:
    Animator(ModuleBus *moduleBus, int moduleId, int outputId, bool invert = false);

    void setAnimation(animationType animation);

    void clock();

private:
    ModuleBus *_moduleBus;
    int _moduleId;
    int _outputId;
    animationType _lastState;
    animationType _animation;
    int _lightLevel;
    int _clock;
    int _bitAngle;
    bool _pulseRise;
    int _resolotion;
    int _depth;
    bool _inverted;

    bool getPwmValue();

    void calculateLightLevel();
};

#endif
