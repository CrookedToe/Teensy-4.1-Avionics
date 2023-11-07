#include <Wire.h>
#include <bno086.h>
#include "SparkFun_BNO08x_Arduino_Library.h"


void setup() {
  initBNO086(); // Assuming this function initializes the BNO086 sensor as per your previous code
}

void loop() {
  readBNO086(); // Assuming this function reads data from the BNO086 sensor as per your previous code
  delay(100); // Delay between readings. Adjust as needed.
}