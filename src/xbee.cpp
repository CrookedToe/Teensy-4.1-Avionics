#include "xbee.h"
#include <Arduino.h>




void xbeesetup() {
  Serial.begin(9600);
Serial5.begin(9600);
}

void xbeewriteloop(String data) {
  if (Serial.available()) {
    Serial5.write(data.c_str(), data.length());
  }
}

void xbereadloop() {
  if (Serial5.available()) {
    xbeechar = Serial5.read();
  }
}
