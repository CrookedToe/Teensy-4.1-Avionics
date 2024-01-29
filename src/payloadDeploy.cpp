#include <global.h>
#include <payloadDeploy.h>
#include <arduino.h>
#include <xbee.h>

// Constants for payload deployment
const int PIN_NUMBER = 10; 
const float ALTITUDE_MIN = 152.4;
const float ALTITUDE_MAX = 167.640;

// Variables for payload deployment
bool payloadDeployed;
bool deploy;

// Function to setup payload deployment
void setupPayloadDeploy() {
    deploy = false; // Initialize deploy as false
    payloadDeployed = false; // Initialize payloadDeployed as false

    pinMode(PIN_NUMBER, OUTPUT); // Set the pin as output
    digitalWrite(PIN_NUMBER, LOW); // Set the pin to low
}

// Function to deploy payload
void deployPayload() {
    if (xbeechar == 'd' && !deploy) {
        deploy = true; // Set deploy to true if xbeechar is 'd'
        Serial5.println("PAYLOAD DEPLOYMENT ENABLED");
        Serial5.println("PAYLOAD DEPLOYMENT ENABLED");
        Serial5.println("PAYLOAD DEPLOYMENT ENABLED");

    }

    // Check conditions for payload deployment
    if ((altitudeAltimeter - groundLevel) >= ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= ALTITUDE_MAX && altitudeAltimeter < previousAltitude && !payloadDeployed && deploy) {
        digitalWrite(PIN_NUMBER, HIGH); // Set the pin to high
        payloadDeployed = true; // Set payloadDeployed to true
        delay(300);
        Serial5.println("PAYLOAD DEPLOYED");
        Serial5.println("PAYLOAD DEPLOYED");
        Serial5.println("PAYLOAD DEPLOYED");

        digitalWrite(PIN_NUMBER, LOW); // Set the pin to low
    }
}