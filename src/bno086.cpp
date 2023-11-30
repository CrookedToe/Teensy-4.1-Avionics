#include <Wire.h>
#include "SparkFun_BNO08x_Arduino_Library.h"
#include "bno086.h"

BNO08x myIMU;

float roll, pitch, yaw; // Roll, pitch and yaw values
float gravityX, gravityY, gravityZ; // Gravity force vector values

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  Serial.println("Setting desired reports");
  if (myIMU.enableRotationVector() == true) {
    Serial.println(F("Rotation vector enabled"));
    Serial.println(F("Output in form roll, pitch, yaw"));
  } else {
    Serial.println("Could not enable rotation vector");
  }
  if (myIMU.enableGravity() == true) {
    Serial.println(F("Gravity enabled"));
    Serial.println(F("Output in form x, y, z"));
  } else {
    Serial.println("Could not enable gravity");
  }
}

void initBNO086() {
  Serial.println();
  Serial.println("BNO08x Read Example");

  Wire.begin();

  if (myIMU.begin() == false) {
    Serial.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1)
      ;
  }
  Serial.println("BNO08x found!");

  // Wire.setClock(400000); //Increase I2C data rate to 400kHz

  setReports();

  Serial.println("Reading events");
  delay(250);

}



void readRotationVector() {

  if (myIMU.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }

  // Has a new event come in on the Sensor Hub Bus?
  if (myIMU.getSensorEvent() == true) {

    // is it the correct sensor data we want?
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_ROTATION_VECTOR) {

    roll = (myIMU.getRoll()) * 180.0 / PI; // Convert roll to degrees
    pitch = (myIMU.getPitch()) * 180.0 / PI; // Convert pitch to degrees
    yaw = (myIMU.getYaw()) * 180.0 / PI; // Convert yaw / heading to degrees

    }
  }
}
void readGravity() {

  if (myIMU.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }

  // Has a new event come in on the Sensor Hub Bus?
  if (myIMU.getSensorEvent() == true) {

    // is it the correct sensor data we want?
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_GRAVITY) {

    gravityX = myIMU.getGravityX();
    gravityY = myIMU.getGravityY();
    gravityZ = myIMU.getGravityZ();

    }
  }
}