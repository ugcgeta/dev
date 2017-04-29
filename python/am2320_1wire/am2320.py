# -*- coding: utf-8 -*-
from time import sleep
from datetime import datetime
import Adafruit_DHT as DHT

## センサーの種類
SENSOR_TYPE = DHT.DHT22

## 接続したGPIOポート
DHT_GPIO = 21

def Am2320_init(i2c):
    pass

def Am2320_getSensor():
    
    # read data
    humidity,temperature = DHT.read_retry(SENSOR_TYPE, DHT_GPIO)

    #return (('%6.02f'%temperature),('%6.02f'%humidity))
    return (temperature,humidity)

def Am2320_close():
    pass

#############################################
if __name__ == '__main__':
    
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
    

