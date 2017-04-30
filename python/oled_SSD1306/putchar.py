# -*- coding: utf-8 -*-
import wiringpi
#import wiringpi2
import os
import struct
from time import sleep
from datetime import datetime
from shinonome16x16FontList import Font_getChar, Font_getString
from oled import Oled_init,Oled_putString,Oled_putChar


def Oled_putFonts(i2c,y,x,string):

    Oled_putString(i2c,y,x,Font_getString(string))


######################################################
if __name__ == '__main__':
    
    wiringpi.wiringPiSetup()
    i2c = wiringpi.I2C()
    Oled_init(i2c)
    
    string = ("君の名はという","もう見ましたか","名作らしいですよ")
    
    Oled_putFonts(i2c,0,0,string[0])
    Oled_putFonts(i2c,1,0,string[1])
    Oled_putFonts(i2c,2,0,string[2])

   # Oled_putString(i2c,0,0,Font_getString(string[0]))
   # Oled_putString(i2c,1,0,Font_getString(string[1]))
   # Oled_putString(i2c,2,0,Font_getString(string[2]))
    print(Font_getString(string[0]))

    #Oled_putChar(i2c,0,0,Font_getChar("A"))
    #print(Font_getChar("あ"))

