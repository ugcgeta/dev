import wiringpi
from mp3 import *
ButtonPin = 20
################################################################
if __name__ == '__main__':
    
    wiringpi.wiringPiSetupGpio()

    wiringpi.pinMode(ButtonPin,0)

    MP3_load("/home/pi/dev/python/stopButton/test.mp3")
    MP3_play(1)

    while(wiringpi.digitalRead(ButtonPin)==1):
        #print('.')
        pass

    MP3_stop()
    
