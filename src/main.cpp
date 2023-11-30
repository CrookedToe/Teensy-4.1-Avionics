#include <bno086.h>
#include <Wire.h>
#include <bmp390.h>
#include <UltimateGPS.h>
#include <SDWriter.h>
void setup() {
  Serial.begin(115200);
  setupSDWriter();
  initBNO086();
  initBMP390();
  initUltimateGPS();
  delay(10000);
}

void loop() {
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

  writeDataToSD(roll, pitch, yaw, temperature, pressure, altitudeAltimeter, latitude, longitude, altitudeGPS, speed, heading);
  delay(50);
}