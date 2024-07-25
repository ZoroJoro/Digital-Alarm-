# Digital-Alarm
# Arduino Alarm Clock with Temperature Display

This project is an Arduino-based alarm clock that displays the current time and temperature on an OLED screen. It allows users to set an alarm using buttons and provides visual feedback using an RGB LED based on the temperature.

## Components

- Arduino board (e.g., Arduino Uno)
- SSD1306 OLED display (128x32)
- DS18B20 temperature sensor
- DS1307 RTC module
- Buttons (4x)
- RGB LED
- Buzzer
- Wires and breadboard

## Libraries

This project uses the following Arduino libraries:
- `U8g2lib` for the OLED display
- `OneWire` for communication with the DS18B20 sensor
- `DallasTemperature` for temperature readings from the DS18B20
- `RTClib` for the RTC module

Ensure you have these libraries installed in your Arduino IDE.

## Wiring

- **OLED Display:**
  - VCC to 5V
  - GND to GND
  - SDA to A4
  - SCL to A5

- **DS18B20 Temperature Sensor:**
  - VCC to 5V
  - GND to GND
  - Data to pin 9 (with a 4.7kΩ pull-up resistor to VCC)

- **DS1307 RTC Module:**
  - VCC to 5V
  - GND to GND
  - SDA to A4
  - SCL to A5

- **Buttons:**
  - Button 1 to pin 5
  - Button 2 to pin 6
  - Button 3 to pin 7
  - Button 4 to pin 8

- **RGB LED:**
  - Red to pin 2
  - Green to pin 3
  - Blue to pin 4

- **Buzzer:**
  - Buzzer to pin 13

## Functionality

### Display Time and Temperature
The OLED display shows the current time (in 24-hour format) and the temperature in Celsius.

### Set Alarm
Press Button 1 to enter alarm set mode. Use Button 2 and Button 3 to adjust the hours and minutes for the alarm. Press Button 4 to switch between setting hours and minutes, and to finalize the alarm settings.

### Alarm Notification
When the current time matches the set alarm time, the buzzer will sound, and the alarm time will be displayed on the OLED screen.

### RGB LED Temperature Indicator
- If the temperature is above 30°C, the RGB LED will turn red.
- If the temperature is between 25°C and 30°C, the RGB LED will turn yellow.
- If the temperature is below 25°C, the RGB LED will turn blue.
