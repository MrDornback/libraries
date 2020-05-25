/* 
 *   AHD 4/20/2020
 *   Example from AM2315 library
 *   
 *   5-wire AM2315 with grey cable and grey plastic encasing
 *   
 *   REQUIRES 2 10k resisitors from SDA to Vin/Vcc and SCL to Vin/Vcc or will NOT work
 *   
 *   RED = VCC  >>  3.3v or 5v
 *   BLK = GND  >>  GND
 *   WHT = SCL  >>  A5
 *   YLW = SDA  >>  A4
 *   
 */
#include <Wire.h>
#include <ESG_AM2315.h>

/*************************************************** 
  This is an example for the AM2315 Humidity + Temp sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/1293

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  
  Additional improvements added by Daniel Sandoval/EasternStarGeek  
  8 July, 2013.  (Parent Library: Adafruit_AM2315)
  
  This version gets the Temperature and Humidity data with a single read, and is
  believed to solve some prior timing problems in the original.
  
  Be careful with return data array indexing!  Follow this example closely.

  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect RED of the AM2315 sensor to 5.0V
// Connect BLACK to Ground
// Connect WHITE to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect YELLOW to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4

/*
 *  Test with bmp180
 *  SCL = A4 UNO
 *  SDA = A5 UNO
 *  Vin = 3.3v
 *  GND = GND
 */
 
ESG_AM2315 am2315;

float dataAM2315[2];  //Array to hold data returned by sensor.  [0,1] => [Humidity, Temperature]
boolean OK;  // 1=successful read

void setup() {
  Serial.begin(115200);
  Serial.println("AM2315 Test!");
  Wire.begin();
 }

void loop() {
  OK = am2315.readData(dataAM2315);
  
  if (OK) {
  Serial.print("Hum: "); Serial.println(dataAM2315[0]);
  Serial.print("TempF: "); Serial.println(dataAM2315[1]);
  }
else
Serial.println("Sensor not found, check wiring & pullups!");

  delay(1000);
}
