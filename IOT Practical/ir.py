import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(3,GPIO.IN)

try:
	while True:
		if(GPIO.input(3)):
			print("No Object")
			time.sleep(1)
		else:
			print("Object Detected")
			time.sleep(1)
except KeyboardInterrupt:
	GPIO.cleanup()
