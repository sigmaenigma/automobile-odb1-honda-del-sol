import RPi.GPIO as GPIO
import time

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

obd1_codes = {
    0: "Electronic control module (ECM)",
    1: "Heated oxygen sensor A",
    2: "Oxygen content B",
    3: "Manifold absolute pressure",
    4: "Crank position sensor",
    5: "Manifold absolute pressure",
    6: "Engine coolant temperature",
    7: "Throttle position sensor",
    8: "Top dead center sensor",
    9: "No.1 cylinder position sensor",
    10: "Intake air temperature sensor",
    11: "Electronic control module (ECM)",
    12: "Exhaust recirculation system",
    13: "Barometric pressure sensor",
    14: "Idle air control valve or bad ECM",
    15: "Ignition output signal",
    16: "Fuel Injector",
    17: "Vehicle speed sensor",
    19: "A/T lock-up control solenoid",
    20: "Electric load detector",
    21: "V-TEC control solenoid",
    22: "V-TEC pressure solenoid",
    23: "Knock sensor",
    30: "A/T FI signal A",
    31: "A/T FI signal B",
    41: "Heated oxygen sensor heater",
    43: "Fuel supply system",
    45: "Fuel supply metering",
    48: "Heated oxygen sensor",
    61: "Front heated oxygen sensor",
    63: "Rear heated oxygen sensor",
    65: "Rear heated oxygen sensor heater",
    67: "Catalytic converter system",
    70: "Automatic transaxle",
    71: "Misfire detected cylinder 1",
    72: "Misfire detected cylinder 2",
    73: "Misfire detected cylinder 3",
    74: "Misfire detected cylinder 4",
    75: "Misfire detected cylinder 5",
    76: "Misfire detected cylinder 6",
    80: "Exhaust recirculation system",
    86: "Coolant temperature",
    92: "Evaporative emission control system"
}

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
