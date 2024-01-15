#include "xbee.h"
#include <Arduino.h>



void xbeesetup() {
  Serial.begin(9600);
Serial1.begin(9600);
}

void xbeeloop(String data) {
  if (Serial.available()) {
    Serial.write(data.c_str(), data.length());
  }
}