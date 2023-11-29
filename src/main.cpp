#include <bno086.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  initBNO086();
}

void loop() {
  delay(500);
  readBNO086();
  readRotationVector();
  readlinearAccelerometer();
  readMagnetometer();
  readGyroIntegratedRotationVector();
  
  Serial.print("QuatI: ");
  Serial.print(quatI);
  Serial.print(' ');

  Serial.print("Quatj: ");
  Serial.print(quatJ);
  Serial.print(' ');

  Serial.print("Quatk: ");
  Serial.print(quatK);
  Serial.println(" ");

  Serial.print("QuatReal: ");
  Serial.print(quatReal);
  Serial.println(" ");

  Serial.print("LinaccelZ: ");
  Serial.print(linaccelZ);
  Serial.print(' ');
  
  Serial.print("LinaccelY: ");
  Serial.print(linaccelY);
  Serial.print(' ');

  Serial.print("LinaccelX: ");
  Serial.print(linaccelX);
  Serial.println(" ");

  Serial.print("MagX: ");
  Serial.print(MagX);
  Serial.print(' ');

  Serial.print("MagY: ");
  Serial.print(MagY);
  Serial.print(' ');

  Serial.print("MagZ: ");
  Serial.print(MagZ);
  Serial.println(" ");

  



  delay(50);
}