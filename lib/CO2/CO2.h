#ifndef CO2_H
#define CO2_H

#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>
#include "zigbeeConnection.h"

bool tryInitSensor(int retries);
uint16_t getCO2();
float getTemp();

#endif