#ifndef BNO086_H
#define BNO086_H
#include <SparkFun_BNO08x_Arduino_Library.h>
 
extern BNO08x myIMU;
extern float magZ, magY, magX;
extern float gyroZ, gyroY, gyroX;
extern float accelZ, accelY, accelX;

void initBNO086();
void readBNO086();

#endif // BNO086_H