#include "global.h"
#include "payloadDeploy.h"
#include "arduino.h"
#include "xbee.h"


int PIN_NUMBER;
bool payloadDeployed;
bool deploy;

void setupPayloadDeploy() {
    pinMode(PIN_NUMBER, OUTPUT);
    digitalWrite(PIN_NUMBER, LOW); 
    payloadDeployed = false;
    PIN_NUMBER = 0;
    bool deploy = false;
}
void deployPayload() {
    if (xbeechar == 'd') {
        bool deploy = true;
    }

    if (altitudeAltimeter >= 525.0 && altitudeAltimeter <= 575.0 && altitudeAltimeter < previousAltitude && !payloadDeployed && deploy == true) {
    digitalWrite(PIN_NUMBER, HIGH); // Replace PIN_NUMBER with the actual pin number
    payloadDeployed = true;
    }
    previousAltitude = altitudeAltimeter;

}
