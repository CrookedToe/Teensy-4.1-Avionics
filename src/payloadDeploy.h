#ifndef PAYLOADDEPLOY_H
#define PAYLOADDEPLOY_H

extern const int PIN_NUMBER;
extern bool payloadDeployed;

void setupPayloadDeploy();
void deployPayload();
void deployAirbag();
void thrusterDeploy();
void thrusterKill();
#endif // PAYLOADDEPLOY_H

