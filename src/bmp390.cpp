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
float temperature, pressure, altitudeAltimeter, previousAltitude, groundLevel;

// Constants for moving average filter
const int WINDOW_SIZE = 5;
// Buffers for moving average filter
float altitudeBuffer[WINDOW_SIZE] = {0};
float altitudeSum = 0;
int altitudeIndex = 0;


// Function to initialize BMP390 sensor
void initBMP390() {
  Serial5.println(("Initializing BMP390..."));
  groundLevel = 0.0;
  // Start the I2C bus on pins 37 (SDA1) and 38 (SCL1)
  Wire1.begin();
  delay(100);

  // Check if BMP3 sensor is connected
  if (!bmp.begin_I2C()) {
    Serial5.println(("Could not find a valid BMP3 sensor, check wiring!"));
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(TEMP_OVERSAMPLING);
  bmp.setPressureOversampling(PRESSURE_OVERSAMPLING);
  bmp.setIIRFilterCoeff(IIR_FILTER_COEFF);
  bmp.setOutputDataRate(OUTPUT_DATA_RATE);

  Serial5.println(("BMP390 initialized successfully."));
  bmp.performReading(); // Perform an initial reading to set the ground level
  delay(150);
  bmp.performReading(); // Perform an initial reading to set the ground level
  delay(150);
  bmp.performReading(); // Perform an initial reading to set the ground level
  groundLevel = bmp.readAltitude(ALTITUDE_ADJUSTMENT);
}

// Function to read data from BMP390 sensor
void readBMP390() {
  // Perform sensor reading
  if (!bmp.performReading()) {
    Serial5.println("Failed to perform reading :(");
  }

  // Store sensor readings in variables
  temperature = bmp.temperature;
  pressure = bmp.pressure / 100.0;
  previousAltitude = altitudeAltimeter; // Store the current altitude to previousAltitude before updating it

  // Update altitude buffer
  altitudeSum -= altitudeBuffer[altitudeIndex];
  altitudeBuffer[altitudeIndex] = bmp.readAltitude(ALTITUDE_ADJUSTMENT);
  altitudeSum += altitudeBuffer[altitudeIndex];
  altitudeIndex = (altitudeIndex + 1) % WINDOW_SIZE;

  // Calculate moving average of altitude
  altitudeAltimeter = altitudeSum / WINDOW_SIZE;
}