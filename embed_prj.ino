#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>
#include <Wire.h>

RTC_DS1307 rtc;
bool alarm_set_mode = false;

// Create a U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C object
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(9);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Button pins
const int button1 = 5;
const int button2 = 6;
const int button3 = 7;
const int button4 = 8;

// RGB LED pins
const int redLight = 2;
const int greenLight = 3;
const int blueLight = 4;

//buzzer pin
const int buzzpin = 13;
// Time variables
int hours = 0;
int minutes = 0;
bool setTime = false;
bool alarm_enabled = false;
int alarm_h = 0;
int alarm_m = 0;
int current_setting_alarm = 2;  // 0 for hour setting --- 1 for minute setting --- 2 for None
void setup() {
  // Begin the U8g2 object
  u8g2.begin();
  Serial.begin(9600);
  Wire.begin();
  // Set the font to use
  u8g2.setFont(u8g2_font_ncenB10_tr);

  // Start the DS18B20 sensor
  sensors.begin();

  // Setup the buttons
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  // Setup the RGB LED
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(blueLight, OUTPUT);

  // setup buzzer
  pinMode(buzzpin, OUTPUT);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2024, at 3am you would call:
    // rtc.adjust(DateTime(2024, 1, 21, 3, 0, 0));
  }
}

void loop() {
    DateTime now = rtc.now();
  alarm_check(now.hour(),now.minute());
  if (alarm_set_mode) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, 12);
    if (current_setting_alarm == 0) {
      set_hours_alarm();
    }
    // u8g2.print(":");
    //u8g2.print(alarm_m);
    if (current_setting_alarm == 1) {
      set_minutes_alarm();
    }

  } else {


    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    //delay(1000);
    // Request temperature from DS18B20
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);

    // Check if the set time button is pressed
    // if (digitalRead(button3) == LOW) {
    //   setTime = !setTime;
    //   delay(200);  // Debounce delay
    // }

    // // If in set time mode, check the hour and minute buttons
    // if (setTime) {
    //   if (digitalRead(button2) == LOW) {
    //     hours = (hours + 1) % 24;
    //     delay(200);  // Debounce delay
    //   }
    //   if (digitalRead(button4) == LOW) {
    //     minutes = (minutes + 1) % 60;
    //     delay(200);  // Debounce delay
    //   }
    // }
    if (digitalRead(button1) == HIGH) {
      alarm_set_mode = true;
      current_setting_alarm = 0;
      // setAlarm = true;
      //setTime = false;
    }


    // Set the RGB LED color based on the temperature
    if (tempC > 30) {
      digitalWrite(redLight, HIGH);
      digitalWrite(greenLight, LOW);
      digitalWrite(blueLight, LOW);
    } else if (tempC >= 25 && tempC <= 30) {
      digitalWrite(redLight, HIGH);
      digitalWrite(greenLight, HIGH);
      digitalWrite(blueLight, LOW);
    } else {
      digitalWrite(redLight, LOW);
      digitalWrite(greenLight, LOW);
      digitalWrite(blueLight, HIGH);
    }

    // Clear the buffer
    u8g2.clearBuffer();

    // Display the time
    u8g2.setCursor(0, 12);
    u8g2.print("Time: ");
    u8g2.print(now.hour());
    u8g2.print(":");
    u8g2.print(now.minute());

    // Display the temperature
    u8g2.setCursor(0, 29);
    u8g2.print("Temp: ");
    u8g2.print(tempC);
    u8g2.print(" C");

    // Send the buffer to the display
    u8g2.sendBuffer();
  }
}
void set_hours_alarm() {
  u8g2.print("Set Hour : ");
  u8g2.print(alarm_h);
  u8g2.sendBuffer();

  if (digitalRead(button2) == HIGH) {
    if (alarm_h < 24) {


      alarm_h++;
      u8g2.clearBuffer();
      u8g2.setCursor(0, 12);
      u8g2.print("Set Hour : ");
      u8g2.print(alarm_h);
      u8g2.sendBuffer();
    }
    delay(100);
  }
  if (digitalRead(button3) == HIGH) {
    if (alarm_h > 0) {

      alarm_h--;
      u8g2.clearBuffer();
      u8g2.setCursor(0, 12);
      u8g2.print("Set Hour : ");
      u8g2.print(alarm_h);
      u8g2.sendBuffer();
    }

    delay(50);
  }
  if (digitalRead(button4) == HIGH) {
    current_setting_alarm = 1;
    delay(200);
  }
}
void set_minutes_alarm() {
  u8g2.print("Set Minute : ");
  u8g2.print(alarm_m);
  u8g2.sendBuffer();

  if (digitalRead(button2) == HIGH) {
    if (alarm_m < 59) {


      alarm_m++;
      u8g2.clearBuffer();
      u8g2.setCursor(0, 12);
      u8g2.print("Set Minute : ");
      u8g2.print(alarm_m);
      u8g2.sendBuffer();
    }
    delay(100);
  }
  if (digitalRead(button3) == HIGH) {
    if (alarm_m > 0) {

      alarm_m--;
      u8g2.clearBuffer();
      u8g2.setCursor(0, 12);
      u8g2.print("Set Minute : ");
      u8g2.print(alarm_m);
      u8g2.sendBuffer();
    }

    delay(50);
  }
  if (digitalRead(button4) == HIGH) {
    current_setting_alarm = 2;
    alarm_set_mode = false;
    delay(200);
    alarm_enabled = true;
  }
}
void alarm_check(int hour_now, int min_now){
  if(alarm_enabled){
if(hour_now == alarm_h & min_now== alarm_m){
 u8g2.clearBuffer();
      u8g2.setCursor(0, 12);
      u8g2.print("Alarm : ");
      u8g2.print(hour_now);
      u8g2.print(":");
      u8g2.print(min_now);
      u8g2.sendBuffer();
  digitalWrite(buzzpin, HIGH);
  delay(1000);
  digitalWrite(buzzpin, LOW);
  alarm_enabled = false;
}
  }
}