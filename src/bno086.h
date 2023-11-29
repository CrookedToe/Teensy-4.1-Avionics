#ifndef BNO086_H
#define BNO086_H
#include <SparkFun_BNO08x_Arduino_Library.h>
 
extern BNO08x myIMU;
extern float quatI, quatJ, quatK, quatReal;  // Add quaternion variables
extern float linaccelZ, linaccelY, linaccelX;
extern float MagX, MagY, MagZ;

void initBNO086();
bool readRotationVector();
bool readlinearAccelerometer();
bool readMagnetometer();
bool readGyroIntegratedRotationVector();

void readBNO086();

#endif // BNO086_H