#include <global.h>
#include <payloadDeploy.h>
#include <arduino.h>
#include <xbee.h>

// Constants for payload deployment
const int DEPLOYMENT_PIN_NUMBER = 10; 
const int AIRBAG_PIN_NUMBER = 24;
const int THRUSTER_PIN_NUMBER = 12;

const float PAYLOAD_ALTITUDE_MIN = 152.4;
const float PAYLOAD_ALTITUDE_MAX = 167.640;
const float THRUSTER_ALTITUDE_MIN = 11.43;
const float THRUSTER_ALTITUDE_MAX = 12.954;

// Variables for payload deployment
bool payloadDeployed;
bool payloadDeploy;
bool airbagDeployed;
bool thrusterKilled;
bool thrusterDeployed;

// Function to setup payload deployment
void setupPayloadDeploy() {
    payloadDeploy = false; // Initialize deploy as false
    payloadDeployed = false; // Initialize payloadDeployed as false
    airbagDeployed = false;
    thrusterDeployed = false;
    thrusterKilled = false;

    pinMode(DEPLOYMENT_PIN_NUMBER, OUTPUT); // Set the pin as output
    pinMode(AIRBAG_PIN_NUMBER, OUTPUT); // Set the pin as output
    pinMode(THRUSTER_PIN_NUMBER, OUTPUT); // Set the pin as output
    
    digitalWrite(DEPLOYMENT_PIN_NUMBER, LOW); // Set the pin to low
}

// Function to deploy payload
void deployPayload() {
    if (xbeechar == 'd' && !payloadDeploy) {
        payloadDeploy = true; // Set deploy to true if xbeechar is 'd'
        Serial5.println("PAYLOAD DEPLOYMENT ENABLED");
        Serial5.println("PAYLOAD DEPLOYMENT ENABLED");
        Serial5.println("PAYLOAD DEPLOYMENT ENABLED");

    }

    // Check conditions for payload deployment
    if ((altitudeAltimeter - groundLevel) >= PAYLOAD_ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= PAYLOAD_ALTITUDE_MAX && altitudeAltimeter < previousAltitude && !payloadDeployed && payloadDeploy) {
        digitalWrite(DEPLOYMENT_PIN_NUMBER, HIGH); // Set the pin to high
        payloadDeployed = true; // Set payloadDeployed to true
        Serial5.println("PAYLOAD DEPLOYED");
        Serial5.println("PAYLOAD DEPLOYED");
        Serial5.println("PAYLOAD DEPLOYED");
        digitalWrite(DEPLOYMENT_PIN_NUMBER, LOW); // Set the pin to low
    }
}

void deployAirbag() {
    // Check conditions for payload deployment
    if ((altitudeAltimeter < previousAltitude) && !airbagDeployed && payloadDeployed) {
        digitalWrite(AIRBAG_PIN_NUMBER, HIGH); // Set the pin to high
        airbagDeployed = true; // Set payloadDeployed to true
        Serial5.println("AIRBAG DEPLOYED");
        Serial5.println("AIRBAG DEPLOYED");
        Serial5.println("AIRBAG DEPLOYED");
    }
}

void thrusterDeploy() {
    if ((altitudeAltimeter - groundLevel) >= THRUSTER_ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= THRUSTER_ALTITUDE_MAX && altitudeAltimeter < previousAltitude && airbagDeployed && payloadDeployed && pitch <= -82.5 && pitch >= -97.5 && !thrusterDeployed && !thrusterKilled) {
        digitalWrite(THRUSTER_PIN_NUMBER, HIGH); // Set the pin to high
        thrusterDeployed = true; // Set payloadDeployed to true
        Serial5.println("THRUSTER DEPLOYED");
        Serial5.println("THRUSTER DEPLOYED");
        Serial5.println("THRUSTER DEPLOYED");
    } 
}

void thrusterKill() {
    if (thrusterDeployed && pitch > -82.5 && pitch < -97.5) {
        digitalWrite(THRUSTER_PIN_NUMBER, LOW); // Set the pin to low
        thrusterKilled = true; // Set payloadDeployed to true
        Serial5.println("THRUSTER KILLED");
        Serial5.println("THRUSTER KILLED");
        Serial5.println("THRUSTER KILLED");
    }
}