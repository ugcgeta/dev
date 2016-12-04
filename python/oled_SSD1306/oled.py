# -*- coding: utf-8 -*-
import wiringpi
import wiringpi2
import os
import struct
from time import sleep
from datetime import datetime


def oled_init(wiringpi2):

    i2c = wiringpi2.I2C()
    oled_i2c = i2c.setup(0x3C)
    
    print(i2c.write(oled_i2c,0xAE))  # display off
    i2c.write(oled_i2c,0xA4)  # RAM reset
    i2c.write(oled_i2c,0xA5)  # Entire display ON
    i2c.write(oled_i2c,0x00)  # set lower column address
    i2c.write(oled_i2c,0x10)  # set higher column address
    i2c.write(oled_i2c,0x00)  # set display start line
    i2c.write(oled_i2c,0x2E)  # Deactivate scrollスクロール表示解除
    
    #i2c.write(oled_i2c,0x21)  # set Column Address
    #i2c.write(oled_i2c,0x00)  # Column Start Address←水平開始位置はここで決める(0～126)
    #i2c.write(oled_i2c,0x7f)  # Column Stop Address　画面をフルに使う
    i2c.writeReg16(oled_i2c,0x21,0x7F00)

    #i2c.write(oled_i2c,0x22)  # Set Page Address
    #i2c.write(oled_i2c,0x00)  # start page address
    #i2c.write(oled_i2c,0x07)  # stop page address
    i2c.writeReg16(oled_i2c,0x22,0x0700)

    i2c.write(oled_i2c,0xB0)  # set page start address←垂直開始位置はここで決める8bitで１ページ(B0～B7)

    #i2c.write(oled_i2c,0x81)  # contrast control コントラスト設定オン
    #i2c.write(oled_i2c,0x7F)  # 127　コントラスト0-127
    i2c.writeReg8(oled_i2c,0x81,0x7F)

    i2c.write(oled_i2c,0xA6)  # normal / reverse A7ならば白黒反転
    i2c.write(oled_i2c,0xC0)  # Com scan direction←開始位置を右下から始める
    #i2c.write(oled_i2c,0x8d)  # set charge pump enableチャージポンプを入れないと表示されない
    #i2c.write(oled_i2c,0x14)  # charge pump ON
    i2c.writeReg8(oled_i2c,0x8d,0x14)

    i2c.write(oled_i2c,0xAF)  # display ON
    # Clear Display ディスプレイを黒で塗りつぶす
    for i in range(0 , 8):
        i2c.write(oled_i2c,0x00)  # set display start line
        i2c.write(oled_i2c,0xB0 + i)  # set page start address←垂直開始位置はここで決める8bitで１ページ(B0～B7)
        
        #i2c.write(oled_i2c,0x21) # set column addres
        #i2c.write(oled_i2c,0x00) # start column addres←水平開始位置はここで決める(0～126)
        #i2c.write(oled_i2c,0x7F) # stop column addres 画面をフルに使う
        i2c.writeReg16(oled_i2c,0x21,0x7F00)

        # 水平ライン表示
        for j in range(0 , 16): # column = 8bit X 16 ←8バイト毎に水平に連続で16個表示
            i2c.write(oled_i2c,0x40)  # Set Display Start Line ←このコマンドが実際のビットを書き込むコマンドらしい
            for k in range(0 , 8):
                i2c.write(oled_i2c,0x01)






if __name__ == '__main__':
    
    wiringpi2.wiringPiSetup()
    
    oled_init(wiringpi2)
