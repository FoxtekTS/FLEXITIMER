#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

// Pins for the MAX7219 module
const int DIN = 10;
const int CLK = 12;
const int CS = 11;

// Create an instance of the LedControl object
LedControl lc = LedControl(DIN, CLK, CS, 1);

// Create an instance of the RTC object
RTC_DS3231 rtc;

void setup() {
  // Start the serial communication with the computer for debugging
  Serial.begin(9600);

  // Initialize the MAX7219 display
  lc.shutdown(0, false);       // Wake up displays
  lc.setIntensity(0, 8);       // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);          // Clear display register

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Set the RTC to the current date & time if it has lost power
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Optionally, you can manually set the RTC time here:
  // rtc.adjust(DateTime(2024, 9, 15, 7, 14, 0));
}

void loop() {
  // Display the current RTC time
  displayRTCTime();
  delay(1000); // Update every second
}

void displayRTCTime() {
  // Get the current time
  DateTime now = rtc.now();

  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  // Prepare the time as a string
  char timeString[9];
  sprintf(timeString, "%02d-%02d-%02d", hour, minute, second);

  // Display the time on the MAX7219
  for (int i = 0; i < 8; i++) {
    if (timeString[i] == '-') {
      lc.setChar(0, 7 - i, '-', false); // Blank space for the dash
    } else {
      lc.setDigit(0, 7 - i, timeString[i] - '0', false);
    }
  }
}
