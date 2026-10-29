#ifndef STEPPER
#define STEPPER

#include <Arduino.h>
#include <AccelStepper.h>

enum class BirdPosition {
    UP = 0,
    DOWN = 1,
    ERROR = 2,
};

bool stepperInit(int buttonPin);
bool stepperCheck(int buttonPin);
void stepperSleep(bool state);
void setBirdPosition(BirdPosition state);

#endif