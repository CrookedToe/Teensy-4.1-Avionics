// SDWriter.cpp
#include <SD.h>
#include <SPI.h>
#include <vector>


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

void writeDataToSD(const std::vector<float>& dataPoints) {
    if (dataFile) {
        for (float data : dataPoints) {
            printData(data);
        }
        
        int bytesWritten = dataFile.println(); // Add a newline at the end of the data row
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