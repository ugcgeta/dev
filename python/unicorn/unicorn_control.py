# -*- coding: utf-8 -*-
import unicornhat as unicorn
import struct
import os
from time import sleep

UNIC_GROUNG_FORE = 0
UNIC_GROUNG_BACK = 1
UNIC_PLANE_MAX = 8

# LEDの水平、垂直幅
__UnicWidth = 8
__UnicHeight = 4

# 現在のLED値8面分
_UnicPlaneList = []
_UnicPlaneNow = 0

def Unic_init(rotation=0,brightness=0.5):
    global _UnicWidth
    global _UnicHeight

    global UnicForeList
    global UnicBackList
    unicorn.set_layout(unicorn.AUTO)
    unicorn.rotation(rotation)
    unicorn.brightness(brightness)
    _UnicWidth,_UnicHeight=unicorn.get_shape()

    for x in range(_UnicWidth):
    	for y in range(_UnicHeight):
            _UnicPlaneList.append([0,0,0])

# xy座標をindexに変換
def _pixToList(p,x,y):
    return y + x*_UnicHeight + p*(_UnicHeight*_UnicWidth)

# 値のクリップ
def _clipValue(min,max,val):
    if(val<min):
        return min
    elif(val>max):
        return max
    else:
        return val

# 座標にRGB値を設定
def Unic_setPixel(plane,x,y,red,green,blue):
    global _UnicPlaneList
    
    rgb = [abs(red),abs(green),abs(blue)]

    UnicForeList[_pixToList(plane,x,y)] = rgb

    if(plane == _UnicPlaneNow):
        unicorn.set_pixel(x,y,red,green,blue)

# プレーン番号の更新
# 番号更新時のLED情報を更新

# 表示
# 表示プレーンと現在のプレーンが異なる場合はLED情報を更新してから表示
def Unic_show(plane=0):
    
	if(plane != _UnicPlaneNow):
		_UnicPlaneNow = plane
		
    unicorn.show()
    
##############################################
if __name__ == '__main__':
    
    Unic_init(0,0.9)
    Unic_setPixel(1,2,0,255,0)
    
    Unic_show()
    sleep(5)

    for x in range(_UnicWidth):
        for y in range(_UnicHeight):
            rgb = (x*32,0,y*64)
            Unic_setPixel(x,y,*rgb)
            Unic_show()
            sleep(1)
    sleep(5)


