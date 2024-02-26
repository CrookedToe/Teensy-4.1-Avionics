#ifndef GLOBALVAR_H
#define GLOBALVAR_H

extern float roll, pitch, yaw;
extern float gravityX, gravityY, gravityZ;
extern int rflinktrigger;
extern float temperature, pressure, altitudeAltimeter, groundLevel;
extern float latitude, longitude, altitudeGPS, speed, heading;
extern float bmpTemperature, bmpPressure;
extern float bmpAltitude;
extern float altitudefromlaunchpad;
extern float previousAltitude;
extern bool thrusterDeployed;
#endif // GLOBALVAR_H
