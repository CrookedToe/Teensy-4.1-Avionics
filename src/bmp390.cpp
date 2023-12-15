#include "bmp390.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Wire.h>
#include "globalvar.h"

Adafruit_BMP3XX bmp; // I2C

float temperature, pressure, altitudeAltimeter;

void initBMP390() {
  Serial.println(F("BMP390 test"));

  Wire1.begin(); // Start the I2C bus on pins 37 (SDA1) and 38 (SCL1)
    delay(100);   
  if (!bmp.begin_I2C()) { // Pass the Wire1 object to the begin_I2C function
    Serial.println(F("Could not find a valid BMP3 sensor, check wiring!"));
    while (1);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void readBMP390() {
  if (!bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  
  
  temperature = bmp.temperature;
  pressure = bmp.pressure / 100.0;
  altitudeAltimeter = bmp.readAltitude(1013.25); // this should be adjusted to your local forcase


}

