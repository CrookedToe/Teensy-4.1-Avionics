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

  Serial.print("QuatI: ");
  Serial.print(quatI);
  Serial.print(' ');

  Serial.print("Quatj: ");
  Serial.print(quatJ);
  Serial.print(' ');

  Serial.print("Quatk: ");
  Serial.print(quatK);
  Serial.println(" ");

  delay(50);
}