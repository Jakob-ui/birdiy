#include <Arduino.h>
#include "CO2.h"
#include "Stepper.h"

int Button = 2;
int LED = 15;
int lastButtonState = 0;
bool success = false;
bool zigbeeSuccess = false;

void setup()
{
  Serial.begin(115200);
  pinMode(Button, INPUT_PULLDOWN);
  lastButtonState = digitalRead(Button);
  stepperInit();
  pinMode(LED, OUTPUT);
  success = initSensor();
  zigbeeSuccess = initZigbee();
}

void loop()
{
  if (success)
  {
    getCO2();
  }
  else
  {
    success = initSensor();
    if (success)
    {
      zigbeeSuccess = initZigbee();
    }
  }

  if (success && !zigbeeSuccess)
  {
    zigbeeSuccess = initZigbee();
  }

  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, !currentButtonState);
  stepperCheck(currentButtonState, lastButtonState);
  lastButtonState = currentButtonState;
}
