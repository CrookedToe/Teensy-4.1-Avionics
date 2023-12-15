#ifndef BNO086_H
#define BNO086_H
#include <SparkFun_BNO08x_Arduino_Library.h>
#include "global.h"

extern BNO08x myIMU;


void setReports(void);
void initBNO086();
void bno086readRotationVector();
void bno086readGravity();


#endif // BNO086_H