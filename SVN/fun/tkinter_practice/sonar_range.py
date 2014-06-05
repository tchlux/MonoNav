from serial import *
#import serial

sonar = Serial("/dev/ttyUSB0", 576000)
sonar.open()
print(sonar.read(8))
