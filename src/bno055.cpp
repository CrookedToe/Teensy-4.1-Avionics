#include <bno055.h>
#include <wire.h>
#include <global.h>
#include <Adafruit_BNO055.h>

// Initialize BNO055 sensor
Adafruit_BNO055 bno = Adafruit_BNO055();

// Constants for BNO055 sensor configuration
const int SENSOR_INIT_DELAY = 1000; // Delay to ensure sensor is ready

void initBNO055() {
  // Start the I2C bus
  Wire.begin();

  // Check if BNO055 sensor is connected
  if (!bno.begin()) {
    Serial5.println("No BNO055 detected. Check your wiring or I2C address");
  }

  // Delay to ensure sensor is ready
  delay(SENSOR_INIT_DELAY);

  // Use external crystal for better accuracy
  bno.setExtCrystalUse(true);
}

void bno055readRotationVector() {
  // Get the orientation data
  sensors_event_t event;
  bno.getEvent(&event);

  // Store the orientation data
  roll = event.orientation.x;
  pitch = event.orientation.y;
  yaw = event.orientation.z;
}

void bno055readGravity() {
  // Get the gravity vector
  imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

  // Store the gravity data
  gravityX = gravity.x();
  gravityY = gravity.y();
  gravityZ = gravity.z();
}