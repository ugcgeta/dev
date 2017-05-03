#!/usr/bin/env python
#coding:utf-8

import pygame.mixer
import time

def MP3_load(title):

    pygame.mixer.init()
    pygame.mixer.music.load(title)

def MP3_play(loop):

    pygame.mixer.music.play(loop) # ()内は再生回数 -1:ループ再生

def MP3_pause():

    pygame.mixer.music.pause() # 音楽の一時停止

def MP3_stop():

    pygame.mixer.music.stop() # 再生の終了

#pygame.mixer.music.unpause # 一時停止した音楽の再開
#pygame.mixer.music.set_volume(0.8) # ボリュームの設定
#pygame.mixer.music.queue('test2.mp3') # 次の再生ファイルのセット

#print( "音量:%s" % pygame.mixer.music.get_volume()) #ボリュームの取得
#print( "再生時間:%s[ms]"%pygame.mixer.music.get_busy()) # 再生時間の取得[ms]

#time.sleep(2)
#pygame.mixer.music.stop() # 再生の終了

if __name__ == '__main__':
    
    MP3_load("test.mp3")
    MP3_play(1)

    time.sleep(2)
    
    MP3_stop()



