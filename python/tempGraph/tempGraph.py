# -*- coding: utf-8 -*-
import os
from time import sleep
from datetime import datetime
from am2320 import *
from oled import *
from unicorn_control import *
from shinonome16x16FontList import *
#############################################
if __name__ == '__main__':
    
    wiringpi2.wiringPiSetup()
    i2c = wiringpi2.I2C()
#    am2320 = i2c.setup(0x5C)

    Am2320_init(i2c)
    Oled_init(i2c)
    
    Unic_init(0,0.5)
    
    sleep(5)
    #for var in range(0, 100):
    while(True):
        tmp,wet = Am2320_getSensor()
        print(datetime.now().strftime('%X')," >>>  ",wet,"%  , ",tmp,"'C")

        Oled_putString(i2c,0,0,Font_getString(datetime.now().strftime('%X')))
        Oled_putString(i2c,2,0,Font_getString(str(tmp)+"℃"))
        Oled_putString(i2c,3,0,Font_getString(str(wet)+"％"))

        Unic_setPixel(0,int(tmp/5),0,255,0,0)
        Unic_setPixel(0,int((wet-30)/6),2,0,0,255)
        Unic_show(0)

        sleep(1)
    
    Am2320_close()

