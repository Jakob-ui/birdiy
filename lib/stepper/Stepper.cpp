#include "Stepper.h"

const int motor1 = 17;
const int motor2 = 19;
const int motor3 = 20;
const int motor4 = 18;
AccelStepper stepper1(AccelStepper::FULL4WIRE, motor4, motor2, motor3, motor1);
float motorSpeed = 400.0;
float motorAccel = 200.0;
// Multiply all motor steps by this amount when using an additional gearbox
const int GEAR_RATIO = 17;
// Motor steps for the up position
const int UP_POSITION = 1040;
// Motor steps for the down position
const int DOWN_POSITION = 0;
// Motor steps for the error position
const int ERROR_POSITION = 300;
// direction and steps to turn to find the endstop
const int HOME_SEARCH_WINDOW = (-4076);
// Position the motor will be in when it hit the end stop
const int HOMING_OFFSET = DOWN_POSITION - 10;

bool stepperInit(int buttonPin) {
  stepper1.setMaxSpeed(motorSpeed);
  stepper1.setMinPulseWidth(2000);
  stepper1.setAcceleration(motorAccel);
  stepperSleep(true);
  return stepperCheck(buttonPin);
}

bool stepperCheck(int buttonPin) {
  stepper1.moveTo(HOME_SEARCH_WINDOW * GEAR_RATIO);
  Serial.println("Init stepper homing");

  while (digitalRead(buttonPin) == 0) {
    stepper1.run();

    if (stepper1.distanceToGo() == 0) {
      Serial.println("Error no stepper reset point found!");
      return false;
    }
  }

  stepper1.stop();
  stepper1.setCurrentPosition(HOMING_OFFSET);
  stepper1.moveTo(DOWN_POSITION);
  stepper1.runToPosition();
  stepperSleep(true);
  return true;
}

void setBirdPosition(BirdPosition state) {
  switch (state) {
  case BirdPosition::UP:
    stepper1.moveTo(UP_POSITION * GEAR_RATIO);
    break;
  case BirdPosition::DOWN:
    stepper1.moveTo(DOWN_POSITION * GEAR_RATIO);
    break;
  case BirdPosition::ERROR:
    stepper1.moveTo(ERROR_POSITION * GEAR_RATIO);
    break;
  }
  stepper1.runToPosition();
  stepperSleep(true);
}

void stepperSleep(bool state) {
  digitalWrite(motor1, !state);
  digitalWrite(motor2, !state);
  digitalWrite(motor3, !state);
  digitalWrite(motor4, !state);
}
