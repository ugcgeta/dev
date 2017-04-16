import wiringpi as wiringpi
import time

OUTPUT = 2
PWM_PIN = 18
SLEEP_TIME = 0.03

wiringpi.wiringPiSetupGpio()
wiringpi.pinMode(PWM_PIN, OUTPUT)

for i in range(0, 1024, 16):
    print(i)
    wiringpi.pwmWrite(PWM_PIN, i)
    time.sleep(SLEEP_TIME)

for i in range(1024, 0, -16):
    print(i)
    wiringpi.pwmWrite(PWM_PIN, i)
    time.sleep(SLEEP_TIME)
