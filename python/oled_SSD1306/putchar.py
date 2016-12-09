# -*- coding: utf-8 -*-
import wiringpi
import wiringpi2
import os
import struct
from time import sleep
from datetime import datetime
from shinonome16x16FontList import putFont, putsFontArray
from oled import oled_init,oled_putString,oled_putChar

######################################################
if __name__ == '__main__':
    
    wiringpi2.wiringPiSetup()
    i2c = wiringpi2.I2C()
    oled_init(i2c)
    
    string = ("君の名はという","もう見ましたか","名作らしいです")

    oled_putString(i2c,0,0,putsFontArray(string[0]))
    oled_putString(i2c,1,0,putsFontArray(string[1]))
    oled_putString(i2c,2,0,putsFontArray(string[2]))
    print(putsFontArray(string[0]))

    #oled_putChar(i2c,0,0,putFont("A"))
    #print(putFont("あ"))

