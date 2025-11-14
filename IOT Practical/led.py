import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(3,GPIO.OUT)
try:
	while True:
		GPIO.output(3,True)
		print("LED IS ON")
		time.sleep(1)
		GPIO.output(3,False)
		print("LED IS OFF")
		time.sleep(1)
except KeyboardInterrupt:
	GPIO.cleanup()
	
