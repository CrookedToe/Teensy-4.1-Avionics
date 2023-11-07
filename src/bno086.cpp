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
float magZ, magY, magX;
float quatI, quatJ, quatK, quatReal;  // Add quaternion variables
float accelZ, accelY, accelX;

void setReports(void) {
  Serial.println("Setting desired reports");

  if (myIMU.enableRotationVector(1.25) == true) {  // Enable rotation vector report at 50Hz
    Serial.println(F("Rotation vector enabled"));
  } else {
    Serial.println("Could not enable rotation vector");
  }

  if (myIMU.enableAccelerometer() == true) {
    Serial.println(F("Accelerometer enabled"));
  } else {
    Serial.println("Could not enable Accelerometer");
  }

  if (myIMU.enableMagnetometer() == true) {
    Serial.println(F("Magnetometer enabled"));
  } else {
    Serial.println("Could not enable Magnetometer");
  }
}

void initBNO086() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("BNO08x Read Example");
  delay(100);
  Wire.begin();
  delay(100);
  if (myIMU.begin() == false) {
    Serial.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1)
      ;
  }
  Serial.println("BNO08x found!");

  // Wire.setClock(400000); //Increase I2C data rate to 400kHz

  setReports();

  Serial.println("Reading events");
  delay(100);
}

// Here is where you define the sensor outputs you want to receive


void readBNO086() {
  if (myIMU.wasReset()) {
    Serial.println("Sensor was reset. Re-enabling reports...");
    setReports();
  }

  // Wait for rotation vector event
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_ROTATION_VECTOR);
  quatI = myIMU.getQuatI();
  quatJ = myIMU.getQuatJ();
  quatK = myIMU.getQuatK();
  quatReal = myIMU.getQuatReal();

  Serial.print("Quat: ");
  Serial.print(quatI, 2);
  Serial.print(F(", "));
  Serial.print(quatJ, 2);
  Serial.print(F(", "));
  Serial.print(quatK, 2);
  Serial.print(F(", "));
  Serial.println(quatReal, 2);

  // Wait for accelerometer event
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_ACCELEROMETER);
  accelX = myIMU.getAccelX();
  accelY = myIMU.getAccelY();
  accelZ = myIMU.getAccelZ();

  Serial.print("Accel: ");
  Serial.print(accelX, 2);
  Serial.print(F(", "));
  Serial.print(accelY, 2);
  Serial.print(F(", "));
  Serial.println(accelZ, 2);

  // Wait for magnetometer event
  while (myIMU.getSensorEvent() == false || myIMU.getSensorEventID() != SENSOR_REPORTID_MAGNETIC_FIELD);
  magX = myIMU.getMagX();
  magY = myIMU.getMagY();
  magZ = myIMU.getMagZ();

  Serial.print("Mag: ");
  Serial.print(magX, 2);
  Serial.print(F(", "));
  Serial.print(magY, 2);
  Serial.print(F(", "));
  Serial.println(magZ, 2);
}