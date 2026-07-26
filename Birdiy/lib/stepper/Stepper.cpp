#include "Stepper.h"

int motor1 = 17;
int motor2 = 19;
int motor3 = 20;
int motor4 = 18;
AccelStepper stepper1(4, motor4, motor2, motor3, motor1);
int currentMotorPosition = 0;

bool stepperInit(int buttonPin)
{
    stepper1.setMaxSpeed(200.0);
    stepper1.setAcceleration(200.0);
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
    stepper1.moveTo(-1019);
    stepper1.runToPosition();
    stepper1.setCurrentPosition(0);
    currentMotorPosition = 0;
    stepperSleep(true);
    return true;
}

void stepperSleep(bool state)
{
    digitalWrite(motor1, !state);
    digitalWrite(motor2, !state);
    digitalWrite(motor3, !state);
    digitalWrite(motor4, !state);
    Serial.println("motor sleep");
}

void showError(int errorPosition){
    stepper1.moveTo(errorPosition);
    stepper1.runToPosition();
    stepperSleep(true);
}