#ifndef CO2_H
#define CO2_H

#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2cScd4x.h>

bool initSensor();
int getCO2();

#endif