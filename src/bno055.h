#ifndef BNO055_H
#define BNO055_H
#include "Adafruit_BNO055.h"
#include "globalvar.h"
extern Adafruit_BNO055 bno;



void initBNO055();
void bno055readRotationVector();
void bno055readGravity();



#endif // BN055_H