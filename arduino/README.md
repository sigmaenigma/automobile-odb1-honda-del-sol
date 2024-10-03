# OBD1 Data Reader for 1994 Honda Del Sol (Arduino)

This project reads the blinks from a Malfunction Indicator Lamp (MIL) on a Honda Del Sol and decodes them into Diagnostic Trouble Codes (DTCs).

## Description

The script reads input from a specified GPIO pin on the Raspberry Pi, counts the number of blinks, and matches the count to a corresponding OBD1 code from a JSON file. The JSON file contains diagnostic trouble codes (DTCs) specific to the 1994 Honda Del Sol.. This Arduino sketch reads the long and short blinks from the MIL and converts them into DTC codes. The codes are then matched with predefined messages to provide a readable output.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno)
- MIL connected to pin 18 on the Arduino
- USB cable for programming and serial communication

## Software Requirements

- Arduino IDE

## Installation

1. **Clone the repository:**

   ```sh
   git clone https://github.com/yourusername/arduino-mil-blink-reader.git
   cd arduino-mil-blink-reader
   ```

2. **Open the sketch:**

   Open `mil_blink_reader.ino` in the Arduino IDE.

3. **Upload the sketch:**

   Connect your Arduino board to your computer and upload the sketch.

## Usage

1. **Connect the MIL:**

   Ensure the MIL is properly connected to pin 18 on the Arduino.

2. **Open Serial Monitor:**

   Open the Serial Monitor in the Arduino IDE to view the DTC codes and messages.

3. **Read Blinks:**

   The Arduino will read the blinks from the MIL and output the corresponding DTC code and message.

## Code

```cpp
#include <Arduino.h>

// Pin setup
const int milPin = 18;  // Assuming pin 18 is connected to the MIL

// DTC codes (you'll need to manually input your DTC codes here)
const char* dtc_codes[] = {
  "Unknown DTC",  // 0
  "DTC 1",        // 1
  // Add more DTC codes as needed
};

void setup() {
  Serial.begin(9600);
  pinMode(milPin, INPUT);
}

void loop() {
  int long_blinks = 0;
  int short_blinks = 0;

  while (true) {
    if (digitalRead(milPin) == HIGH) {
      unsigned long start_time = millis();
      while (digitalRead(milPin) == HIGH) {
        // Wait for the pin to go LOW
      }
      unsigned long blink_duration = millis() - start_time;
      if (blink_duration > 1000) {  // Assuming long blink is > 1 second
        long_blinks++;
      } else {
        short_blinks++;
      }
    }
    delay(100);  // Debounce delay
    if (long_blinks > 0 && short_blinks > 0) {
      break;
    }
  }

  int dtc_code = long_blinks * 10 + short_blinks;
  const char* dtc_message = dtc_codes[dtc_code];
  Serial.print("DTC Code: ");
  Serial.print(dtc_code);
  Serial.print(", Message: ");
  Serial.println(dtc_message);

  delay(5000);  // Wait before reading the next code
}
```
