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

void printData(float data) {
    dataFile.print(data);
    dataFile.print(",");
}

void writeDataToSD(float roll, float pitch, float yaw, float temperature, float pressure, float altitude, float gravityx,float gravityy, float gravityz, float latitude, float longitude, float altitudeGPS, float speed, float heading) {
  if (dataFile) {
    printData(roll);
    printData(pitch);
    printData(yaw);
    printData(temperature);
    printData(pressure);
    printData(altitude);
    printData(gravityx);
    printData(gravityy);
    printData(gravityz);
    printData(latitude);
    printData(longitude);
    printData(altitudeGPS);
    printData(speed);
    
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