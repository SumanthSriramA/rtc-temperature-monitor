aurdino code

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

// LCD (adjust address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RTC object
RTC_DS3231 rtc;

// Temperature threshold
const float tempThreshold = 35.0;

void setup() {
  lcd.init();
  lcd.backlight();
  
  // Initialize RTC
  if (!rtc.begin()) {
    lcd.clear();
    lcd.print("RTC not found!");
    while (1); // Stop here
  }
  
  // Uncomment this to set RTC time to compile time ONCE
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Clock + Temp Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read LM35
  int rawValue = analogRead(A0);
  float voltage = rawValue * (5.0 / 1023.0);
  float temperatureC = voltage * 100;

  // Get RTC date and time
  DateTime now = rtc.now();

  // If temperature exceeds threshold, show warning
  if (temperatureC >= tempThreshold) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WARNING: TEMP");
    lcd.setCursor(0,1);
    lcd.print("HIGH!");
    delay(2000); // Show warning for 2 sec
    lcd.clear();
  }

  // Display time
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  // Display date and temperature
  lcd.setCursor(0,1);
  if (now.day() < 10) lcd.print("0");
  lcd.print(now.day());
  lcd.print("-");
  if (now.month() < 10) lcd.print("0");
  lcd.print(now.month());
  lcd.print("-");
  lcd.print(now.year() % 100); // show last 2 digits
  lcd.print(" T:");
  lcd.print((int)temperatureC);
  lcd.print((char)223);
  lcd.print("C");

  delay(1000);
}
