#ifndef BNO055_H
#define BNO055_H
#include "Adafruit_BNO055.h"

extern Adafruit_BNO055 bno;
extern float roll, pitch, yaw; // Roll, pitch and yaw values
extern float gravityX, gravityY, gravityZ; // Gravity force vector values

void initBNO055();
void readRotationVector();
void readGravity();



#endif // BN055_H