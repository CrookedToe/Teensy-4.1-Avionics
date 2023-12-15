#include "bno055.h"
#include "wire.h"
#include "global.h"
#include "Adafruit_BNO055.h"

Adafruit_BNO055 bno = Adafruit_BNO055();


// Initialize the BNO055 sensor
void initBNO055() {
    Wire.begin();

  if (!bno.begin()) {
    Serial.print("No BNO055 detected. Check your wiring or I2C address");
    return; // return from the function if sensor is not detected
  }
  const int delayTime = 1000;
  delay(delayTime);
  const bool useExtCrystal = true;
  bno.setExtCrystalUse(useExtCrystal);
}

// Read the rotation vector from the BNO055 sensor
void bno055readRotationVector() {
  sensors_event_t event;
  bno.getEvent(&event);
  roll = event.orientation.x;
  pitch = event.orientation.y;
  yaw = event.orientation.z;
}

// Read the gravity vector from the BNO055 sensor
void bno055readGravity() {
  imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  gravityX = gravity.x();
  gravityY = gravity.y();
  gravityZ = gravity.z();
}