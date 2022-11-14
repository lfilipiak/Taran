#!/bin/python3

"""
    
    Taran

"""

import spidev
from Xbox import xbox
import time

# joy object
joy = xbox.Joystick()

# master & slave adresses
spi_bus = 0
spi_device = 0

# spi object
spi = spidev.SpiDev()
spi.open(spi_bus, spi_device)
spi.max_speed_hz = 2 ^ 20  # min 10MHz
spi.mode = 0b11
send_byte = 0


# Button configuration section
### bytes(str_1, 'UTF-8')
# buttonA = 0
# buttonB = 0
# buttonX = 0
# buttonY = 0
# buttonGuide = 0

buttonStart = 0
left_stick_X = 50
rbumper = 0
lbumper = 0

# clearing buffor on slave, stoping the motor and servo
spi.xfer2([0x0, 0x0, 0x0])

# infinite loop for reading buttons, Select (Back) ends script
while not joy.Back():

    time.sleep(1)

    print(spi.xfer2([0x0,0xA,0xFF]))

    # stoping the motors
    if joy.Start() != buttonStart:
        buttonStart = joy.Start()
        # spi.writebytes([0x0, 0x0, 0x0])

    # motors go forward, signal from 0 to 100
    if int(round(joy.rightTrigger(), 2) * 100) != rbumper:
        rbumper = int(round(joy.rightTrigger(), 2) * 100)
        # spi.writebytes([0xAA, rbumper, 0b11111111])
        # spi.xfer2([1])
        # print("RT", spi.writebytes([0xAA, rbumper, 0b11111111]))

    # motors go backwards, signal from 0 to 100
    if int(round(joy.leftTrigger(), 2) * 100) != lbumper:
        lbumper = int(round(joy.leftTrigger(), 2) * 100)
        # spi.writebytes([0xBB, lbumper, 0b11111111])
        # spi.xfer2([2])
        # print("LT", spi.writebytes([0xBB, lbumper, 0xFF]))

    # Servo left and right sweap, signal from 0 to 100
    if int(round((joy.leftX()+1)/2, 2) * 100) != left_stick_X:
        left_stick_X = int(round((joy.leftX()+1)/2, 2) * 100)
        # spi.writebytes([0xFF, left_stick_X, 0b11111111])
        # spi.xfer2([3])
        # print("LS", spi.writebytes([0xFF, left_stick_X, 0b11111111]))

# if joy.A() != buttonA:
    #     buttonA = joy.A()
    #     send_byte = buttonA
    #     spi.xfer2([0x65, send_byte, 0xFF])

    # if joy.Guide() != buttonGuide:
    #     buttonGuide = joy.Guide()
    #     spi.xfer2([0x1, 0x1, 0x1, 0x1])

    # if joy.B() != buttonB:
    #     buttonB = joy.B()
    #     send_byte = buttonB
    #     spi.xfer2([0xE, send_byte, 0xA])

    # if joy.X() != buttonX:
    #     buttonX = joy.X()
    #     send_byte = buttonX
    #     spi.xfer2([0xD, send_byte, 0xA])

    # if joy.Y() != buttonY:
    #     buttonY = joy.Y()
    #     send_byte = buttonY
    #     spi.xfer2([0xC, send_byte, 0xA])
