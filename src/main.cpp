#include <bno086.h>
#include <Wire.h>
#include <bmp390.h>
#include <UltimateGPS.h>
#include <SDWriter.h>
#include <vector>

void setup() {
  Serial.begin(115200);
  setupSDWriter();
  initBNO086();
  initBMP390();
  initUltimateGPS();
  delay(2000);
}

void loop() {
  readGravity();  
  readRotationVector();
  readBMP390();
  readUltimateGPS();

  Serial.print("roll: ");
  Serial.print(roll);
  Serial.print(' ');

  Serial.print("pitch: ");
  Serial.print(pitch);
  Serial.print(' ');

  Serial.print("yaw: ");
  Serial.print(yaw);
  Serial.print(" ");

  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.print(' ');

  Serial.print("pressure: ");
  Serial.print(pressure);
  Serial.print(' ');

  Serial.print("altitude: ");
  Serial.print(altitudeAltimeter);
  Serial.print(' ');

  Serial.print("gravityX: ");
  Serial.print(gravityX);
  Serial.print(' ');

  Serial.print("gravityY: ");
  Serial.print(gravityY);
  Serial.print(' ');

  Serial.print("gravityZ: ");
  Serial.print(gravityZ);
  Serial.print(' ');


  Serial.print("latitude: ");
  Serial.print(latitude);
  Serial.print(' ');

  Serial.print("longitude: ");
  Serial.print(longitude);
  Serial.print(' ');

  Serial.print("altitude: ");
  Serial.print(altitudeGPS);
  Serial.print(' ');

  Serial.print("speed: ");
  Serial.print(speed);
  Serial.print(' ');

  Serial.print("heading: ");
  Serial.print(heading);
  Serial.println();

std::vector<float> dataPoints = {roll, pitch, yaw, temperature, pressure, altitudeAltimeter, gravityX, gravityY, gravityZ, latitude, longitude, altitudeGPS, speed, heading};

writeDataToSD(dataPoints);  
delay(250);
}