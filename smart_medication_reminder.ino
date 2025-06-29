#include <Servo.h>
#include <Wire.h>
#include "RTClib.h"

Servo pillServo;
const int irSensorPin = 2;       // IR sensor digital output pin
const int buzzerPin = 3;         // Optional: buzzer or alert pin
const int servoPin = 9;          // Servo signal pin

RTC_DS3231 rtc;

bool pillTaken = false;
bool doseStarted = false;

DateTime scheduledTime;

void setup() {
  Serial.begin(9600);

  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pillServo.attach(servoPin);

  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }

  // Set RTC time once if not set
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Set scheduled time for demo (e.g., 3:00 PM)
  scheduledTime = DateTime(rtc.now().year(), rtc.now().month(), rtc.now().day(), 15, 0, 0); // 3:00 PM
}

void loop() {
  DateTime now = rtc.now();

  // Check if it's time to dispense
  if (now.hour() == scheduledTime.hour() && now.minute() == scheduledTime.minute() && !doseStarted) {
    dispensePill();
    doseStarted = true;
    pillTaken = false;

    Serial.println("Pill Dispensed. Waiting for pickup...");
    delay(1000);
    
    // Give user 2 minutes to pick up
    unsigned long startTime = millis();
    while ((millis() - startTime) < 120000) {
      if (digitalRead(irSensorPin) == LOW) { // LOW means pill picked
        pillTaken = true;
        Serial.println("Pill taken ✅");
        break;
      }
    }

    if (!pillTaken) {
      Serial.println("Pill not taken ❌ - Alert caretaker!");
      tone(buzzerPin, 1000, 3000);  // Buzz for 3 seconds
    }

    delay(60000); // Wait 1 minute to prevent re-triggering
  }

  // Reset flags at midnight
  if (now.hour() == 0 && now.minute() == 0) {
    doseStarted = false;
  }
}

void dispensePill() {
  pillServo.write(90);  // Open
  delay(1000);
  pillServo.write(0);   // Close
}
