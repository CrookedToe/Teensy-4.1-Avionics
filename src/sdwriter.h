#ifndef SDWRITER_H
#define SDWRITER_H

void setupSDWriter();
void writeDataToSD(float roll, float pitch, float yaw, float temperature, float pressure, float altitude, float gravityx, float gravityy, float gravityz, float latitude, float longitude, float altitudeGPS, float speed, float heading);

#endif // SDWRITER_H