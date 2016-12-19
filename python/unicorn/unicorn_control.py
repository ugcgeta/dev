# -*- coding: utf-8 -*-
import unicornhat as unicorn
import struct
import os
from time import sleep

UNIC_PLANE_MAX = 8
UNIC_SELECT_RED = 0
UNIC_SELECT_GREEN = 1
UNIC_SELECT_BLUE = 2

# LEDの水平、垂直幅
_UnicWidth = 8
_UnicHeight = 4

# 現在のLED値8面分
_UnicPlaneList = []
_UnicPlaneNow = 0
_UnicAllUpdate = True
def Unic_init(rotation=0,brightness=0.5):
    global _UnicWidth
    global _UnicHeight

    global _UnicPlaneList
	
    unicorn.set_layout(unicorn.AUTO)
    unicorn.rotation(rotation)
    unicorn.brightness(brightness)
    _UnicWidth,_UnicHeight=unicorn.get_shape()

    for plane in range(UNIC_PLANE_MAX):
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

    _UnicPlaneList[_pixToList(plane,x,y)] = rgb

    if(plane == _UnicPlaneNow):
        unicorn.set_pixel(x,y,red,green,blue)

# 座標のRGB値を取得
def Unic_getPixel(plane,x,y):
    
    rgb = _UnicPlaneList[_pixToList(plane,x,y)]
    return rgb

def Unic_addColor(plane,x,y,color,selectRGB):
    global _UnicPlaneList

    nowRed,nowGreen,nowBlue = Unic_getPixel(plane,x,y)
    if(selectRGB == UNIC_SELECT_RED):
        rgb = [color,nowGreen,nowBlue]
    elif(selectRGB == UNIC_SELECT_GREEN):
        rgb = [nowRed,color,nowBlue]
    elif(selectRGB == UNIC_SELECT_BLUE):
        rgb = [nowRed,nowGreen,color]
    else:
        rgb = [nowRed,nowGreen,nowBlue]

    _UnicPlaneList[_pixToList(plane,x,y)] = rgb
    if(plane == _UnicPlaneNow):
        unicorn.set_pixel(x,y,*rgb)



#表示全体をシフト
def Unic_shiftLeft(plane,shiftWidth=1):
    global _UnicPlaneList
    
    for y in range(_UnicHeight):
        #print(_pixToList(plane,0,y))
        del (_UnicPlaneList[_pixToList(plane,0,0)])
        _UnicPlaneList.insert(_pixToList(plane,_UnicWidth-1,_UnicHeight-1),[0,0,0])
    
    _UnicAllUpdate = True

# プレーン番号の更新
# 番号更新時のLED情報を更新
def Unic_setPlane(plane):
    global _UnicPlaneNow

    _UnicPlaneNow = abs(plane)
    _UnicAllUpdate = True

# 表示
# 表示プレーンと現在のプレーンが異なる場合はLED情報を更新してから表示
def Unic_show(plane=_UnicPlaneNow, forceUpdate=_UnicAllUpdate):
    
    global _UnicAllUpdate

    # 現在の表示プレーンと異なる場合は、
    # 指定されたプレーンのRGB値で出力値を上書きする
    if((plane != _UnicPlaneNow) or forceUpdate):
     #   print("aaaaa")
        Unic_setPlane(plane)
        for x in range(_UnicWidth):
            for y in range(_UnicHeight):
                rgb = _UnicPlaneList[_pixToList(_UnicPlaneNow,x,y)]
                unicorn.set_pixel(x,y,*rgb)
    
    unicorn.show()
    _UnicAllUpdate = False
    
##############################################
if __name__ == '__main__':
    
    Unic_init(0,0.999)
    Unic_setPixel(0,1,3,0,255,0)
    Unic_setPixel(1,0,0,0,255,0)

    Unic_shiftLeft(0)
    Unic_show(0)
    sleep(2)
    for x in range(_UnicWidth):
        for y in range(_UnicHeight):
            rgb = (x*32,0,y*64)
            Unic_setPixel(0,x,y,*rgb)
    for i in range(8):
        Unic_setPixel(0,7,2,128,128,128)
        Unic_show(0)
        print(_UnicPlaneList[0:32])
        print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",i)
        Unic_shiftLeft(0)

        sleep(1)

    Unic_show(1)
    sleep(5)
    
    for x in range(_UnicWidth):
        for y in range(_UnicHeight):
            rgb = (x*32,0,y*64)
            Unic_setPixel(2,x,y,*rgb)
            Unic_show(2)
            sleep(1)
    sleep(5)


