#!/bin/python3

"""
    
    Taran

"""

import spidev

import time

# joy object
# joy = xbox.Joystick()

# master & slave adresses
spi_bus = 0
spi_device = 0

# spi object
spi = spidev.SpiDev()
spi.open(spi_bus, spi_device)
spi.max_speed_hz = 4000000
spi.mode = 0b00
send_byte = 0


# Button configuration section
### bytes(str_1, 'UTF-8')
buttonA = 0
buttonB = 0
buttonX = 0
buttonY = 0
buttonGuide = 0

buttonStart = 0
left_stick_X = 50
rbumper = 0
lbumper = 0

data = 0b00000000

# clearing buffor on slave, stoping the motor and servo
while True:
    spi.xfer2([data])
    data = data + 1
    print(bin(data))
    if data == 15:
        data = 0
    time.sleep(0.5)

# infinite loop for reading buttons, Select (Back) ends script
# while not joy.Back():

    # print(spi.xfer2([0x0,0xA,0xFF]))

    # # stoping the motors
    # if joy.Start() != buttonStart:
    #     buttonStart = joy.Start()
    #     spi.xfer2([0x0, 0x0, 0x0])

    # # motors go forward, signal from 0 to 100
    # if int(round(joy.rightTrigger(), 2) * 100) != rbumper:
    #     rbumper = int(round(joy.rightTrigger(), 2) * 100)
    #     spi.xfer2([0xAA, rbumper, 0xFF])
    #     print("data send")

    # # motors go backwards, signal from 0 to 100
    # if int(round(joy.leftTrigger(), 2) * 100) != lbumper:
    #     lbumper = int(round(joy.leftTrigger(), 2) * 100)
    #     spi.xfer2([0xBB, lbumper, 0xFF])

    # # Servo left and right sweap, signal from 0 to 100
    # if int(round((joy.leftX()+1)/2, 2) * 100) != left_stick_X:
    #     left_stick_X = int(round((joy.leftX()+1)/2, 2) * 100)
    #     spi.xfer2([0xFF, left_stick_X, 0xFF])

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
