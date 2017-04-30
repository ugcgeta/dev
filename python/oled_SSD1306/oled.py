# -*- coding: utf-8 -*-
import wiringpi
#import wiringpi2
import os
import struct
from time import sleep
from datetime import datetime
OLED_I2C_ADDRESS = 0x3C

_Oled_i2c = 0

def Oled_init(i2c):
    global _Oled_i2c
    #i2c = wiringpi.I2C()
    _Oled_i2c = i2c.setup(OLED_I2C_ADDRESS)
    oled_i2c = _Oled_i2c

    i2c.writeReg8(oled_i2c,0x00,0xAE)  # display off
    i2c.writeReg8(oled_i2c,0x00,0xA4)  # RAM reset
    #i2c.writeReg8(oled_i2c,0x00,0xA5)  # Entire display ON


    i2c.writeReg8(oled_i2c,0x00,0xA1)  # Segment Remap
    i2c.writeReg8(oled_i2c,0x00,0xC8)  # Com Direction remap


    i2c.writeReg8(oled_i2c,0x00,0x00)  # set lower column address
    i2c.writeReg8(oled_i2c,0x00,0x10)  # set higher column address
    i2c.writeReg8(oled_i2c,0x00,0x40)  # set display start line
    i2c.writeReg8(oled_i2c,0x00,0x2E)  # Deactivate scrollスクロール表示解除
    
    i2c.writeReg8(oled_i2c,0x00,0x21)  # set Column Address
    i2c.writeReg8(oled_i2c,0x00,0x00)  # Column Start Address←水平開始位置はここで決める(0～126)
    i2c.writeReg8(oled_i2c,0x00,0x7f)  # Column Stop Address　画面をフルに使う

    i2c.writeReg8(oled_i2c,0x00,0x22)  # Set Page Address
    i2c.writeReg8(oled_i2c,0x00,0x00)  # start page address
    i2c.writeReg8(oled_i2c,0x00,0x07)  # stop page address

    i2c.writeReg8(oled_i2c,0x00,0xB0)  # set page start address←垂直開始位置はここで決める8bitで１ページ(B0～B7)

    i2c.writeReg8(oled_i2c,0x00,0x81)  # contrast control コントラスト設定オン
    i2c.writeReg8(oled_i2c,0x00,0x7F)  # 127　コントラスト0-127

    i2c.writeReg8(oled_i2c,0x00,0xA6)  # normal / reverse A7ならば白黒反転
    #i2c.writeReg8(oled_i2c,0x00,0xC0)  # Com scan direction←開始位置を右下から始める
    i2c.writeReg8(oled_i2c,0x00,0x8d)  # set charge pump enableチャージポンプを入れないと表示されない
    i2c.writeReg8(oled_i2c,0x00,0x14)  # charge pump ON

    i2c.writeReg8(oled_i2c,0x00,0xAF)  # display ON




    # Clear Display ディスプレイを黒で塗りつぶす
    for i in range(0 , 8):
        i2c.writeReg8(oled_i2c,0x00,0x40)  # set display start line
        i2c.writeReg8(oled_i2c,0x00,0xB0 + i)  # set page start address←垂直開始位置はここで決める8bitで１ページ(B0～B7)
        
        i2c.writeReg8(oled_i2c,0x00,0x21) # set column addres
        i2c.writeReg8(oled_i2c,0x00,0x00) # start column addres←水平開始位置はここで決める(0～126)
        i2c.writeReg8(oled_i2c,0x00,0x7F) # stop column addres 画面をフルに使う
        #i2c.writeReg16(oled_i2c,0x21,0x7F00)

        # 水平ライン表示
        for j in range(0 , 16): # column = 8bit X 16 ←8バイト毎に水平に連続で16個表示
            for k in range(0 , 8):
            #for k in range(0 , 4):
                i2c.writeReg8(oled_i2c,0x40,0x00)


