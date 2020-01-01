import RPi.GPIO as GPIO
import time

state = 0

GPIO.setmode(GPIO.BCM)
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(19, GPIO.IN, pull_up_down=GPIO.PUD_UP)


def interrupt_handler(channel):
    global state

    print("interrupt handler")

    if channel == 19:
        if state == 1:
            state = 0
            print("state reset by event on pin 19")
    elif channel == 26:
        if state == 0:
            state = 1
            print("state set by event on pin 26")


GPIO.add_event_detect(26, GPIO.RISING,
                      callback=interrupt_handler,
                      bouncetime=200)

GPIO.add_event_detect(19, GPIO.RISING,
                      callback=interrupt_handler,
                      bouncetime=200)


while (True):
    time.sleep(0)