#include <Arduino.h>
#include "CO2.h"
#include "Stepper.h"

int Button = 2;
int LED = 15;
int lastButtonState = 0;
bool success = false;

void setup()
{
  Serial.begin(115200);
  while (success == false)
  {
    success = initSensor();
    Serial.println("Try to find CO2 sensor");
  }
  stepperInit();
  pinMode(Button, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop()
{
  getCO2();
  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, currentButtonState);
  stepperCheck(currentButtonState, lastButtonState);
  lastButtonState = currentButtonState;
}
