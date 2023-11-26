import RPi.GPIO as GPIO
import time
import json

""" This is a proof of concept and definitely not in a 'prod' state. Just saving stuff here in case someone finds this and decides to start using it. BE CAREFUL! """

# Set the mode of the GPIO library
GPIO.setmode(GPIO.BCM)

# Set the pin number to read from
channel = 17

# Set the pin as an input channel
GPIO.setup(channel, GPIO.IN)

# Initialize the blink count
blink_count = 0

# Initialize the previous input value
prev_input_value = GPIO.input(channel)

# Read in the JSON file with all the Codes
with open('honda_del_sol_codes.json','r') as f:
    obd1_codes = json.load(f)

# Loop forever
while True:
    # Wait for a short period of time
    time.sleep(0.1)

    # Read the value of the input channel
    input_value = GPIO.input(channel)

    # If the input value has changed
    if input_value != prev_input_value:
        # Increment the blink count
        blink_count += 1

        # Update the previous input value
        prev_input_value = input_value

        # If the blink count is in the key of the dictionary
        if blink_count in obd1_codes:
            # Output the appropriate key / value pair
            print(f"{blink_count}: {obd1_codes[blink_count]}")
