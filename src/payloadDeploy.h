#ifndef PAYLOADDEPLOY_H
#define PAYLOADDEPLOY_H

extern const int PIN_NUMBER;
extern bool payloadDeployed;

const int SERVO1_PIN = 9;
const int SERVO2_PIN = 8;

// Constants for payload deployment
const int DEPLOYMENT_PIN_NUMBER = 10; 
const int DEPLOYMENT_PAYLOAD_DISCONNECTED = 11;
const int AIRBAG_PIN_NUMBER = 24;
const int THRUSTER_PIN_NUMBER = 12;

// in meters
const float PAYLOAD_ALTITUDE_MIN = 152.4;
const float PAYLOAD_ALTITUDE_MAX = 167.640;
const float THRUSTER_ALTITUDE_MIN = 11.43;
const float THRUSTER_ALTITUDE_MAX = 12.954;

const float MIN_PITCH = -5;
const float MAX_PITCH = 5;

const float MIN_YAW = -5;
const float MAX_YAW = 5;

// Variables for payload deployment
bool payloadDeployed;
bool payloadDeployEnabled;
bool airbagDeployed;
bool thrusterKilled;
bool thrusterDeployed;
bool payloadDisconnected;

void setupPayloadDeploy();
void deployPayload();
void deployAirbag();
void thrusterDeploy();
void thrusterKill();
#endif // PAYLOADDEPLOY_H

