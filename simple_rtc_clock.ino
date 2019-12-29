#include <Arduino.h>
#include <TM1637Display.h>
#include <DS3231.h>

// pins 2 and 3 are reserved for i2c bus for ds3231
// for whatever reason, SDA and SCL macros don't work (or are defined incorrectly?)
#define RXLED_PIN         17
#define RTC_CLK_PIN       2
#define RTC_DATA_PIN      3
#define DISP_CLK_PIN      4
#define DISP_DIO_PIN      5
#define TIME_EDIT_BTN_PIN 6
#define TIME_HOUR_BTN_PIN 0
#define TIME_MIN_BTN_PIN  1

#define LED_BTN_PIN       7
#define LED1_PIN          10
#define LED2_PIN          14
#define LED3_PIN          15
#define LED4_PIN          16

#define DELAY_MS        80
#define EDIT_DELAY_MS   20
#define STARTUP_MSG_MS  700
#define EDIT_BLINK_MS   600
#define DEBOUNCE_MS     100

#define PM_INDICATOR_SEGMENT    0x10  // only for use in the left most digit
#define EDIT_INDICATOR_SEGMENT  0x20  // only for use in the left most digit
#define COLON_SEGMENT           0x80  // only for use by the second digit from the left

static TM1637Display display(DISP_CLK_PIN, DISP_DIO_PIN);
static DS3231 rtc(RTC_DATA_PIN, RTC_CLK_PIN);

static bool startup = true;
static uint8_t startupMsgPos = 0;

// time/display edits can only occur in the loop function,
// otherwise we may interrupt an in-progress communication with the DS3231/TM1637
static bool addHour = false;
static bool addMin = false;
static bool changeDisplayBrightness = false;

static unsigned long interruptDebounceTimer = 0;
static bool interruptTriggered = false;

// startup message = "hour=rESEt mIn=contInuE  "
#define STARTUP_MSG_LEN   26
#define STARTUP_SEG_LEN   4
static uint8_t startupMsg[STARTUP_MSG_LEN][STARTUP_SEG_LEN] = {
  { 0b01110100, 0b01011100, 0b00011100, 0b01010000 },
  { 0b01011100, 0b00011100, 0b01010000, 0b01001000 },
  { 0b00011100, 0b01010000, 0b01001000, 0b01010000 },
  { 0b01010000, 0b01001000, 0b01010000, 0b01111001 },
  { 0b01001000, 0b01010000, 0b01111001, 0b01101101 },
  { 0b01010000, 0b01111001, 0b01101101, 0b01111001 },
  { 0b01111001, 0b01101101, 0b01111001, 0b01111000 },
  { 0b01101101, 0b01111001, 0b01111000, 0b00000000 },
  { 0b01111001, 0b01111000, 0b00000000, 0b01010100 },
  { 0b01111000, 0b00000000, 0b01010100, 0b01000100 },
  { 0b00000000, 0b01010100, 0b01000100, 0b00000110 },
  { 0b01010100, 0b01000100, 0b00000110, 0b01010100 },
  { 0b01000100, 0b00000110, 0b01010100, 0b01001000 },
  { 0b00000110, 0b01010100, 0b01001000, 0b01011000 },
  { 0b01010100, 0b01001000, 0b01011000, 0b01011100 },
  { 0b01001000, 0b01011000, 0b01011100, 0b01010100 },
  { 0b01011000, 0b01011100, 0b01010100, 0b01111000 },
  { 0b01011100, 0b01010100, 0b01111000, 0b00000110 },
  { 0b01010100, 0b01111000, 0b00000110, 0b01010100 },
  { 0b01111000, 0b00000110, 0b01010100, 0b00011100 },
  { 0b00000110, 0b01010100, 0b00011100, 0b01111001 },
  { 0b01010100, 0b00011100, 0b01111001, 0b00000000 },
  { 0b00011100, 0b01111001, 0b00000000, 0b00000000 },
  { 0b01111001, 0b00000000, 0b00000000, 0b01110100 },
  { 0b00000000, 0b00000000, 0b01110100, 0b01011100 },
  { 0b00000000, 0b01110100, 0b01011100, 0b00011100 },
};

static byte ledMode = 0;
static byte displayBrightnessMode = 2;

static unsigned long editBlinkTimer = 0;
static bool editIndicator = false;

bool debounceCheck()
{
  unsigned long currentTime = millis();

  if ((interruptDebounceTimer - currentTime) < DEBOUNCE_MS || interruptTriggered)
    return false;

  interruptDebounceTimer = currentTime;
  return true;
}

