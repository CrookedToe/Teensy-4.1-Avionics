#include <Wire.h>
#include <vector>
#include <bmp390.h>
#include <bno055.h>
#include <global.h>
#include <UltimateGPS.h>
#include <SDWriter.h>
#include <payloadDeploy.h>
#include <xbee.h>

unsigned long previousMillis = 0;  // will store the last time the GPS was read
unsigned long previousMillisXBee = 0;  // will store the last time the XBee data was sent
const long interval = 100;  // the non-blocking delay interval (250 milliseconds)
const long intervalXBee = 3000;  // the non-blocking delay interval for XBee data sending (2000 milliseconds)


char lat_str[10];
char lon_str[10];

void setup() {
  Serial.begin(115200);
  xbeesetup();
  setupSDWriter();
  initBNO055();
  initBMP390();
  initUltimateGPS();
  setupPayloadDeploy();
  Serial5.println("Test message");
  delay(2000);
}

void loop() {
  readUltimateGPS();

  unsigned long currentMillis = millis();

  std::vector<std::pair<std::string, float>> dataPoints = {
    {"Roll: ", roll}, 
    {"Pitch: ", pitch}, 
    {"Yaw: ", yaw}, 
    {"Temperature: ", temperature}, 
    {"Pressure: ", pressure}, 
    {"Altitude Altimeter: ", altitudeAltimeter},
    {"Ground Level: ", groundLevel},
    {"Altitude from Launchpad: ", altitudefromlaunchpad},
    {"Gravity X: ", gravityX}, 
    {"Gravity Y: ", gravityY}, 
    {"Gravity Z: ", gravityZ}, 
    {"Latitude: ", latitude}, 
    {"Longitude: ", longitude}, 
    {"Altitude GPS: ", altitudeGPS}, 
    {"Speed: ", speed}, 
    {"Heading: ", heading}, 
    {"Satellite Count: ", SatelliteCount}
  };

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    std::vector<float> floatDataPoints;
    for (const auto& point : dataPoints) {
      floatDataPoints.push_back(point.second);
    }
  
    writeDataToSD(floatDataPoints);
    bno055readGravity();
    bno055readRotationVector();
    deployPayload();
    deployAirbag();
    thrusterDeploy();
    readBMP390();
    if (thrusterDeployed) {
      thrusterKill();
    }
  }

  if (currentMillis - previousMillisXBee >= intervalXBee) {
    previousMillisXBee = currentMillis;

    // Convert data points to strings and concatenate them
    std::string data;
    for (const auto& point : dataPoints) {
      char str[10];
      dtostrf(point.second, 4, 6, str);
      data += point.first + std::string(str) + "\n";
    }

    // Send data via XBee
    xbeewriteloop(data);
  }
  xbeereadloop();
}

