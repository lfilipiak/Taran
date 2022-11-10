#!/bin/python3

import spidev
from Xbox import xbox
import time


joy = xbox.Joystick()

spi_bus = 0
spi_device = 0

spi = spidev.SpiDev()
spi.open(spi_bus, spi_device)
spi.max_speed_hz = 2 ^ 20  # min 10MHz
spi.mode = 0b00

send_byte = 0

buttonA = 0
buttonB = 0
buttonX = 0      # bytes(str_1, 'UTF-8')
buttonY = 0
buttonStart = 0
buttonGuide = 0

left_stick_X = 0
rbumper = 0
lbumper = 0

# spi.xfer2([0,0,0])
# print("empty frame was send")

while not joy.Back():

    if joy.A() != buttonA:
        buttonA = joy.A()
        send_byte = buttonA
        spi.xfer2([0xF])
        spi.xfer2([send_byte])
        spi.xfer2([0xA])

    if int(round((joy.leftX()+1)/2, 2) * 100) != left_stick_X:
        left_stick_X = int(round((joy.leftX()+1)/2, 2) * 100)
        spi.xfer2([0xF5, 0x00, left_stick_X, 0xB5])

    if joy.Start() != buttonStart:
        buttonStart = joy.Start()
        spi.xfer2([0x0, 0x0, 0x0, 0x0])

    if joy.Guide() != buttonGuide:
        buttonGuide = joy.Guide()
        spi.xfer2([0x1, 0x1, 0x1, 0x1])

    if joy.B() != buttonB:
        buttonB = joy.B()
        send_byte = buttonB
        spi.xfer2([0xE, send_byte, 0xA])

    if joy.X() != buttonX:
        buttonX = joy.X()
        send_byte = buttonX
        spi.xfer2([0xD, send_byte, 0xA])

    if joy.Y() != buttonY:
        buttonY = joy.Y()
        send_byte = buttonY
        spi.xfer2([0xC, send_byte, 0xA])

    if int(round(joy.rightTrigger(), 2) * 100) != rbumper:
        rbumper = int(round(joy.rightTrigger(), 2) * 100)
        spi.xfer2([0xCC, 0xFF, rbumper, 0xA])

    if int(round(joy.leftTrigger(), 2) * 100) != lbumper:
        lbumper = int(round(joy.leftTrigger(), 2) * 100)
        spi.xfer2([0xDD, 0xFF, lbumper, 0xA])
        print([0xDD, 0xFF, lbumper, 0xA])
