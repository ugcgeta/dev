# -*- coding: utf-8 -*-
import os
import wiringpi
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

def makeLogFileName():
    today = datetime.today()
    logFileName = today.strftime("%Y%m%d_%H%M%S")+'.log'
    print("Log FileName = ", logFileName)

    return logFileName

#############################################
if __name__ == '__main__':
    
    wiringpi.wiringPiSetup()
    i2c = wiringpi.I2C()

    Am2320_init(i2c)
    Oled_init(i2c)
    Bmp180_init(BMP085.BMP085_ULTRAHIGHRES)
    
    #today = datetime.today()
    #logFileName = today.strftime("%Y%m%d_%H%M%S")+'.log'
    #print("Log FileName = ", logFileName)
    f = open(makeLogFileName(), 'w')
    
    sleep(1)
    while(True):
        nowTime = datetime.now().strftime('%H:%M')

        tmp,wet = Am2320_getSensor()
        try:
            tmpBmp,hPa,alt = Bmp180_getSensor()
        except:
            i2c.write(0x00,0x06)  # reset I2C

        tmpString = ("%02.1f" % tmp)
        wetString = ("%02.1f" % wet)
        hPaString = ("%04.2f" % hPa)
       
        try:
            Oled_putStringX2(i2c,0,20,Font_getString(nowTime))
            Oled_putString(i2c,2,2,Font_getString(tmpString+"℃"))
            Oled_putString(i2c,2,70,Font_getString(wetString+"％"))
            Oled_putString(i2c,3,0,Font_getString(hPaString+"hPa"))
        except:
            i2c.write(0x00,0x06)  # reset I2C

        logTime = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        f.write(logTime+' '+tmpString+"℃ "+ wetString+"％ " + hPaString+"hPa" + '\n')
        print(logTime+' '+tmpString+"℃ "+ wetString+"％ " + hPaString+"hPa")
        

        for secCount in range(20):
            if((secCount%2) == 0):
                Oled_putString(i2c,3,100,Font_getString("----"))
            else:
                Oled_putString(i2c,3,100,Font_getString("    "))
            sleep(1)

    f.close()
    Am2320_close()

