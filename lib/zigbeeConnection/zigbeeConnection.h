#ifndef ZIGBEECONNECTION_H
#define ZIGBEECONNECTION_H

#include <Zigbee.h>

void publishData(uint16_t co2, float temp);
bool tryInitZigbee(int retries);

#endif