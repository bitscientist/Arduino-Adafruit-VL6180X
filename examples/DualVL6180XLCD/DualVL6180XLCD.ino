// Multiple VL6180X sensors using modified Adafruit library

#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <LiquidCrystal_I2C.h>

// Define the sensor I2C addresses
#define Sensor0Address 0x20
#define Sensor1Address 0x30
// Wire these pins to the GPIO0 pin of VL6180x
const int Sensor0ResetPin = 10;
const int Sensor1ResetPin = 11;

Adafruit_VL6180X Sensor0 = Adafruit_VL6180X();
Adafruit_VL6180X Sensor1 = Adafruit_VL6180X();

// Set the LCD address, and set for a 16 char and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//LiquidCrystal_I2C lcd(0x3f, 16, 2);
// Set the LCD address, and set for a 20 char and 4 line display
//LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(0x3f, 20, 4);


void setup()
{
  uint8_t status;

  // Initialize the LCD
  lcd.begin();
  lcd.clear();
  lcd.setBacklight(1);

  // Initialize pins
  pinMode(Sensor0ResetPin,OUTPUT);
  pinMode(Sensor1ResetPin,OUTPUT);
  digitalWrite(Sensor0ResetPin, LOW);
  digitalWrite(Sensor1ResetPin, LOW);
  delay(100);

  Wire.begin();

  Serial.begin(115200);
  // wait for serial port to open on native usb devices
  while (!Serial)
  {
    delay(1);
  }
  Serial.println("Adafruit VL6180x test");

  // Initialize Sensor 0
  digitalWrite(Sensor0ResetPin, HIGH);
  delay(100);
  status = Sensor0.begin(Sensor0Address);
  if (!status)
  {
    Serial.println("Sensor 0: FAIL");
    Serial.println(Sensor0.read8(I2C_ADDRESS),HEX); // read I2C address
    lcd.setCursor(0,0);
    lcd.print("Sensor 0: FAIL");
   //while (1);
  }
  else
  {
    Serial.println("Sensor 0: OK");
    Serial.println(Sensor0.read8(I2C_ADDRESS),HEX); // read I2C address
    lcd.setCursor(0,0);
    lcd.print("Sensor 0: OK");
  }

  // Initialize Sensor 1
  digitalWrite(Sensor1ResetPin, HIGH);
  delay(100);
  status = Sensor1.begin(Sensor1Address);
  if (!status)
  {
    Serial.println("Sensor 1: FAIL");
    Serial.println(Sensor1.read8(I2C_ADDRESS),HEX); // read I2C address
    lcd.setCursor(0,1);
    lcd.print("Sensor 1: FAIL");
    //while (1);
  }
  else
  {
    Serial.println("Sensor 1: OK");
    Serial.println(Sensor1.read8(I2C_ADDRESS),HEX); // read I2C address
    lcd.setCursor(0,1);
    lcd.print("Sensor 1: OK");
  }

  delay(500);
}


void loop()
{
  float lux;
  uint8_t range;
  uint8_t status;

  lux = Sensor0.readLux(VL6180X_ALS_GAIN_5);
  //Serial.print("Lux 0: "); Serial.println(lux);
  range = Sensor0.readRange();
  status = Sensor0.readRangeStatus();

  if (status == VL6180X_ERROR_NONE)
  {
    Serial.print("Sensor 0: "); Serial.print(range); Serial.println(" mm");
    lcd.setCursor(0,0);
    lcd.print("Sensor 0: "); lcd.print(range); lcd.print(" mm ");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Sensor 0: ERROR ");

  // Some error occurred
  Serial.print("Sensor 0: ");
  if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
    Serial.println("System error");
  }
  else if (status == VL6180X_ERROR_ECEFAIL) {
    Serial.println("ECE failure");
  }
  else if (status == VL6180X_ERROR_NOCONVERGE) {
    Serial.println("No convergence");
  }
  else if (status == VL6180X_ERROR_RANGEIGNORE) {
    Serial.println("Ignoring range");
  }
  else if (status == VL6180X_ERROR_SNR) {
    Serial.println("Signal/Noise error");
  }
  else if (status == VL6180X_ERROR_RAWUFLOW) {
    Serial.println("Raw reading underflow");
  }
  else if (status == VL6180X_ERROR_RAWOFLOW) {
    Serial.println("Raw reading overflow");
  }
  else if (status == VL6180X_ERROR_RANGEUFLOW) {
    Serial.println("Range reading underflow");
  }
  else if (status == VL6180X_ERROR_RANGEOFLOW) {
    Serial.println("Range reading overflow");
  }
  }

  lux = Sensor1.readLux(VL6180X_ALS_GAIN_5);
  //Serial.print("Lux 1: "); Serial.println(lux);
  range = Sensor1.readRange();
  status = Sensor1.readRangeStatus();

  if (status == VL6180X_ERROR_NONE)
  {
    Serial.print("Sensor 1: "); Serial.print(range); Serial.println(" mm");
    lcd.setCursor(0,1);
    lcd.print("Sensor 1: "); lcd.print(range); lcd.print(" mm ");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("Sensor 1: ERROR ");

  // Some error occurred, print it out!
  Serial.print("Sensor 1: ");
  if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
    Serial.println("System error");
  }
  else if (status == VL6180X_ERROR_ECEFAIL) {
    Serial.println("ECE failure");
  }
  else if (status == VL6180X_ERROR_NOCONVERGE) {
    Serial.println("No convergence");
  }
  else if (status == VL6180X_ERROR_RANGEIGNORE) {
    Serial.println("Ignoring range");
  }
  else if (status == VL6180X_ERROR_SNR) {
    Serial.println("Signal/Noise error");
  }
  else if (status == VL6180X_ERROR_RAWUFLOW) {
    Serial.println("Raw reading underflow");
  }
  else if (status == VL6180X_ERROR_RAWOFLOW) {
    Serial.println("Raw reading overflow");
  }
  else if (status == VL6180X_ERROR_RANGEUFLOW) {
    Serial.println("Range reading underflow");
  }
  else if (status == VL6180X_ERROR_RANGEOFLOW) {
    Serial.println("Range reading overflow");
  }
  }

  delay(50);

  Serial.println("");
}

