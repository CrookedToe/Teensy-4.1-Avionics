import serial

ser = serial.Serial('COM3', 115200)  # Change 'COM3' to your port
while True:
    line = ser.readline().decode('utf-8').strip()  # Read a line from the serial port
    gyroX, gyroY, gyroZ = map(float, line.split(','))  # Parse the line into variables