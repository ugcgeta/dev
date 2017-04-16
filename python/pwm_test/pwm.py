# -*- coding: utf-8 -*-
import wiringpi

PWM_PIN = 18   # GPIOの18番ピン
DUTY_MAX = 123 # 90°の時
DUTY_MIN = 26  # -90°の時
DUTY_HOME= 74  # 0°の時
duty = 0       # Duty比の値(0から1024)

wiringpi.wiringPiSetupGpio()   #winringPiの初期設定
wiringpi.pinMode(PWM_PIN, wiringpi.GPIO.PWM_OUTPUT)
#「Balanced」→「mark:space」Modeに変更
wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)
# 周波数を50Hzにすると、18750/周波数=375
wiringpi.pwmSetClock(375)

wiringpi.pwmWrite(PWM_PIN, DUTY_HOME)        # 0°の位置に移動
wiringpi.delay(1000) #1sec

# 0°から90°まで動かす
wiringpi.pwmWrite(PWM_PIN, DUTY_MAX)
wiringpi.delay(200) #2sec

# 90°から-90°まで動かす
wiringpi.pwmWrite(PWM_PIN, DUTY_MIN)
wiringpi.delay(500)

wiringpi.pwmWrite(PWM_PIN, DUTY_HOME)        # 0°の位置に移動
