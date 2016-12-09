# -*- coding: utf-8 -*-
import wiringpi
import wiringpi2
import os
import struct
from time import sleep
from datetime import datetime
OLED_I2C_ADDRESS = 0x3C


def oled_init(i2c):

    #i2c = wiringpi2.I2C()
    oled_i2c = i2c.setup(OLED_I2C_ADDRESS)
    
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


def oled_putString(i2c,y,x,string):
    if((y<0) or (y>=8) or (x<0) or (x>=128) ):
        return False
    
    oled_i2c = i2c.setup(OLED_I2C_ADDRESS)

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



def oled_putChar(i2c,y,x,string):
    if((y<0) or (y>=4) or (x<0) or (x>=128) ):
        return False
    
    oled_i2c = i2c.setup(OLED_I2C_ADDRESS)
    
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


################################################################
if __name__ == '__main__':
    
    wiringpi2.wiringPiSetup()
    
    i2c = wiringpi2.I2C()
    
    oled_init(i2c)

    #oled_putChar(i2c,1,1,(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf))
    
    oled_putString(i2c,0,1,[[0, 192, 56, 6, 56, 192, 0, 0, 60, 3, 2, 2, 2, 3, 60, 0], [254, 130, 130, 130, 196, 56, 0, 0, 63, 32, 32, 32, 32, 17, 14, 0], [240, 12, 2, 2, 2, 4, 8, 0, 7, 24, 32, 32, 32, 16, 8, 0]])
