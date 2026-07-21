#include "Stepper.h"

int motor1 = 17;
int motor2 = 19;
int motor3 = 20;
int motor4 = 18;
AccelStepper stepper1(4, motor4, motor2, motor3, motor1);
int currentMotorPosition = 0;

void stepperInit()
{
    stepper1.setMaxSpeed(200.0);
    stepper1.setAcceleration(200.0);
    stepper1.setCurrentPosition(0);
    stepper1.moveTo(2038);
    currentMotorPosition = stepper1.currentPosition();
    stepper1.run();
}

void stepperCheck(int currentButtonState, int lastButtonState)
{
    stepper1.run();
    currentMotorPosition = stepper1.currentPosition();

    if (currentButtonState == 1 && lastButtonState == 1)
    {
        stepper1.stop();
        stepper1.setCurrentPosition(1);
        stepper1.moveTo(-1019);
    }
    if (stepper1.currentPosition() == -1019 && currentButtonState == 0 && lastButtonState == 0)
    {
        stepper1.stop();
        stepper1.setCurrentPosition(0);
    }
    if (currentButtonState == 0 && lastButtonState == 1 && currentMotorPosition == -1019)
    {
        Serial.println(currentMotorPosition);
    }
}