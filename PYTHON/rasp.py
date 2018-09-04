def getDistance(trig, echo) :
  pio.output(trig, False)
  time.sleep(0.5)

  gpio.output(trig, True)
  time.sleep(0.00001)
  gpio.output(trig, False)

  while gpio.input(echo) == 0:
    pulse_start = time.time()

  while gpio.input(echo) == 1:
    pulse_end = time.time()

  pulse_duration = pulse_end - pulse_start
  distance = pulse_duration * 17000
  distance = round(distance, 2)

  return distance


import RPi.GPIO as gpio
import Adafruit_DHT as dht
import time
import Adafruit_CharLCD as LCD

gpio.setmode(gpio.BCM)

trig_1 = 13
echo_1 = 19
trig_2 = 23
echo_2 = 24

lcd_rs = 25
lcd_en = 24
lcd_d4 = 23
lcd_d5 = 17
lcd_d6 = 18
lcd_d7 = 22
lcd_backlight = 2

lcd_columns = 16
lcd_rows = 2

lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7, lcd_columns, lcd_rows, lcd_backlight)


gpio.setup(trig, gpio.OUT)
gpio.setup(echo, gpio.IN)

people = 0

try :
  while True :
    h, t = dht.read_retry(dht.DHT11, 4)
    print 'Temp={0:0.1f}*C   Humidity={1:0.1f}%'.format(t, h)
    time.sleep(1)

    IN = getDistance(trig_1, echo_1)
    OUT = getDistance(trig_2, echo_2)

    if IN <= 25:
      if OUT <= 25:
        people +=1

    elif OUT <=25:
      if IN <= 25:
        if people > 0 :
          people -=1

    lcd.message("Temp : " + t + "Humi : " + h + "\nMan : " + people)

except :
  gpio.cleanup()
