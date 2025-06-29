# 💊 Smart Medication Reminder System

An IoT-based Medibox designed to help elderly or forgetful users take their medication on time. The system detects pill pickup, notifies caregivers, and includes live video monitoring via ESP32-CAM.

## 🚀 Features

- Automatic pill chamber opening using a servo motor.
- IR sensor detects whether the pill was taken.
- ESP32-CAM provides live video monitoring.
- Caretaker is alerted if the pill is missed.
- User can schedule timings via a mobile app.

## 🧰 Tech Stack

- **Microcontroller:** ESP32-CAM, Arduino Uno
- **Sensors:** IR Sensor, Servo Motor
- **Programming:** Arduino C/C++
- **App:** Android (MIT App Inventor or similar)
- **Communication:** Wi-Fi, GSM (optional)


## 🔧 How it Works

1. User sets medication schedule via app.
2. Servo motor opens the correct compartment at scheduled time.
3. IR sensor checks if the pill is picked up.
4. If not picked up in 2 minutes, a notification is sent to the caretaker.
5. ESP32-CAM allows real-time visual monitoring.

## 📁 Project Structure

- `/code/` → Arduino code for ESP32-CAM, IR sensor, servo
- `/hardware/` → Circuit diagrams and components list
- `/mobile_app/` → App UI and screenshots
