#include <Arduino.h>
#include "CO2.h"
#include "Stepper.h"
#include "zigbeeConnection.h"

const int Button = 2;
const int LED = 15;
bool sensorSuccess = false;
bool zigbeeSuccess = false;
unsigned long lastPublish = 0;
const unsigned long publishInterval = 120000;
bool wasConnected = false;
int co2Threshold = 1000;

//For zigbee connect try if router gets restartet
unsigned long lastZigbeeRetry = 0;
const unsigned long zigbeeRetryInterval = 86400000;

void setup()
{
  Serial.begin(115200);
  pinMode(Button, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);

  stepperInit(Button);

  int retries = 10;

  sensorSuccess = tryInitSensor(10);

  if (!sensorSuccess)
  {
    Serial.println("Error: Co2-Sensor not reachable.");
    showError(300);
    delay(10000);
    ESP.restart();
  }

  zigbeeSuccess = tryInitZigbee(10);

  if (!zigbeeSuccess)
  {
    Serial.println("Zigbee error");
  }
}

void loop()
{
  //Zigbee daily retry in case of router restart
  if (millis() - lastZigbeeRetry >= zigbeeRetryInterval)
  {
    Serial.println("Daily Zigbee-Reconnect-Versuch...");
    zigbeeSuccess = tryInitZigbee(1);
    lastZigbeeRetry = millis();
  }

    if (millis() - lastPublish >= publishInterval)
    {
      uint16_t currentCO2 = getCO2();
      publishData(currentCO2, getTemp());

      if (currentCO2 == 0)
      {
        Serial.println("Warning: I2C Error");
        showError(300);
      }
      else if (currentCO2 >= co2Threshold)
      {
        setBirdPosition(true);
      }
      else
      {
        setBirdPosition(false);
      }

      lastPublish = millis();
    }

  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, !currentButtonState);
}
