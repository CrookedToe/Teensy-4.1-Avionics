#ifndef PAYLOADDEPLOY_H
#define PAYLOADDEPLOY_H

extern const int PIN_NUMBER;
extern bool payloadDeployed;

const int SERVO1_PIN = 26;

// Constants for payload deployment
const int DEPLOYMENT_PIN_NUMBER = 10; 
const int DEPLOYMENT_PAYLOAD_DISCONNECTED = 10;
const int AIRBAG_PIN_NUMBER = 24;
const int THRUSTER_PIN_NUMBER = 2;
const int STREAMER_PIN_NUMBER = 12;

// in meters
const float descentValue = 5;
const float descentValueStreamer = 9;
const float PAYLOAD_ALTITUDE_MIN = 121.92;
const float PAYLOAD_ALTITUDE_MAX = 160.02;
const float THRUSTER_ALTITUDE_MIN = 11.43;
const float THRUSTER_ALTITUDE_MAX = 12.954;

const float MIN_PITCH = -5;
const float MAX_PITCH = 5;

const float MIN_YAW = -5;
const float MAX_YAW = 5;

// Variables for payload deployment
// Declare global variables as extern
extern bool payloadDeployEnabled;
extern bool airbagDeployed;
extern bool thrusterKilled;
extern bool thrusterDeployed;
extern bool payloadDisconnected;


void setupPayloadDeploy();
void payloadRelease();
void deployPayload();
void deployAirbag();
void thrusterDeploy();
void thrusterKill();
void deployStreamer();
#endif // PAYLOADDEPLOY_H

