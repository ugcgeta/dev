# -*- coding: utf-8 -*-
import os
from time import sleep
from datetime import datetime
from am2320 import *
from oled import *
from shinonome16x16FontList import *
from bmp180 import *

def _clip(inVal,minVal,maxVal):
    if(inVal<=minVal):
        return minVal
    elif(inVal>=maxVal):
        return maxVal
    else:
        return inVal


#############################################
if __name__ == '__main__':
    
    wiringpi.wiringPiSetup()
    i2c = wiringpi.I2C()

    Am2320_init(i2c)
    Oled_init(i2c)
    Bmp180_init(BMP085.BMP085_ULTRAHIGHRES)
    
    sleep(1)
    while(True):
        tmp,wet = Am2320_getSensor()
        tmpBmp,hPa,alt = Bmp180_getSensor()

        tmpString = ("%02.1f" % tmp)
        wetString = ("%02.1f" % wet)
        hPaString = ("%04.2f" % hPa)
        
        nowTime = datetime.now().strftime('%Y/%m/%d %H:%M')
        
        Oled_putString(i2c,0,0,Font_getString(nowTime))
        Oled_putString(i2c,2,2,Font_getString(tmpString+"℃"))
        Oled_putString(i2c,2,70,Font_getString(wetString+"％"))
        Oled_putString(i2c,3,0,Font_getString(hPaString+"hPa"))
        
        for secCount in range(20):
            if((secCount%2) == 0):
                Oled_putString(i2c,3,119,Font_getString("."))
            else:
                Oled_putString(i2c,3,119,Font_getString(" "))
            sleep(1)

    Am2320_close()
