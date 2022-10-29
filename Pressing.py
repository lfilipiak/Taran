import time
from Xbox import xbox
from sys import exit
from smbus import SMBus

addr = 0x2  # bus address
bus = SMBus(1)  # indicates /dev/ic2-1


joy = xbox.Joystick()

print("Press A B Y X")

while not joy.Back():

    if joy.A():
        print("Pressed A")
        time.sleep(0.1)
    elif joy.B():
        print("Pressed B")
        time.sleep(0.1)
    elif joy.Y():
        print("Pressed Y")
        time.sleep(0.1)
    elif joy.X():
        print("Pressed X")
        time.sleep(0.1)
    elif joy.Start():
        print("Bye")
        exit(0)
    elif joy.leftStick():
        print(round(joy.leftStick()[0], 2), round(joy.leftStick()[1], 2))
        time.sleep(0.1)
