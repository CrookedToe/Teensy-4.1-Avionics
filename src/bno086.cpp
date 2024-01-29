#include <Wire.h>
#include <SparkFun_BNO08x_Arduino_Library.h>
#include <bno086.h>
#include <global.h>

// Initialize BNO08x sensor
BNO08x myIMU;

// Variables to store sensor readings
float roll, pitch, yaw; // Roll, pitch and yaw values
float gravityX, gravityY, gravityZ; // Gravity force vector values

// Function to enable desired sensor outputs
void setReports() {
  Serial.println("Setting desired reports");

  if (myIMU.enableRotationVector()) {
    Serial.println(F("Rotation vector enabled"));
    Serial.println(F("Output in form roll, pitch, yaw"));
  } else {
    Serial.println("Could not enable rotation vector");
  }

  if (myIMU.enableGravity()) {
    Serial.println(F("Gravity enabled"));
    Serial.println(F("Output in form x, y, z"));
  } else {
    Serial.println("Could not enable gravity");
  }
}

// Function to initialize BNO086 sensor
void initBNO086() {
  Serial.println();
  Serial.println("BNO08x Read Example");

  // Start the I2C bus
  Wire.begin();

  // Check if BNO08x sensor is connected
  if (!myIMU.begin()) {
    Serial5.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1);
  }

  Serial5.println("BNO08x found!");

  setReports();

  Serial5.println("Reading events");
  delay(250);
}

// Function to read rotation vector from BNO086 sensor
void bno086readRotationVector() {
  if (myIMU.wasReset()) {
    Serial.print("bno086 sensor was reset ");
    setReports();
  }

  // Check if a new event has come in on the Sensor Hub Bus
  if (myIMU.getSensorEvent()) {
    // Check if it is the correct sensor data we want
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_ROTATION_VECTOR) {
      // Convert and store the orientation data
      roll = (myIMU.getRoll()) * 180.0 / PI;
      pitch = (myIMU.getPitch()) * 180.0 / PI;
      yaw = (myIMU.getYaw()) * 180.0 / PI;
    }
  }
}

// Function to read gravity vector from BNO086 sensor
void bno086readGravity() {
  if (myIMU.wasReset()) {
    Serial.print("bno086 sensor was reset ");
    setReports();
  }

  // Check if a new event has come in on the Sensor Hub Bus
  if (myIMU.getSensorEvent()) {
    // Check if it is the correct sensor data we want
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_GRAVITY) {
      // Store the gravity data
      gravityX = myIMU.getGravityX();
      gravityY = myIMU.getGravityY();
      gravityZ = myIMU.getGravityZ();
    }
  }
}