#ifndef GLOBALVAR_H
#define GLOBALVAR_H

extern float roll, pitch, yaw;
extern float accelX, accelY, accelZ;
extern int rflinktrigger;
extern float temperature, pressure, altitudeAltimeter, groundLevel, rateofChange;
extern float latitude, longitude, altitudeGPS, speed, heading;
extern float bmpTemperature, bmpPressure;
extern float bmpAltitude;
extern float altitudefromlaunchpad;
extern float previousAltitude;
  // globals.h
extern bool thrusterDeployed;
#endif // GLOBALVAR_H
