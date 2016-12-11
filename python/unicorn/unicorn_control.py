# -*- coding: utf-8 -*-
import unicornhat as unicorn
import struct
import os
from time import sleep

AM2320_I2C_SLEEP_ERROR = -1
UNIC_GROUNG_FORE = 0
UNIC_GROUNG_BACK = 1

UnicWidth = 8
UnicHeight = 4
UnicForeList = []
UnicBackList = []
def Unic_init(rotation=0,brightness=0.5):
    global UnicWidth
    global UnicHeight

    global UnicForeList
    global UnicBackList
    unicorn.set_layout(unicorn.AUTO)
    unicorn.rotation(rotation)
    unicorn.brightness(brightness)
    UnicWidth,UnicHeight=unicorn.get_shape()

    for y in range(UnicHeight):
        for x in range(UnicWidth):
            UnicForeList.append([0,0,0])
            UnicBackList.append([False,0,0,0])


def _pixToList(x,y):
    return y*UnicWidth+x
def _clipValue(min,max,val):
    if(val<min):
        return min
    elif(val>max):
        return max
    else:
        return val


def Unic_setPixel(x,y,red,green,blue):
    global UnicForeList
    global UnicBackList

    rgbFore = [abs(red),abs(green),abs(blue)]

    UnicForeList[_pixToList(x,y)] = rgbFore

#    if((red<0) or (green<0) or (blue<0)):
#        rgbBack = [clipValue(0,255,red)
#                   ,clipValue(0,255,green)
#                   ,clipValue(0,255,blue)]
#        UnicBackList[_pixToList(x,y)] = (True,rgbBack)
 #   else:
 #       UnicBackList[_pixToList(x,y)] = (False,)

    unicorn.set_pixel(x,y,red,green,blue)

def Unic_show(ground=0):
    
#    if(ground == UNIC_GROUNG_BACK):
#        for x in range(UnicWidth):
#            for y in range(UnicHeight):
#                unicorn.set_pixel(x,y,red,green,blue)
    unicorn.show()
##############################################
if __name__ == '__main__':
    
    Unic_init(0,0.9)
    Unic_setPixel(1,2,0,255,0)
    
    Unic_show()
    sleep(5)

    for x in range(UnicWidth):
        for y in range(UnicHeight):
            rgb = (x*32,0,y*64)
            Unic_setPixel(x,y,*rgb)
            Unic_show()
            sleep(1)
    sleep(5)


