#include <Arduino.h>
#include "CO2.h"
#include "Stepper.h"

int Button = 2;
int LED = 15;
int lastButtonState = 0;
bool success = false;
bool sensorInitAttempted = false;
unsigned long lastSensorRetry = 0;
const unsigned long sensorRetryInterval = 5000;

void tryInitSensor()
{
  if (success)
  {
    return;
  }

  if (sensorInitAttempted && millis() - lastSensorRetry < sensorRetryInterval)
  {
    return;
  }

  sensorInitAttempted = true;
  lastSensorRetry = millis();
  success = initSensor();
  if (!success)
  {
    Serial.println("Try to find CO2 sensor");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(Button, INPUT_PULLUP);
  lastButtonState = digitalRead(Button);
  stepperInit();
  pinMode(LED, OUTPUT);
  tryInitSensor();
}

void loop()
{
  tryInitSensor();
  if (success)
  {
    getCO2();
  }
  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, currentButtonState);
  stepperCheck(currentButtonState, lastButtonState);
  lastButtonState = currentButtonState;
}
