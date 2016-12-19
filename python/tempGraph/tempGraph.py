# -*- coding: utf-8 -*-
import os
from time import sleep
from datetime import datetime
from am2320 import *
from oled import *
from unicorn_control import *
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
    
    wiringpi2.wiringPiSetup()
    i2c = wiringpi2.I2C()

    Am2320_init(i2c)
    Oled_init(i2c)
    
    Unic_init(0,0.5)
    
    Bmp180_init(BMP085.BMP085_ULTRAHIGHRES)
    
    sleep(1)
    while(True):
        tmp,wet = Am2320_getSensor()
        tmpBmp,hPa,alt = Bmp180_getSensor()
        
        tmpString = ("%02.1f" % tmp)
        wetString = ("%02.1f" % wet)
        hPaString = ("%04.2f" % hPa)
        
        nowTime = datetime.now().strftime('%Y/%m/%d %H:%M')
        print(nowTime
              ," >>>  "
              ,wet,"%  , "
              ,tmp,"'C"
              ,tmpBmp,"'C")

        Oled_putString(i2c,0,0,Font_getString(nowTime))
        Oled_putString(i2c,1,2,Font_getString(tmpString+"℃"))
        Oled_putString(i2c,1,70,Font_getString(wetString+"％"))
        Oled_putString(i2c,2,0,Font_getString(hPaString+"hPa"))
        
        
        unicTmp = _clip(int(tmp/5   ),    0, 7)
        unicWet = _clip(int((wet-30 )/5), 0, 7)
        unichPa = _clip(int((hPa-990)/5), 0, 7)
        
        Unic_shiftLeft(0)
        Unic_addColor(0,7,3-unicTmp//2,127+127*(unicTmp%2),UNIC_SELECT_RED)
        Unic_addColor(0,7,3-unicWet//2,127+127*(unicWet%2),UNIC_SELECT_BLUE)
        Unic_addColor(0,7,3-unichPa//2,127+127*(unichPa%2),UNIC_SELECT_GREEN)
        Unic_show(0)

        sleep(10)
    
    Am2320_close()

