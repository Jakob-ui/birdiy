#ifndef CO2_H
#define CO2_H
#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>

int getCO2();
bool initSensor();

#endif