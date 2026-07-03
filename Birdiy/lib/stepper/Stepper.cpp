#include "Stepper.h"

int motor1 = 18;
int motor2 = 20;
int motor3 = 19;
int motor4 = 0;
AccelStepper stepper1(4, motor1, motor2, motor3, motor4);
int currentMotorPosition = 0;

void stepperInit()
{
    stepper1.setMaxSpeed(200.0);
    stepper1.setAcceleration(200.0);
    stepper1.setCurrentPosition(0);
    stepper1.moveTo(2038);
}

void stepperCheck(int currentButtonState, int lastButtonState)
{
    stepper1.run();
    currentMotorPosition = stepper1.currentPosition();

    if (currentButtonState == 1 && lastButtonState == 0)
    {
        stepper1.stop();
        stepper1.setCurrentPosition(0);
        stepper1.moveTo(-1019);
    }
    if (currentButtonState == 1 && lastButtonState == 0 && currentMotorPosition == 1019)
    {
        Serial.println(currentMotorPosition);
    }
}