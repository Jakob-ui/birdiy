#include <Arduino.h>
#include "CO2.h"
#include "Stepper.h"
#include "zigbeeConnection.h"

int Button = 2;
int LED = 15;
int lastButtonState = 0;
bool sensorSuccess = false;
bool zigbeeSuccess = false;
unsigned long lastPublish = 0;
const unsigned long publishInterval = 10000;

bool errorCheck()
{
  if (!sensorSuccess)
  {
    sensorSuccess = initSensor();
  }

  if (sensorSuccess && !zigbeeSuccess)
  {
    zigbeeSuccess = initZigbee();
  }

  return sensorSuccess && zigbeeSuccess;
}

void setup()
{
  Serial.begin(115200);
  pinMode(Button, INPUT_PULLDOWN);
  lastButtonState = digitalRead(Button);
  stepperInit();
  pinMode(LED, OUTPUT);
  sensorSuccess = initSensor();
  zigbeeSuccess = initZigbee();
}

void loop()
{
  if (errorCheck() && Zigbee.connected())
  {
    if (millis() - lastPublish >= publishInterval)
    {
      publishData(getCO2(), getTemp());
      lastPublish = millis();
    }
  }

  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, !currentButtonState);
  stepperCheck(currentButtonState, lastButtonState);
  lastButtonState = currentButtonState;
}
