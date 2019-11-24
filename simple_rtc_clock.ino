#include <Arduino.h>
#include <TM1637Display.h>
#include <DS3231.h>

// pins 2 and 3 are reserved for i2c bus for ds3231
#define RXLED_PIN         17
#define DISP_CLK_PIN      4
#define DISP_DIO_PIN      5
#define LED_PIN           6
#define LED_BTN_PIN       7
#define TIME_EDIT_BTN_PIN 8
#define TIME_HOUR_BTN_PIN 9
#define TIME_MIN_BTN_PIN  10

#define DELAY_MS      50
#define EDIT_BLINK_MS 800

#define PM_INDICATOR_SEGMENT    0x10  // only for use in the left most digit
#define EDIT_INDICATOR_SEGMENT  0x20  // only for use in the left most digit
#define COLON_SEGMENT           0x80  // only for use by the second digit from the left

TM1637Display display(DISP_CLK_PIN, DISP_DIO_PIN);
DS3231 rtc;

bool wasHourPressed = false;
bool wasMinPressed = false;
byte ledMode = LOW;

unsigned long editBlinkTimer = 0;
bool editIndicator = true;

void toggleLED() {
  digitalWrite(LED_PIN, HIGH);
  ledMode = !ledMode;
}

void showTime(bool showEditIndicator = false) {
  bool unused1 = false;
  bool unused2 = false;
  uint8_t hour = rtc.getHour(unused1, unused2);
  uint8_t minute = rtc.getMinute();
  bool pm;
  uint8_t segments[4] = {0};

  pm = hour > 12;
  hour %= 12;

  // draw the pm indicator, colon, and digits for the hour
  if (hour / 10 == 1 || hour == 0)
    segments[0] = display.encodeDigit(1) | (pm ? PM_INDICATOR_SEGMENT : 0x0) | (showEditIndicator ? EDIT_INDICATOR_SEGMENT : 0x0);
  else
    segments[0] = (pm ? PM_INDICATOR_SEGMENT : 0x0) | (showEditIndicator ? EDIT_INDICATOR_SEGMENT : 0x0);
  if (hour == 0)
    segments[1] = display.encodeDigit(hour % 10) | COLON_SEGMENT;
  else
    segments[1] = display.encodeDigit(hour % 10) | COLON_SEGMENT;

  // draw the digits for the minute
  segments[2] = display.encodeDigit(minute / 10);
  segments[3] = display.encodeDigit(minute % 10);
  
  display.setSegments(segments);
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  // initialize pins
  pinMode(DISP_CLK_PIN, OUTPUT);
  pinMode(DISP_DIO_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BTN_PIN, INPUT_PULLUP);
  pinMode(TIME_EDIT_BTN_PIN, INPUT_PULLUP);
  pinMode(TIME_HOUR_BTN_PIN, INPUT_PULLUP);
  pinMode(TIME_MIN_BTN_PIN, INPUT_PULLUP);
  
  // turn off LEDs
  digitalWrite(RXLED_PIN, LOW);
  TXLED0;

  // attach interrupt to LED toggle button pin
  attachInterrupt(digitalPinToInterrupt(LED_BTN_PIN), toggleLED, FALLING);

  // initialize other components
  display.setBrightness(2);
  rtc.setHour(0);
  rtc.setMinute(0);
  rtc.setSecond(0);
  rtc.setClockMode(false);
  //rtc.enableOscillator(true, false, 3);
}

void loop() {
  if (digitalRead(TIME_EDIT_BTN_PIN))
  {
    // let the user modify the time shown on the display
    bool hourPressed = digitalRead(TIME_HOUR_BTN_PIN) == HIGH;
    if (!hourPressed)
    {
      wasHourPressed = false;
    }
    else if (hourPressed && !wasHourPressed)
    {
      bool unused1 = false;
      bool unused2 = false;
      rtc.setHour((rtc.getHour(unused1, unused2) + 1) % 24);
      wasHourPressed = true;
    }

    bool minPressed = digitalRead(TIME_MIN_BTN_PIN) == HIGH;
    if (!minPressed)
    {
      wasMinPressed = false;
    }
    else if (minPressed && !wasMinPressed)
    {
      rtc.setMinute((rtc.getMinute() + 1) % 60);
      wasMinPressed = true;
    }

    // display the new time with blinking edit indicator
    if (millis() - editBlinkTimer > EDIT_BLINK_MS)
    {
      editBlinkTimer = millis();
      editIndicator = !editIndicator;
    }
    
    showTime(editIndicator);
  }
  else
  {
    showTime();
    delay(DELAY_MS);
  }
}
