#include "xbee.h"
#include <Arduino.h>

// Variable to store the character read from the XBee
char xbeechar;

// Function to setup the XBee
void xbeesetup() {
  // Begin serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial7.begin(9600);
}

// Function to write data to the XBee
void xbeewriteloop(std::string data) {
    // Write the data to the XBee
  size_t bytesWritten = Serial7.write(data.c_str(), data.length());

    Serial.println(bytesWritten);
}

// Function to read data from the XBee
char xbeereadloop() {
  // Check if data is available to read
  if (Serial7.available()) {
    // Read a character from the XBee
    xbeechar = Serial7.read();
    return xbeechar;
  }
  else {
    return '0';
  }
}

