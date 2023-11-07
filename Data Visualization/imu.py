import serial
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import math

ser = serial.Serial('COM9', 115200)  # Change 'COM3' to your port

plt.ion()  # Turn on interactive mode
fig = plt.figure()  # Create a figure
ax = fig.add_subplot(111, projection='3d')  # Create a 3D axes

# Create a 3D arrow (initially pointing in the +X direction)
arrow = ax.quiver(0, 0, 0, 1, 0, 0)

def quat_to_euler(qi, qj, qk, qr):
    # Compute Euler angles (roll, pitch, yaw) from quaternion
    ysqr = qj * qj

    t0 = +2.0 * (qr * qi + qj * qk)
    t1 = +1.0 - 2.0 * (qi * qi + ysqr)
    X = math.atan2(t0, t1)

    t2 = +2.0 * (qr * qj - qk * qi)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    Y = math.asin(t2)

    t3 = +2.0 * (qr * qk + qi * qj)
    t4 = +1.0 - 2.0 * (ysqr + qk * qk)
    Z = math.atan2(t3, t4)

    return X, Y, Z  # roll, pitch, yaw

def update_arrow():
    line_data = ser.readline().decode('utf-8').strip()  # Read a line from the serial port
    if ': ' in line_data:
        data_type, values = line_data.split(': ')
        values = list(map(float, values.split(',')))  # Convert the values to floats

        if data_type == 'Quat':
            quatI, quatJ, quatK, quatReal = values
            # Convert quaternion to Euler angles
            eulerX, eulerY, eulerZ = quat_to_euler(quatI, quatJ, quatK, quatReal)
            # Normalize the Euler angles
            magnitude = np.sqrt(eulerX**2 + eulerY**2 + eulerZ**2)
            eulerX /= magnitude
            eulerY /= magnitude
            eulerZ /= magnitude
            # Update the arrow's direction
            arrow.set_segments([[(0, 0, 0), (eulerX, eulerY, eulerZ)]])
            plt.draw()  # Redraw the plot
            plt.pause(0.01)  # Pause for a short period to allow the plot to update
while True:
    update_arrow()