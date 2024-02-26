#include <Wire.h>
#include <vector>
#include <bno055.h>
#include <global.h>
#include <payloadDeploy.h>
#include <arduino.h>
#include <servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(115200);
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object
}

void loop() {
    myservo.write(0);
    delay(1000);
    myservo.write(180);
    delay(1000);
}

