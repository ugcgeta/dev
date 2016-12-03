# -*- coding: utf-8 -*-
import wiringpi
import wiringpi2
import os
import struct
from time import sleep
from datetime import datetime

AM2320_I2C_SLEEP_ERROR = -1
if __name__ == '__main__':
    
    wiringpi2.wiringPiSetup()
    i2c = wiringpi2.I2C()
    am2320 = i2c.setup(0x5C)

    #for var in range(0, 100):
    while(True):
        while(i2c.writeReg16(am2320,0x03,0x0600)==AM2320_I2C_SLEEP_ERROR):
            pass
            #print("--")
        #i2c.writeReg16(am2320,0x03,0x0600)
        #i2c.writeReg16(am2320,0x03,0x0600)
    
        # read data controlDatax2 wetDatax2 TempDatax2
        dataArray = struct.unpack('6B',os.read(am2320,6))
        
        wet = (float)((dataArray[2]<<8) | dataArray[3])/10
        tmp = (float)((dataArray[4]<<8) | dataArray[5])/10
        print(datetime.now().strftime('%X')," >>>  ",wet,"%  , ",tmp,"'C")
        sleep(300)

    os.close(am2320)

