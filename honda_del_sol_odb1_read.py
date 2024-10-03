import RPi.GPIO as GPIO
import time
import json

""" This is a proof of concept and definitely not in a 'prod' state. 
Just saving stuff here in case someone finds this and decides to start using it. 
BE CAREFUL! 
"""

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN)  # Assuming GPIO 18 is connected to the MIL

with open('honda_del_sol_codes.json','r') as f:
    dtc_codes = json.load(f)
    
def read_blinks():
    long_blinks = 0
    short_blinks = 0
    while True:
        if GPIO.input(18) == GPIO.HIGH:
            start_time = time.time()
            while GPIO.input(18) == GPIO.HIGH:
                pass
            blink_duration = time.time() - start_time
            if blink_duration > 1:  # Assuming long blink is > 1 second
                long_blinks += 1
            else:
                short_blinks += 1
        time.sleep(0.1)  # Debounce delay
        if long_blinks > 0 and short_blinks > 0:
            break
    return long_blinks, short_blinks

try:
    while True:
        long_blinks, short_blinks = read_blinks()
        dtc_code = long_blinks * 10 + short_blinks
        dtc_message = dtc_codes.get(str(dtc_code), "Unknown DTC")
        print(f"DTC Code: {dtc_code}, Message: {dtc_message}")
        time.sleep(5)  # Wait before reading the next code
except KeyboardInterrupt:
    GPIO.cleanup()
