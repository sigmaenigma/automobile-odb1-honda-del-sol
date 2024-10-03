# OBD1 Data Reader for 1994 Honda Del Sol

This repository contains a proof-of-concept Python script designed to read OBD1 data from a 1994 Honda Del Sol using a Raspberry Pi. This script is not in a production state and should be used with caution.

## Description

The script reads input from a specified GPIO pin on the Raspberry Pi, counts the number of blinks, and matches the count to a corresponding OBD1 code from a JSON file. The JSON file contains diagnostic trouble codes (DTCs) specific to the 1994 Honda Del Sol.

## Hardware Requirements

- Raspberry Pi
- GPIO setup for reading OBD1 data
- 1994 Honda Del Sol with a B16a3 Engine

## Software Requirements

- Python 3.x
- RPi.GPIO library
- JSON file with OBD1 codes

## Installation

1. Clone this repository:
    ```bash
    git clone https://github.com/yourusername/obd1-reader.git
    cd obd1-reader
    ```

2. Install the required Python libraries:
    ```bash
    pip install RPi.GPIO
    ```

3. Ensure the `honda_del_sol_codes.json` file is in the same directory as the script.

## Usage

1. Connect the Raspberry Pi to the OBD1 port of the 1994 Honda Del Sol.
2. Run the script:
    ```bash
    python obd1_reader.py
    ```

## Code

```python
import RPi.GPIO as GPIO
import time
import json

""" This is a proof of concept and definitely not in a 'prod' state. 
Just saving stuff here in case someone finds this and decides to start using it. 
BE CAREFUL! 
"""

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
```

## JSON File Format

The `honda_del_sol_codes.json` file should be formatted as follows:

```json
{
  "0": "Electronic control module (ECM)",
  "1": "Heated oxygen sensor A",
  "2": "Oxygen content B",
  "3": "Manifold absolute pressure",
  "4": "Crank position sensor",
  "5": "Manifold absolute pressure",
  "6": "Engine coolant temperature",
  "7": "Throttle position sensor",
  "8": "Top dead center sensor",
  "9": "No.1 cylinder position sensor",
  "10": "Intake air temperature sensor",
  "11": "Electronic control module (ECM)",
  "12": "Exhaust recirculation system",
  "13": "Barometric pressure sensor",
  "14": "Idle air control valve or bad ECM",
  "15": "Ignition output signal",
  "16": "Fuel Injector",
  "17": "Vehicle speed sensor",
  "19": "A/T lock-up control solenoid",
  "20": "Electric load detector",
  "21": "V-TEC control solenoid",
  "22": "V-TEC pressure solenoid",
  "23": "Knock sensor",
  "30": "A/T FI signal A",
  "31": "A/T FI signal B",
  "41": "Heated oxygen sensor heater",
  "43": "Fuel supply system",
  "45": "Fuel supply metering",
  "48": "Heated oxygen sensor",
  "61": "Front heated oxygen sensor",
  "63": "Rear heated oxygen sensor",
  "65": "Rear heated oxygen sensor heater",
  "67": "Catalytic converter system",
  "70": "Automatic transaxle",
  "71": "Misfire detected cylinder 1",
  "72": "Misfire detected cylinder 2",
  "73": "Misfire detected cylinder 3",
  "74": "Misfire detected cylinder 4",
  "75": "Misfire detected cylinder 5",
  "76": "Misfire detected cylinder 6",
  "80": "Exhaust recirculation system",
  "86": "Coolant temperature",
  "92": "Evaporative emission control system"
}
```

## Disclaimer

This script is a proof of concept and should be used with caution. It is not intended for production use. Always ensure you understand the code and its implications before using it on your vehicle.

### Acknowledgments

This project was made possible through the support and resources provided by various contributors and repositories:

- **brendan-w/python-OBD**: OBD-II serial module for reading engine data. Available at [GitHub](https://github.com/brendan-w/python-OBD).
- **Fork from OBDTester**: OBD-II compliant car module. Available at [GitHub](https://github.com/chethenry/pyOBD).
- **brokenrobotz/python-OBD**: OBD-II serial module for reading engine data. Available at [GitHub](https://github.com/brokenrobotz/python-OBD).
- **peterh/pyobd**: Original repository. Available at [GitHub](https://github.com/peterh/pyobd).
- **Pbartek/pyobd-pi**: Forked repository. Available at [GitHub](https://github.com/Pbartek/pyobd-pi).
- **OBDTester**: OBD-II compliant car module. Available at [OBDTester](http://www.obdtester.com/pyobd).
- **SparkFun**: ELM327 AT Commands documentation. Available at [SparkFun](https://www.sparkfun.com/datasheets/Widgets/ELM327_AT_Commands.pdf).
- **Wikipedia**: Information on OBD-II PIDs. Available at [Wikipedia](http://en.wikipedia.org/wiki/OBD-II_PIDs).
- **SparkFun**: OBD-II products. Available at [SparkFun](https://www.sparkfun.com/products/9555).
