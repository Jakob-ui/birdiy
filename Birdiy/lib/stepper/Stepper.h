#ifndef STEPPER
#define STEPPER

#include <Arduino.h>
#include <AccelStepper.h>

void stepperInit();
void stepperCheck(int currentButtonState, int lastButtonState);

#endif