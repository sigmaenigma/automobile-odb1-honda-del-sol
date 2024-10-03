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
