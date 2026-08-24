#include "CO2.h"
#include "Stepper.h"
#include "zigbeeConnection.h"
#include <Arduino.h>

const int Button = 2;
const int LED = 15;
bool sensorSuccess = false;
bool zigbeeSuccess = false;
unsigned long lastPublish = 0;
const unsigned long publishInterval = 120000;
bool wasConnected = false;
const int co2Threshold = 1000;
const int co2LowThreshold = 800;
bool firstUpdate = true;

// For zigbee connect try if router gets restarted
unsigned long lastZigbeeRetry = 0;
const unsigned long zigbeeRetryInterval = 86400000;

void setup() {
  Serial.begin(115200);
  pinMode(Button, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);

  stepperInit(Button);

  sensorSuccess = tryInitSensor(10);

  if (!sensorSuccess) {
    Serial.println("Error: Co2-Sensor not reachable.");
    setBirdPosition(BirdPosition::ERROR);
    delay(10000);
    ESP.restart();
  }

  zigbeeSuccess = tryInitZigbee(10);

  if (!zigbeeSuccess) {
    Serial.println("Zigbee error");
  }
  Serial.println("Init done");
}

void loop() {
  // Zigbee daily retry in case of router restart
  if (millis() - lastZigbeeRetry >= zigbeeRetryInterval) {
    Serial.println("Daily Zigbee-Reconnect-Versuch...");
    zigbeeSuccess = tryInitZigbee(1);
    lastZigbeeRetry = millis();
  }

  if (millis() - lastPublish >= publishInterval || firstUpdate) {
    uint16_t currentCO2 = getCO2();
    if (currentCO2 == 0) {
      Serial.println("Warning: No CO2 data yet");
      setBirdPosition(BirdPosition::ERROR);
      delay(1000);
      return;
    }
    publishData(currentCO2, getTemp());
    firstUpdate = false;
    if (currentCO2 >= co2Threshold) {
      setBirdPosition(BirdPosition::DOWN);
    } else if (currentCO2 <= co2LowThreshold) {
      setBirdPosition(BirdPosition::UP);
    }
    lastPublish = millis();
  }

  int currentButtonState = digitalRead(Button);
  digitalWrite(LED, !currentButtonState);
}
