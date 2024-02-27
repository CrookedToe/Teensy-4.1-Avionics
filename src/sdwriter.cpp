#include <SD.h>
#include <SPI.h>
#include <vector>

File dataFile;

// Constants for SD card writer
const char* FILE_NAME = "datalog.csv";

void setupSDWriter() {
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial5.println("Card failed, or not present");
    return; // Return from function if SD card initialization fails
  }
  Serial5.println("card initialized.");
  
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (!dataFile) {
    Serial5.println("error opening datalog.csv");
    return; // Return from function if file opening fails
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
        
        int bytesWritten = dataFile.println();
        if(bytesWritten == 0) {
            Serial7.println("Write failed");
        }
        dataFile.flush();
        if(!dataFile) {
            Serial7.println("Flush failed or file got closed");
        }
    }
}

void closeSDWriter() {
  dataFile.close();
}