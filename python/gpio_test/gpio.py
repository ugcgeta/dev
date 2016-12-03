# coding: UTF-8
######################################################################
import RPi.GPIO as GPIO
import time

if __name__ == '__main__':
    # Use GPIO numbers not pin numbers
    GPIO.setmode(GPIO.BCM)
    
    # set up the GPIO channels - one input and one output
    GPIO.setup(21, GPIO.OUT)
    
    # output to GPIO21
    GPIO.output(21, True)
    time.sleep(4.0)

    # output to GPIO21
    GPIO.output(21, False)
    time.sleep(4.0)
    
    GPIO.cleanup()


