# -*- coding: utf-8 -*-
import wiringpi2

PWM_PIN = 18   # GPIOの18番ピン
DUTY_MAX = 123 # 90°の時
DUTY_MIN = 26  # -90°の時
DUTY_HOME= 74  # 0°の時
duty = 0       # Duty比の値(0から1024)

wiringpi2.wiringPiSetupGpio()   #winringPiの初期設定
wiringpi2.pinMode(PWM_PIN, wiringpi2.GPIO.PWM_OUTPUT)
#「Balanced」→「mark:space」Modeに変更
wiringpi2.pwmSetMode(wiringpi2.GPIO.PWM_MODE_MS)
# 周波数を50Hzにすると、18750/周波数=375
wiringpi2.pwmSetClock(375)

wiringpi2.pwmWrite(PWM_PIN, DUTY_HOME)        # 0°の位置に移動
wiringpi2.delay(100) #0.1sec

for duty in range(DUTY_HOME, DUTY_MAX+1, 1):  # 0°から90°まで動かす
    wiringpi2.pwmWrite(PWM_PIN, duty)
    wiringpi2.delay(100) #0.1sec
   # wiringpi2.delay(500)    #0.5sec

for duty in range(DUTY_MAX, DUTY_MIN-1, -1):  # 90°から-90°まで動かす
    wiringpi2.pwmWrite(PWM_PIN, duty)
    wiringpi2.delay(100)
   # wiringpi2.delay(500)

wiringpi2.pwmWrite(PWM_PIN, DUTY_HOME)        # 0°の位置に移動
