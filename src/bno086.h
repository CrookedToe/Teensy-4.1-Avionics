#ifndef BNO086_H
#define BNO086_H
#include <SparkFun_BNO08x_Arduino_Library.h>
 
extern BNO08x myIMU;
extern float roll, pitch, yaw; // Roll, pitch and yaw values

void setReports(void);
void initBNO086();
void readRotationVector();


#endif // BNO086_H