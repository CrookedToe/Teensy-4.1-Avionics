#ifndef ULTIMATEGPS_H
#define ULTIMATEGPS_H

#include <Arduino.h>

extern float latitude, longitude, altitudeGPS, speed, heading;

void initUltimateGPS();
void readUltimateGPS();
void printGPSData();
void updateGPSData();

#endif // ULTIMATEGPS_H