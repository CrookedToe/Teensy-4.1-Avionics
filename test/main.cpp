#include <bno086.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  initBNO086();
}

void loop() {
  readBNO086();
  Serial.print("AccelX: ");
  Serial.print(accelX);
  Serial.print(' ');

  Serial.print("AccelY: ");
  Serial.print(accelY);
  Serial.print(' ');

  Serial.print("AccelZ: ");
  Serial.print(accelZ);
  Serial.println(' ');

  Serial.print("gyroX: ");
  Serial.print(gyroX);
  Serial.print(' ');

  Serial.print("gyroY: ");
  Serial.print(gyroY);
  Serial.print(' ');

  Serial.print("gyroZ: ");
  Serial.print(gyroZ);
  Serial.println(" ");

  Serial.print("magX: ");
  Serial.print(magX);
  Serial.print(' ');

  Serial.print("magY: ");
  Serial.print(magY);
  Serial.print(' ');

  Serial.print("magZ: ");
  Serial.print(magZ);
  Serial.println(' ');

  delay(250);
}