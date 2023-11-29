/*
  Using the BNO08x IMU

  This example shows how to output the parts of the calibrated gyro.

  By: Nathan Seidle
  SparkFun Electronics
  Date: December 21st, 2017
  SparkFun code, firmware, and software is released under the MIT License.
	Please see LICENSE.md for further details.

  Originally written by Nathan Seidle @ SparkFun Electronics, December 28th, 2017

  Adjusted by Pete Lewis @ SparkFun Electronics, June 2023 to incorporate the
  CEVA Sensor Hub Driver, found here:
  https://github.com/ceva-dsp/sh2

  Also, utilizing code from the Adafruit BNO08x Arduino Library by Bryan Siepert
  for Adafruit Industries. Found here:
  https://github.com/adafruit/Adafruit_BNO08x

  Also, utilizing I2C and SPI read/write functions and code from the Adafruit
  BusIO library found here:
  https://github.com/adafruit/Adafruit_BusIO

  Hardware Connections:
  Plug the sensor into IoT RedBoard via QWIIC cable.
  Serial.print it out at 115200 baud to serial monitor.

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/22857
*/

#include <Wire.h>
#include <bno086.h>
#include "SparkFun_BNO08x_Arduino_Library.h" // CTRL+Click here to get the library: http://librarymanager/All#SparkFun_BNO08x

BNO08x myIMU;
float quatI, quatJ, quatK, quatReal;  // Add quaternion variables
float linaccelZ, linaccelY, linaccelX;
float MagX, MagY, MagZ;
float gyroX, gyroY, gyroZ;


#define ROTATION_VECTOR_TIMEOUT 5000
#define ACCELEROMETER_TIMEOUT 5000


void setReports(void) {
  Serial.println("Setting desired reports");

  if (myIMU.enableRotationVector(10) == true) {  // Enable rotation vector report at 50Hz
    Serial.println(F("Rotation vector enabled"));
  } else {
    Serial.println("Could not enable rotation vector");
  }

  if (myIMU.enableLinearAccelerometer(10) == true) {
    Serial.println(F("Accelerometer enabled"));
  } else {
    Serial.println("Could not enable Accelerometer");
  }
  if (myIMU.enableGyroIntegratedRotationVector(10) == true) {
    Serial.println(F("Gyro Calibrated"));
  } else {
    Serial.println("Could not calibrate Gyro");
  }
  // Enable Magnetic Field report
  if (myIMU.enableMagnetometer(10) == true) {  // Enable at 50Hz
    Serial.println(F("Magnetic Field enabled"));
  } else {
    Serial.println("Could not enable Magnetic Field");
  }


}

void initBNO086() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("BNO08x Read Example");
  delay(100);
  Wire.begin();
  delay(100);

  int attempts = 0;
  while (myIMU.begin() == false) {
    attempts++;
    if (attempts > 10) {
      Serial.println("BNO08x not detected after multiple attempts. Check your jumpers and the hookup guide. Freezing...");
      while (1);
    }
    Serial.println("BNO08x not detected. Retrying...");
    delay(100);
  }
  Serial.println("BNO08x found!");

  setReports();
}

// Here is where you define the sensor outputs you want to receive


bool readRotationVector() {
  unsigned long startTime = millis();
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_ROTATION_VECTOR) {
    if (millis() - startTime > ROTATION_VECTOR_TIMEOUT) {
      Serial.println("Timeout waiting for rotation vector event");
      return false;
    }
  }
  quatI = myIMU.getQuatI();
  quatJ = myIMU.getQuatJ();
  quatK = myIMU.getQuatK();
  quatReal = myIMU.getQuatReal();
  return true;
}

void convertQuaternionToEuler(float quatI, float quatJ, float quatK, float quatReal, float& roll, float& pitch, float& yaw) {
  // roll (x-axis rotation)
  double sinr_cosp = 2 * (quatReal * quatI + quatJ * quatK);
  double cosr_cosp = 1 - 2 * (quatI * quatI + quatJ * quatJ);
  roll = atan2(sinr_cosp, cosr_cosp);

  // pitch (y-axis rotation)
  double sinp = 2 * (quatReal * quatJ - quatK * quatI);
  if (abs(sinp) >= 1)
    pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
  else
    pitch = asin(sinp);

  // yaw (z-axis rotation)
  double siny_cosp = 2 * (quatReal * quatK + quatI * quatJ);
  double cosy_cosp = 1 - 2 * (quatJ * quatJ + quatK * quatK);
  yaw = atan2(siny_cosp, cosy_cosp);
}

bool readlinearAccelerometer() {
  unsigned long startTime = millis();
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_ACCELEROMETER) {
    if (millis() - startTime > ACCELEROMETER_TIMEOUT) {
      Serial.println("Timeout waiting for accelerometer event");
      return false;
    }
  }
  linaccelX = myIMU.getAccelX();
  linaccelY = myIMU.getAccelY();
  linaccelZ = myIMU.getAccelZ();
  return true;
}

bool readMagnetometer() {
  unsigned long startTime = millis();
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_MAGNETIC_FIELD) {
    if (millis() - startTime > ACCELEROMETER_TIMEOUT) {
      Serial.println("Timeout waiting for magnetometer event");
      return false;
    }
  }
  MagX = myIMU.getMagX();
  MagY = myIMU.getMagY();
  MagZ = myIMU.getMagZ();

  return true;
}

bool readGyroIntegratedRotationVector() {
  unsigned long startTime = millis();
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_GYRO_INTEGRATED_ROTATION_VECTOR) {
    if (millis() - startTime > ACCELEROMETER_TIMEOUT) {
      Serial.println("Timeout waiting for gyro integrated rotation vector event");
      return false;
    }
  }
  gyroX = myIMU.getGyroX();
  gyroY = myIMU.getGyroY();
  gyroZ = myIMU.getGyroZ();

  return true;
}
void readBNO086() {
  if (myIMU.wasReset()) {
    Serial.println("Sensor was reset. Re-enabling reports...");
    setReports();
  }

  if (!readRotationVector()) {
    // Handle rotation vector read failure
    Serial.println("Rotation vector read failure");
  }

  if (!readlinearAccelerometer()) {
    // Handle accelerometer read failure
    Serial.println("Accelerometer read failure");
  }

  if (!readMagnetometer()) {
    // Handle magnetometer read failure
    Serial.println("Magnetometer read failure");
  }

  if (!readGyroIntegratedRotationVector()) {
    // Handle gyro integrated rotation vector read failure
    Serial.println("Gyro integrated rotation vector read failure");
  }


}