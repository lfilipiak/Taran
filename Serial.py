#!/usr/bin/python3

import serial
from Xbox import xbox

joy = xbox.Joystick()

buttonA = 0
buttonB = 0
buttonX = 0
buttonY = 0
buttonGuide = 0

buttonStart = 0
leftStickX = 50
rbumper = 0
lbumper = 0

if __name__ == "__main__":
    # ser = serial.Serial('/dev/ttyACM1', 9600, timeout=1)
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()

    while True:
        if joy.A() != buttonA:
            buttonA = joy.A()
            send_byte = buttonA
            msg = f"Pressed_A_{send_byte}\n"
            ser.write(msg.encode())
            print(f"Pressed_A_{send_byte}\n")

        if int(round(joy.rightTrigger(), 2) * 100) != rbumper:
            rbumper = int(round(joy.rightTrigger(), 2) * 100)
            send_byte = rbumper
            msg = f"rbumper_{send_byte}\n"
            ser.write(msg.encode())
            print(f"rbumper_{send_byte}")

        if int(round(joy.leftTrigger(), 2) * 100) != lbumper:
            lbumper = int(round(joy.leftTrigger(), 2) * 100)
            send_byte = lbumper
            msg = f"lbumper_{send_byte}\n"
            ser.write(msg.encode())
            print(f"lbumper_{send_byte}")

            # Servo left and right sweap, signal from 0 to 100
        if int(round((joy.leftX()+1)/2, 2) * 100) != leftStickX:
            leftStickX = int(round((joy.leftX()+1)/2, 2) * 100)
            send_byte = leftStickX
            msg = f"leftStickX_{send_byte}\n"
            ser.write(msg.encode())
            print(f"leftStickX_{send_byte}")

        # ledstate = input(">>>>    ")
        # if ledstate == "1":
        #     ser.write(b"power_on\n")
        # elif ledstate == "0":
        #     ser.write(b"power_off\n")
