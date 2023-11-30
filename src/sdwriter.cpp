// SDWriter.cpp
#include <SD.h>
#include <SPI.h>


File dataFile;

void setupSDWriter() {
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  
  // Open up the file we're going to log to!
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("error opening datalog.csv");
    // Wait forever since we cant write data
    while (1);
  }
}
void writeDataToSD(float roll, float pitch, float yaw, float temperature, float pressure, float altitude, float latitude, float longitude, float altitudeGPS, float speed, float heading) {
  if (dataFile) {
    dataFile.print(roll);
    dataFile.print(",");
    dataFile.print(pitch);
    dataFile.print(",");
    dataFile.print(yaw);
    dataFile.print(",");
    dataFile.print(temperature);
    dataFile.print(",");
    dataFile.print(pressure);
    dataFile.print(",");
    dataFile.print(altitude);
    dataFile.print(",");
    dataFile.print(latitude);
    dataFile.print(",");
    dataFile.print(longitude);
    dataFile.print(",");
    dataFile.print(altitudeGPS);
    dataFile.print(",");
    dataFile.print(speed);
    dataFile.print(",");
    int bytesWritten = dataFile.println(heading);
    if(bytesWritten == 0) {
        Serial.println("Write failed");
        }
        dataFile.flush();
    if(!dataFile) {
        Serial.println("Flush failed or file got closed");
        }
    }
}

void closeSDWriter() {
  dataFile.close();
}