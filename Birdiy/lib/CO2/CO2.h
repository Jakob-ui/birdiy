#ifndef CO2_H
#define CO2_H

#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>
#include "zigbeeConnection.h"

bool initSensor();
bool initZigbee();
uint16_t getCO2();
float getTemp();

#endif