#include <AccelStepper.h>
#include <Arduino.h>
#include "CO2.h"

int motor1 = 18;
int motor2 = 20;
int motor3 = 19;
int motor4 = 0;
AccelStepper stepper1(4, motor1, motor2, motor3, motor4);
int Button = 2;
int LED = 15;
int lastButtonState = 0;
int currentMotorPosition = 0;
bool success = false;

void motor(bool mode)
{
  if (mode == true)
  {
    digitalWrite(motor1, LOW); 
    digitalWrite(motor2, LOW);
    digitalWrite(motor3, LOW);
    digitalWrite(motor4, LOW);
  }
  else
  {
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, HIGH);
    digitalWrite(motor3, HIGH);
    digitalWrite(motor4, HIGH);
  }
}

void setup()
{
  Serial.begin(115200);
  while (success == false)
  {
    success = initSensor();
    Serial.println("Try to find CO2 sensor");
  }
  pinMode(Button, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(200.0);
  stepper1.moveTo(2038);
  }

void loop()
{
  getCO2();
  stepper1.run();
  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, currentButtonState);
  currentMotorPosition = stepper1.currentPosition();

  if (currentButtonState == 1 && lastButtonState == 0)
  {
    stepper1.stop();
    stepper1.setCurrentPosition(0);
    stepper1.moveTo(-1019);
  }
  if (currentButtonState == 1 && lastButtonState == 0 && currentMotorPosition == 1019){
    Serial.println(currentMotorPosition);
  }
  
  lastButtonState = currentButtonState;
}