void showTime(bool showEditIndicator = false)
{
  uint8_t segments[4] = {0};
  bool pm;
  uint8_t hour, minute;
  Time t = rtc.getTime();
  
  hour = t.hour;
  minute = t.min;

  pm = hour >= 12;
  hour %= 12;

  // draw the pm indicator, colon, and digits for the hour
  if (hour / 10 == 1 || hour == 0)
    segments[0] = display.encodeDigit(1) | (pm ? PM_INDICATOR_SEGMENT : 0x0) | (showEditIndicator ? EDIT_INDICATOR_SEGMENT : 0x0);
  else
    segments[0] = (pm ? PM_INDICATOR_SEGMENT : 0x0) | (showEditIndicator ? EDIT_INDICATOR_SEGMENT : 0x0);
  if (hour == 0)
    segments[1] = display.encodeDigit(2) | COLON_SEGMENT;
  else
    segments[1] = display.encodeDigit(hour % 10) | COLON_SEGMENT;

  // draw the digits for the minute
  segments[2] = display.encodeDigit(minute / 10);
  segments[3] = display.encodeDigit(minute % 10);
  
  display.setSegments(segments);
}

void toggleLED()
{
  if (!debounceCheck())
    return;
  
  ledMode = (ledMode + 1) % 3;
  
  digitalWrite(LED1_PIN, ledMode > 0 ? HIGH : LOW);
  digitalWrite(LED2_PIN, ledMode > 0 ? HIGH : LOW);
  digitalWrite(LED3_PIN, ledMode == 1 ? HIGH : LOW);
  digitalWrite(LED4_PIN, ledMode == 1 ? HIGH : LOW);
  
  interruptTriggered = true;
}

void hourPressed()
{
  if (!debounceCheck())
  {
    return;
  }
  else if (startup)
  {
    // reset time in ds3231
    rtc.setTime(0, 0, 0);
    rtc.setDate(1, 1, 1970);

    Serial.println("Resetting time");
    
    startup = false;
  }
  else if (digitalRead(TIME_EDIT_BTN_PIN) == LOW)
  {
    addHour = true;
  }

  interruptTriggered = true;
}

void minPressed()
{
  if (!debounceCheck())
  {
    return;
  }
  else if (startup)
  {
    // use time already stored in ds3231
    startup = false;

    Serial.println("Using stored time");
  }
  else if (digitalRead(TIME_EDIT_BTN_PIN) == LOW)
  {
    addMin = true;
  }
  else
  {
    changeDisplayBrightness = true;
  }

  interruptTriggered = true;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning setup");
  
  // initialize pins
  pinMode(RTC_CLK_PIN, INPUT_PULLUP);
  pinMode(RTC_DATA_PIN, INPUT_PULLUP);
  pinMode(DISP_CLK_PIN, OUTPUT);
  pinMode(DISP_DIO_PIN, OUTPUT);
  pinMode(LED_BTN_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(TIME_EDIT_BTN_PIN, INPUT_PULLUP);
  pinMode(TIME_HOUR_BTN_PIN, INPUT_PULLUP);
  pinMode(TIME_MIN_BTN_PIN, INPUT_PULLUP);
  
  // turn off LEDs
  TXLED0;
  digitalWrite(RXLED_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);

  // attach interrupts
  attachInterrupt(digitalPinToInterrupt(LED_BTN_PIN), toggleLED, FALLING);
  attachInterrupt(digitalPinToInterrupt(TIME_HOUR_BTN_PIN), hourPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(TIME_MIN_BTN_PIN), minPressed, FALLING);

  // initialize other components
  display.setBrightness(6);
  rtc.begin();

  Serial.println("Finished setup");
}

void loop()
{
  if (interruptTriggered &&
      digitalRead(LED_BTN_PIN) == HIGH &&
      digitalRead(TIME_HOUR_BTN_PIN) == HIGH &&
      digitalRead(TIME_MIN_BTN_PIN) == HIGH)
  {
    interruptDebounceTimer = millis();
    interruptTriggered = false;
  }
  
  if (startup)
  {
    display.setSegments(startupMsg[startupMsgPos], STARTUP_SEG_LEN);
    startupMsgPos = (startupMsgPos + 1) % STARTUP_MSG_LEN;
    delay(STARTUP_MSG_MS);
  }
  else if (digitalRead(TIME_EDIT_BTN_PIN) == LOW)
  {
    // edit mode
    if (addHour)
    {
      Time t = rtc.getTime();
      rtc.setTime((t.hour + 1) % 24, t.min, t.sec); 
      addHour = false;
    }
    else if (addMin)
    {
      // editing the minute field resets the seconds to 0
      Time t = rtc.getTime();
      rtc.setTime(t.hour, (t.min + 1) % 60, 0);
      addMin = false;
    }
    
    if (millis() - editBlinkTimer > EDIT_BLINK_MS)
    {
      editBlinkTimer = millis();
      editIndicator = !editIndicator;
    }
  
    showTime(editIndicator);
    delay(EDIT_DELAY_MS);
  }
  else
  {
    if (changeDisplayBrightness)
    {
      displayBrightnessMode = (displayBrightnessMode + 1) % 3;
      int8_t brightness = displayBrightnessMode * 4 - 1;
      display.setBrightness(brightness > 0 ? brightness : 0);
      
      changeDisplayBrightness = false;
    }
    
    showTime();
    delay(DELAY_MS);
  }
}
