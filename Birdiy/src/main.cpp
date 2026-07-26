#include <Arduino.h>
#include "CO2.h"
#include "Stepper.h"
#include "zigbeeConnection.h"

int Button = 2;
int LED = 15;
bool sensorSuccess = false;
bool zigbeeSuccess = false;
unsigned long lastPublish = 0;
const unsigned long publishInterval = 10000;
bool wasConnected = false;

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
  pinMode(LED, OUTPUT);

  stepperInit(Button);

  int retries = 10;

  for (int i = 0; i < retries; i++)
  {
    sensorSuccess = initSensor();
    if(sensorSuccess == true){
      break;
    }
    Serial.println("CO2 Init failed, try again... " + String(i) + "x");
    delay(1000);
  }

  if (!sensorSuccess)
  {
    Serial.println("Error: Co2-Sensor not reachable.");
    showError(300);
    while (true);
  }

  for (int i = 0; i < retries; i++)
  {
    zigbeeSuccess = initZigbee();
    if (zigbeeSuccess == true)
    {
      break;
    }
    Serial.println("Zigbee Init failed, try again... " + String(i) + "x");
    delay(1000);
  }
}

void loop()
{
  if (errorCheck())
  {
    if (Zigbee.connected())
    {
      if (!wasConnected)
      {
        Serial.println("Verbunden! Warte auf Abschluss des Interviews...");
        wasConnected = true;
        lastPublish = millis();
      }

      if (millis() - lastPublish >= publishInterval)
      {
        publishData(getCO2(), getTemp());
        lastPublish = millis();
      }
    }
    else
    {
      wasConnected = false;
    }
  }

  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, !currentButtonState);
}
