#!/bin/python3

### test 123 ###

import time
from Xbox import xbox
from sys import exit
from smbus import SMBus

DEVICE_BUS = 1

addr = 0x2  # bus address
bus = SMBus(DEVICE_BUS)  # indicates /dev/ic2-1

joy = xbox.Joystick()

print("Press A B Y X")

data = ""

while not joy.Back():

    print("A ", joy.A(), "B ", joy.B(), "X ", joy.X(), "Y ", joy.Y(), "\t"
          "L Stick ", round(joy.leftStick()[0], 2), round(joy.leftStick()[1], 2), "R Stick ", round(joy.rightStick()[0], 2), round(joy.rightStick()[1], 2), "\t", "R Bumper", joy.rightBumper(), "R Trigger ", round(joy.rightTrigger(), 2))
    time.sleep(0.05)

    if joy.Start():
        print("Bye")
        exit(0)
