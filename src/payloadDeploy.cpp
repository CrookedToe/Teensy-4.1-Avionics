#include <global.h>
#include <payloadDeploy.h>
#include <arduino.h>
#include <xbee.h>
#include <servo.h>

bool payloadDeployed = false;
bool payloadDeployEnabled = false;
bool airbagDeployed = false;
bool thrusterKilled = false;
bool thrusterDeployed = false;
bool payloadDisconnected = false;

Servo Servo1;

// Function to setup payload deployment
void setupPayloadDeploy() {
    
    Servo1.attach(SERVO1_PIN);

    Servo1.write(0);

    pinMode(DEPLOYMENT_PIN_NUMBER, OUTPUT); // Set the pin as output
    pinMode(DEPLOYMENT_PAYLOAD_DISCONNECTED, INPUT); // Set the pin as input
    pinMode(AIRBAG_PIN_NUMBER, OUTPUT); // Set the pin as output
    pinMode(THRUSTER_PIN_NUMBER, OUTPUT); // Set the pin as output
    pinMode(STREAMER_PIN_NUMBER, OUTPUT); // Set the pin as output
    digitalWrite(DEPLOYMENT_PIN_NUMBER, LOW); // Set the pin to low
}

// Function to deploy payload
void deployPayload() {
    if (xbeechar == 'd' && !payloadDeployEnabled) {
        payloadDeployEnabled = true; // Set deploy to true if xbeechar is 'd'
        Serial7.println("PAYLOAD DEPLOYMENT ENABLED");
        Serial7.println("PAYLOAD DEPLOYMENT ENABLED");
        Serial7.println("PAYLOAD DEPLOYMENT ENABLED");

    }
    if(payloadDeployEnabled == true){
        if (digitalRead(DEPLOYMENT_PAYLOAD_DISCONNECTED) == LOW && rateofChange > descentValue) {
            payloadDisconnected = true;
            Serial7.println("PAYLOAD DISCONNECTED");
            Serial7.println("PAYLOAD DISCONNECTED");
            Serial7.println("PAYLOAD DISCONNECTED");
        }
    }
}

void payloadRelease() {
    if ((altitudeAltimeter - groundLevel) >= PAYLOAD_ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= PAYLOAD_ALTITUDE_MAX && altitudeAltimeter < previousAltitude && !payloadDeployed && payloadDeployEnabled) {
        digitalWrite(DEPLOYMENT_PIN_NUMBER, HIGH); // Set the pin to high
        payloadDeployed = true; // Set payloadDeployed to true
        Serial7.println("PAYLOAD DEPLOYED");
        Serial7.println("PAYLOAD DEPLOYED");
        Serial7.println("PAYLOAD DEPLOYED");
        delay(150);
        digitalWrite(DEPLOYMENT_PIN_NUMBER, LOW); // Set the pin to low
    }
}

void deployAirbag() {
    // Check conditions for payload deployment
    if ((altitudeAltimeter < previousAltitude) && !airbagDeployed && payloadDisconnected) {
        Servo1.write(180);
        airbagDeployed = true; // Set payloadDeployed to true
        Serial7.println("AIRBAG DEPLOYED");
        Serial7.println("AIRBAG DEPLOYED");
        Serial7.println("AIRBAG DEPLOYED");
    }
}

void thrusterDeploy() {
    if ((altitudeAltimeter - groundLevel) >= THRUSTER_ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= THRUSTER_ALTITUDE_MAX && altitudeAltimeter < previousAltitude && airbagDeployed && pitch > MIN_PITCH && pitch < MAX_PITCH && yaw > MIN_YAW && yaw < MAX_YAW && !thrusterDeployed && !thrusterKilled && payloadDisconnected) {
        digitalWrite(THRUSTER_PIN_NUMBER, HIGH); // Set the pin to high
        thrusterDeployed = true; // Set payloadDeployed to true
        Serial7.println("THRUSTER DEPLOYED");
        Serial7.println("THRUSTER DEPLOYED");
        Serial7.println("THRUSTER DEPLOYED");
    } 
}

void thrusterKill() {
    if (thrusterDeployed && ((pitch < MIN_PITCH || pitch > MAX_PITCH) || (yaw < MIN_YAW || yaw > MAX_YAW)) && !thrusterKilled) {
        digitalWrite(THRUSTER_PIN_NUMBER, LOW); // Set the pin to low
        thrusterKilled = true; // Set payloadDeployed to true
        Serial7.println("THRUSTER KILLED");
        Serial7.println("THRUSTER KILLED");
        Serial7.println("THRUSTER KILLED");
    }
}

void deployStreamer() {
    if (payloadDisconnected && (rateofChange >= descentValueStreamer || (pitch < -45 || pitch >45) || (yaw < -45 || yaw > 45))) {
        digitalWrite(STREAMER_PIN_NUMBER, HIGH); // Set the pin to high
        Serial7.println("STREAMER DEPLOYED");
        Serial7.println("STREAMER DEPLOYED");
        Serial7.println("STREAMER DEPLOYED");
    }
}