#include "xbee.h"
#include <Arduino.h>

// Variable to store the character read from the XBee
char xbeechar;

// Function to setup the XBee
void xbeesetup() {
  // Begin serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial5.begin(9600);
}

// Function to write data to the XBee
void xbeewriteloop(std::string data) {
    // Write the data to the XBee
    Serial5.write(data.c_str(), data.length());
}

// Function to read data from the XBee
char xbeereadloop() {
  // Check if data is available to read
  if (Serial5.available()) {
    // Read a character from the XBee
    xbeechar = Serial5.read();
    return xbeechar;
  }
  // Return null character if no data is available
  return '\0';
}

// Function to send data from serial monitor to the XBee
void serialToXbeeLoop() {
    // Check if data is available to read from the serial monitor
    while (Serial.available()) {
        // Read a character from the serial monitor
        char c = Serial.read();
        // Write the character to the XBee
        Serial5.write(c);
    }
}