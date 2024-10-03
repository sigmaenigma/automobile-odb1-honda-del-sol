#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int milPin = 18;  // Assuming pin 18 is connected to the MIL

// DTC codes
const char* dtc_codes[] = {
  "Electronic control module (ECM)",  // 0
  "Heated oxygen sensor A",           // 1
  "Oxygen content B",                 // 2
  "Manifold absolute pressure",       // 3
  "Crank position sensor",            // 4
  "Manifold absolute pressure",       // 5
  "Engine coolant temperature",       // 6
  "Throttle position sensor",         // 7
  "Top dead center sensor",           // 8
  "No.1 cylinder position sensor",    // 9
  "Intake air temperature sensor",    // 10
  "Electronic control module (ECM)",  // 11
  "Exhaust recirculation system",     // 12
  "Barometric pressure sensor",       // 13
  "Idle air control valve or bad ECM",// 14
  "Ignition output signal",           // 15
  "Fuel Injector",                    // 16
  "Vehicle speed sensor",             // 17
  "Unknown DTC",                      // 18 (placeholder)
  "A/T lock-up control solenoid",     // 19
  "Electric load detector",           // 20
  "V-TEC control solenoid",           // 21
  "V-TEC pressure solenoid",          // 22
  "Knock sensor",                     // 23
  "Unknown DTC",                      // 24-29 (placeholders)
  "A/T FI signal A",                  // 30
  "A/T FI signal B",                  // 31
  "Unknown DTC",                      // 32-40 (placeholders)
  "Heated oxygen sensor heater",      // 41
  "Unknown DTC",                      // 42
  "Fuel supply system",               // 43
  "Unknown DTC",                      // 44
  "Fuel supply metering",             // 45
  "Unknown DTC",                      // 46-47 (placeholders)
  "Heated oxygen sensor",             // 48
  "Unknown DTC",                      // 49-60 (placeholders)
  "Front heated oxygen sensor",       // 61
  "Unknown DTC",                      // 62
  "Rear heated oxygen sensor",        // 63
  "Unknown DTC",                      // 64
  "Rear heated oxygen sensor heater", // 65
  "Unknown DTC",                      // 66
  "Catalytic converter system",       // 67
  "Unknown DTC",                      // 68-69 (placeholders)
  "Automatic transaxle",              // 70
  "Misfire detected cylinder 1",      // 71
  "Misfire detected cylinder 2",      // 72
  "Misfire detected cylinder 3",      // 73
  "Misfire detected cylinder 4",      // 74
  "Misfire detected cylinder 5",      // 75
  "Misfire detected cylinder 6",      // 76
  "Unknown DTC",                      // 77-79 (placeholders)
  "Exhaust recirculation system",     // 80
  "Unknown DTC",                      // 81-85 (placeholders)
  "Coolant temperature",              // 86
  "Unknown DTC",                      // 87-91 (placeholders)
  "Evaporative emission control system" // 92
};

void setup() {
  Serial.begin(9600);
  pinMode(milPin, INPUT);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);  // Pause for 2 seconds
  display.clearDisplay();
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

  // Print to Serial Monitor
  Serial.print("DTC Code: ");
  Serial.print(dtc_code);
  Serial.print(", Message: ");
  Serial.println(dtc_message);

  // Print to OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("DTC Code: ");
  display.println(dtc_code);
  display.print("Message: ");
  display.println(dtc_message);
  display.display();

  delay(5000);  // Wait before reading the next code
}
