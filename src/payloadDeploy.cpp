#include "global.h"
#include "payloadDeploy.h"
#include "arduino.h"

int PIN_NUMBER;
bool payloadDeployed;

void setupPayloadDeploy() {
    pinMode(PIN_NUMBER, OUTPUT);
    digitalWrite(PIN_NUMBER, LOW); 
    payloadDeployed = false;
    PIN_NUMBER = 0;
}
void deployPayload() {
    if (altitudeAltimeter >= 525.0 && altitudeAltimeter <= 575.0 && altitudeAltimeter < previousAltitude && !payloadDeployed) {
    digitalWrite(PIN_NUMBER, HIGH); // Replace PIN_NUMBER with the actual pin number
    payloadDeployed = true;
    }
    previousAltitude = altitudeAltimeter;
}
