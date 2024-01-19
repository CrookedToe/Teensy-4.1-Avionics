#include "xbee.h"
#include <Arduino.h>

char xbeechar;


void xbeesetup() {
  Serial.begin(9600);
Serial5.begin(9600);

}

void xbeewriteloop(std::string data) {
    Serial5.write(data.c_str(), data.length());
}

char xbeereadloop() {
  if (Serial5.available()) {
    xbeechar = Serial5.read();
    return xbeechar;
  }
  return '\0'; // return null character if no data available
}