def Oled_putString(i2c,y,x,string):
    if((y<0) or (y>=8) or (x<0) or (x>=128) ):
        return False
    
    oled_i2c = _Oled_i2c

    fontSize = 0
    nextFontOffset = 0
    for font in string:
        for line in range(0,2):
            i2c.writeReg8(oled_i2c,0x00,0xB0 + y*2 + line )  # 垂直開始位置
            i2c.writeReg8(oled_i2c,0x00,0x21) # set column addres
            i2c.writeReg8(oled_i2c,0x00,0x00+x+nextFontOffset) # start column addres
            i2c.writeReg8(oled_i2c,0x00,0x7F) # stop column addres 
            
            fontSize = (int)(len(font)/2)
            startPos = 0 + fontSize * line
            endPos   = fontSize + fontSize * line
            for i in range(startPos , endPos):
                i2c.writeReg8(oled_i2c,0x40,font[i])

        nextFontOffset += fontSize

def Oled_putStringX2(i2c,y,x,string):
    cursolPos = x
    for font in string:
        cursolPos = Oled_putCharX2(i2c,y,cursolPos,font)
        #print(cursolPos)

def Oled_putChar(i2c,y,x,string):
    if((y<0) or (y>=4) or (x<0) or (x>=128) ):
        return False
    
    oled_i2c = _Oled_i2c
    
    fontSize = (int)(len(string)/2)
    for line in range(0,2):
        i2c.writeReg8(oled_i2c,0x00,0xB0 + y*2 + line )  # 垂直開始位置
        i2c.writeReg8(oled_i2c,0x00,0x21) # set column addres
        i2c.writeReg8(oled_i2c,0x00,0x00+x) # start column addres
        i2c.writeReg8(oled_i2c,0x00,0x7F) # stop column addres 
        
        startPos = 0 + fontSize * line
        endPos   = fontSize + fontSize * line
        for i in range(startPos , endPos):
            i2c.writeReg8(oled_i2c,0x40,string[i])

def Oled_putCharX2(i2c,y,x,string):
    if((y<0) or (y>=2) or (x<0) or (x>=96) ):
        return False
    
    oled_i2c = _Oled_i2c
   
    fontX2 = []
    for lineX2 in range(2):
        lineX2start = lineX2 * 8
        lineX2end = lineX2 * 8 + 8
        
        for line in range(2):
            for i,font in enumerate(string):
                if((i>=lineX2end) or  (i<lineX2start)):
                    pass
                else:
                    if(line==0):
                        temp = font & 0x0F
                    else:
                        temp = (font & 0xF0)>>4
                    #print(line,font,temp)
                    tempX2=0x00
                    for n in range(4):
                        if(temp & (0x01<<n)):
                            tempX2 = tempX2 + (0x03<<(n*2))
                    fontX2.append(tempX2)
                    fontX2.append(tempX2)

        
    fontSize = (int)(len(string)/2)*2
    for line in range(0,4):
        i2c.writeReg8(oled_i2c,0x00,0xB0 + y*4 + line )  # 垂直開始位置
        i2c.writeReg8(oled_i2c,0x00,0x21) # set column addres
        i2c.writeReg8(oled_i2c,0x00,0x00+x) # start column addres
        i2c.writeReg8(oled_i2c,0x00,0x7F) # stop column addres 
        
        startPos = 0 + fontSize * line
        endPos   = fontSize + fontSize * line
        for i in range(startPos , endPos):
            i2c.writeReg8(oled_i2c,0x40,fontX2[i])
    #print(fontX2)
    return x+fontSize


################################################################
if __name__ == '__main__':
    
    wiringpi.wiringPiSetup()
    
    i2c = wiringpi.I2C()
    
    Oled_init(i2c)

    #Oled_putCharX2(i2c,0,0,[0, 192, 56, 6, 56, 192, 0, 0, 60, 3, 2, 2, 2, 3, 60, 0])
    #Oled_putChar(i2c,1,1,(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf))
    
    Oled_putStringX2(i2c,0,1,[[0, 192, 56, 6, 56, 192, 0, 0, 60, 3, 2, 2, 2, 3, 60, 0], [254, 130, 130, 130, 196, 56, 0, 0, 63, 32, 32, 32, 32, 17, 14, 0], [240, 12, 2, 2, 2, 4, 8, 0, 7, 24, 32, 32, 32, 16, 8, 0]])
    #Oled_putString(i2c,2,1,[[0, 192, 56, 6, 56, 192, 0, 0, 60, 3, 2, 2, 2, 3, 60, 0], [254, 130, 130, 130, 196, 56, 0, 0, 63, 32, 32, 32, 32, 17, 14, 0], [240, 12, 2, 2, 2, 4, 8, 0, 7, 24, 32, 32, 32, 16, 8, 0]])
