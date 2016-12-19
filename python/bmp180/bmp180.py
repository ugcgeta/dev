# -*- coding: utf-8 -*-

import Adafruit_BMP.BMP085 as BMP085

_Bmp180 = 0
def Bmp180_init(mode = BMP085.BMP085_STANDARD):
    global _Bmp180

    _Bmp180 = BMP085.BMP085(mode)


def Bmp180_getSensor():
   
    temp =_Bmp180.read_temperature()
    hPa = _Bmp180.read_pressure()/100.0
    alt = _Bmp180.read_altitude()
    #print(_Bmp180.read_sealevel_pressure())
    return (temp,hPa,alt)

#############################################
if __name__ == '__main__':
    
    Bmp180_init()
    print(Bmp180_getSensor())


