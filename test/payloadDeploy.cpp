#include "payloadDeploy.h"
#include "bmp390.h"
#include "arduino.h"
#include "globalvar.h"
// deploys the payload at the altitude of 550 feet coming down above the launch pad while also being triggered by the radio.
//altitude from launch pad is set via a button press.
//the radio works by the rflink which runs a pin high when triggered
//for the teensy 4.0 the pin is 2 and the payload deploy pin is 3
//rflink gets triggered right after payload deployment

void payloadDeploySetup() {
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
  rflinktrigger = 0;
}

void detectrflink() {
  if (digitalRead(2) == HIGH) {
    rflinktrigger += 1;
    delay(1000);
  }
}

void payloadDeploy() {
    if ((altitudeAltimeter - launchpadAltitude) > 500 && (altitudeAltimeter - launchpadAltitude) < 600 && rflinktrigger >= 2) {
        digitalWrite(3, HIGH);
        delay (500);
        digitalWrite(3, LOW);
    }
}