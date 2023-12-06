#ifndef BMP390_H
#define BMP390_H

extern float temperature, pressure, altitudeAltimeter, launchpadAltitude;

void initBMP390();
void readBMP390();
void altitudefromlaunchpad();


#endif // BMP390_H