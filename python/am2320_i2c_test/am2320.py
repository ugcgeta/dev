# -*- coding: utf-8 -*-
import wiringpi
import os
import struct
from time import sleep
from datetime import datetime

_AM2320_I2C_SLEEP_ERROR = -1
_Am2320 = 0
_I2c = 0
def Am2320_init(i2c):
    global _Am2320
    global _I2c

    _I2c = i2c
    _Am2320 = _I2c.setup(0x5C)


def Am2320_getSensor():
    
    # ダミーリードでセンサを起こす
    while(_I2c.writeReg16(_Am2320,0x03,0x0600)==_AM2320_I2C_SLEEP_ERROR):
        sleep(0.001) #wait
        pass
    
    sleep(0.002) # 800usec + 1.5msec wait

    # read data controlDatax2 wetDatax2 TempDatax2
    dataArray = struct.unpack('6B',os.read(_Am2320,6))
        
    Humidity = (float)((dataArray[2]<<8) | dataArray[3])/10
    temperature = (float)((dataArray[4]<<8) | dataArray[5])/10

    return (temperature,Humidity)

def Am2320_close():
    global _Am2320

    os.close(_Am2320)

#############################################
if __name__ == '__main__':
    
    wiringpi.wiringPiSetup()
    i2c = wiringpi.I2C()
#    am2320 = i2c.setup(0x5C)

    Am2320_init(i2c)

    #for var in range(0, 100):
    while(True):
#        while(i2c.writeReg16(am2320,0x03,0x0600)==AM2320_I2C_SLEEP_ERROR):
#            pass
        # read data controlDatax2 wetDatax2 TempDatax2
#        dataArray = struct.unpack('6B',os.read(am2320,6))
        
#        wet = (float)((dataArray[2]<<8) | dataArray[3])/10
#        tmp = (float)((dataArray[4]<<8) | dataArray[5])/10
#        print(datetime.now().strftime('%X')," >>>  ",wet,"%  , ",tmp,"'C")
        tmp,wet = Am2320_getSensor()
        print(datetime.now().strftime('%X')," >>>  ",wet,"%  , ",tmp,"'C")
        sleep(2)
    
    Am2320_close()

