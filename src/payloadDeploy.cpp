#include <global.h>
#include <payloadDeploy.h>
#include <arduino.h>
#include <xbee.h>
#include <servo.h>

Servo Servo1;
Servo Servo2;

// Function to setup payload deployment
void setupPayloadDeploy() {
    payloadDeploy = false; // Initialize deploy as false
    payloadDeployed = false; // Initialize payloadDeployed as false
    airbagDeployed = false;
    thrusterDeployed = false;
    thrusterKilled = false;

    Servo1.attach(SERVO1_PIN);
    Servo2.attach(SERVO2_PIN);

    pinMode(DEPLOYMENT_PIN_NUMBER, OUTPUT); // Set the pin as output
    pinMode(DEPLOYMENT_PAYLOAD_DISCONNECTED, INPUT); // Set the pin as input
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
    if(payloadDeploy == true && !payloadDeployed){
        if (digitalRead(DEPLOYMENT_PAYLOAD_DISCONNECTED) == LOW) {
            payloadDisconnected = true;
            Serial5.println("PAYLOAD DISCONNECTED");
            Serial5.println("PAYLOAD DISCONNECTED");
            Serial5.println("PAYLOAD DISCONNECTED");
        }
    }
    // Check conditions for payload deployment
    if ((altitudeAltimeter - groundLevel) >= PAYLOAD_ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= PAYLOAD_ALTITUDE_MAX && altitudeAltimeter < previousAltitude && !payloadDeployed && payloadDeploy) {
        digitalWrite(DEPLOYMENT_PIN_NUMBER, HIGH); // Set the pin to high
        payloadDeployed = true; // Set payloadDeployed to true
        Serial5.println("PAYLOAD DEPLOYED");
        Serial5.println("PAYLOAD DEPLOYED");
        Serial5.println("PAYLOAD DEPLOYED");
        delay(150);
        digitalWrite(DEPLOYMENT_PIN_NUMBER, LOW); // Set the pin to low
    }
}

void deployAirbag() {
    // Check conditions for payload deployment
    if ((altitudeAltimeter < previousAltitude) && !airbagDeployed && payloadDeployed && payloadDisconnected) {
        digitalWrite(AIRBAG_PIN_NUMBER, HIGH); // Set the pin to high
        airbagDeployed = true; // Set payloadDeployed to true
        Serial5.println("AIRBAG DEPLOYED");
        Serial5.println("AIRBAG DEPLOYED");
        Serial5.println("AIRBAG DEPLOYED");
    }
}

void thrusterDeploy() {
    if ((altitudeAltimeter - groundLevel) >= THRUSTER_ALTITUDE_MIN && (altitudeAltimeter - groundLevel) <= THRUSTER_ALTITUDE_MAX && altitudeAltimeter < previousAltitude && airbagDeployed && payloadDeployed && pitch > MIN_PITCH && pitch < MAX_PITCH && yaw > MIN_YAW && yaw < MAX_YAW && !thrusterDeployed && !thrusterKilled && payloadDisconnected) {
        digitalWrite(THRUSTER_PIN_NUMBER, HIGH); // Set the pin to high
        thrusterDeployed = true; // Set payloadDeployed to true
        Serial5.println("THRUSTER DEPLOYED");
        Serial5.println("THRUSTER DEPLOYED");
        Serial5.println("THRUSTER DEPLOYED");
    } 
}

void thrusterKill() {
    if (thrusterDeployed && (pitch < MIN_PITCH || pitch > MAX_PITCH) || (yaw < MIN_YAW || yaw > MAX_YAW) && !thrusterKilled) {
        digitalWrite(THRUSTER_PIN_NUMBER, LOW); // Set the pin to low
        thrusterKilled = true; // Set payloadDeployed to true
        Serial5.println("THRUSTER KILLED");
        Serial5.println("THRUSTER KILLED");
        Serial5.println("THRUSTER KILLED");
    }
}