#include "Stepper.h"

const int motor1 = 17;
const int motor2 = 19;
const int motor3 = 20;
const int motor4 = 18;
AccelStepper stepper1(4, motor4, motor2, motor3, motor1);
float motorSpeed = 40.0;
float motorAccel = 200.0;
int currentMotorPosition = 0;
int upPosition = 1080;
int downPosition = 1000;


bool stepperInit(int buttonPin)
{
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorAccel);
    stepperSleep(true);
    return stepperCheck(buttonPin);
}

bool stepperCheck(int buttonPin)
{
    stepper1.moveTo(4076);
    Serial.println("Init stepper homing");

    while (digitalRead(buttonPin) == 0)
    {
        stepper1.run();

        if (stepper1.distanceToGo() == 0)
        {
            Serial.println("Error no stepper reset point found!");
            return false;
        }
    }

    stepper1.stop();
    stepper1.setCurrentPosition(0);
    stepper1.moveTo(-upPosition);
    stepper1.runToPosition();
    stepper1.setCurrentPosition(0);
    currentMotorPosition = 0;
    stepperSleep(true);
    return true;
}

void setBirdPosition(bool state)
{
    if (state && stepper1.currentPosition() != downPosition)
    {
        stepper1.moveTo(downPosition);
        stepper1.runToPosition();
        stepperSleep(true);
    }
    else if (!state && stepper1.currentPosition() != 0)
    {
        stepper1.moveTo(0);
        stepper1.runToPosition();
        stepperSleep(true);
    }
}

void stepperSleep(bool state)
{
    digitalWrite(motor1, !state);
    digitalWrite(motor2, !state);
    digitalWrite(motor3, !state);
    digitalWrite(motor4, !state);
}

void showError(int errorPosition)
{
    stepper1.moveTo(errorPosition);
    stepper1.runToPosition();
    stepperSleep(true);
}