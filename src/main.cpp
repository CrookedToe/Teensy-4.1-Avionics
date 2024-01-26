//#include <bno086.h>
#include <Wire.h>
#include <bmp390.h>
#include <UltimateGPS.h>
#include <SDWriter.h>
//#include <payloadDeploy.h>
#include <bno055.h>
#include <global.h>
#include <vector>
#include <payloadDeploy.h>
#include <xbee.h>
unsigned long previousMillis = 0;  // will store the last time the GPS was read
const long interval = 250;  // the non-blocking delay interval (250 milliseconds)
  char lat_str[10];
  char lon_str[10];
void setup() {
  Serial.begin(115200);
  setupSDWriter();
//  initBNO086();
  initBNO055();
  initBMP390();
  initUltimateGPS();
//  payloadDeploySetup();
  setupPayloadDeploy();
  xbeesetup();
  delay(2000);
}

void loop() {
  readUltimateGPS();
//  payloadDeploy();
  // Serial.print("roll: ");
  // Serial.print(roll);
  // Serial.print(' ');

  // Serial.print("pitch: ");
  // Serial.print(pitch);
  // Serial.print(' ');

  // Serial.print("yaw: ");
  // Serial.print(yaw);
  // Serial.print(" ");

  // Serial.print("temperature: ");
  // Serial.print(temperature);
  // Serial.print(' ');

  // Serial.print("pressure: ");
  // Serial.print(pressure);
  // Serial.print(' ');

  // Serial.print("altitude: ");
  // Serial.print(altitudeAltimeter);
  // Serial.print(' ');

  // Serial.print("gravityX: ");
  // Serial.print(gravityX);
  // Serial.print(' ');

  // Serial.print("gravityY: ");
  // Serial.print(gravityY);
  // Serial.print(' ');

  // Serial.print("gravityZ: ");
  // Serial.print(gravityZ);
  // Serial.print(' ');


  // Serial.print("latitude: ");
  // Serial.print(latitude);
  // Serial.print(' ');

  // Serial.print("longitude: ");
  // Serial.print(longitude);
  // Serial.print(' ');

  // Serial.print("altitude: ");
  // Serial.print(altitudeGPS);
  // Serial.print(' ');

  // Serial.print("speed: ");
  // Serial.print(speed);
  // Serial.print(' ');

  // Serial.print("heading: ");
  // Serial.print(heading);
  // Serial.println();




  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  std::vector<float> dataPoints = {roll, pitch, yaw, temperature, pressure, altitudeAltimeter, gravityX, gravityY, gravityZ, latitude, longitude, altitudeGPS, speed, heading};
  writeDataToSD(dataPoints);

  Serial.print("Latitude: ");
  Serial.print(latitude, 6);
  Serial.print(" Longitude: ");
  Serial.print(longitude, 6);

  dtostrf(latitude, 4, 6, lat_str);
  dtostrf(longitude, 4, 6, lon_str);
    // Put the code you want to run every 250 milliseconds here
  std::string data = std::string("Latitude: ") + lat_str + " Longitude: " + lon_str + "\n";
  xbeewriteloop(data);
  bno055readGravity();  
  bno055readRotationVector();
  deployPayload();
  readBMP390();
  }
}

