# Raspberry Pi Master for Arduino Slave
# i2c_master_pi.py
# Connects to Arduino via I2C
# DroneBot Workshop 2019
# https://dronebotworkshop.com

from smbus import SMBus
from Xbox import xbox

joy = xbox.Joystick()

buttonA = 0
buttonB = 0
buttonX = 0
buttonY = 0
buttonGuide = 0

buttonStart = 0
left_stick_X = 50
rbumper = 0
lbumper = 0

addr = 0x8  # bus address
bus = SMBus(1)  # indicates /dev/ic2-1
numb = 1

while not joy.Back():
	if joy.A() != buttonA:
		buttonA = joy.A()
		send_byte = buttonA
		bus.write_byte(addr, send_byte)
		print(send_byte)
	
	# # motors go forward, signal from 0 to 100
	if int(round(joy.rightTrigger(), 2) * 100) != rbumper:
		rbumper = int(round(joy.rightTrigger(), 2) * 100)
		bus.write_byte(addr, 0xAA)
		bus.write_byte(addr, rbumper)
		bus.write_byte(addr, 0xFF)
		print(rbumper)


# print ("Enter 1 for ON or 0 for OFF")
# while numb == 1:

# 	ledstate = input(">>>>   ")

# 	if ledstate == "1":
# 		bus.write_byte(addr, 0x1) # switch it on
# 	elif ledstate == "0":
# 		bus.write_byte(addr, 0x0) # switch it on
# 	else:
# 		numb = 0
