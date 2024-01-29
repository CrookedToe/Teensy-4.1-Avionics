#include <bmp390.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Wire.h>
#include <global.h>

// Constants for BMP3 sensor configuration
const uint8_t TEMP_OVERSAMPLING = BMP3_OVERSAMPLING_8X;
const uint8_t PRESSURE_OVERSAMPLING = BMP3_OVERSAMPLING_4X;
const uint8_t IIR_FILTER_COEFF = BMP3_IIR_FILTER_COEFF_3;
const uint8_t OUTPUT_DATA_RATE = BMP3_ODR_50_HZ;
const float ALTITUDE_ADJUSTMENT = 1013.25; // This should be adjusted to your local forecast

// Initialize BMP3XX sensor on I2C
Adafruit_BMP3XX bmp;

// Variables to store sensor readings
float temperature, pressure, altitudeAltimeter, previousAltitude;

// Function to initialize BMP390 sensor
void initBMP390() {
  Serial.println(F("Initializing BMP390..."));

  // Start the I2C bus on pins 37 (SDA1) and 38 (SCL1)
  Wire1.begin();
  delay(100);

  // Check if BMP3 sensor is connected
  if (!bmp.begin_I2C()) {
    Serial.println(F("Could not find a valid BMP3 sensor, check wiring!"));
    return; // Return from function if sensor is not found
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(TEMP_OVERSAMPLING);
  bmp.setPressureOversampling(PRESSURE_OVERSAMPLING);
  bmp.setIIRFilterCoeff(IIR_FILTER_COEFF);
  bmp.setOutputDataRate(OUTPUT_DATA_RATE);

  Serial.println(F("BMP390 initialized successfully."));
}

// Function to read data from BMP390 sensor
void readBMP390() {
  // Perform sensor reading
  if (!bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  // Store sensor readings in variables
  temperature = bmp.temperature;
  pressure = bmp.pressure / 100.0;
  previousAltitude = altitudeAltimeter; // Store the current altitude to previousAltitude before updating it
  altitudeAltimeter = bmp.readAltitude(ALTITUDE_ADJUSTMENT);
}