#ifndef STEPPER
#define STEPPER

#include <Arduino.h>
#include <AccelStepper.h>

bool stepperInit(int buttonPin);
bool stepperCheck(int buttonPin);
void stepperSleep(bool state);
void showError(int errorPosition);
void setBirdPosition(bool state);

#endif