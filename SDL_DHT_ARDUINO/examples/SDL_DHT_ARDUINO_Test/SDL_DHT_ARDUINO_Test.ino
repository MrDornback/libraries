// Example testing sketch for various DHT humidity/temperature sensors
// Modified from code originally written by ladyada, public domain
// Code re-written and re-named by Alex Dornback April 2020

// Does NOT require either of the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

//  This is the only DHT library you need right now
#include "SDL_DHT_ARDUINO.h"

#define serialSpeed 115200  
// !!  This speed will be overriden and set too 74880 if SDLDHTA_DEBUG_FLAG is set to true

// 74880 will also display internal diagnostic information if any issues occur
// I pulled the serialSpeed into a variable so that we can re-use it if needed throughout
//   the code and it is easier to change up here. Using int, not #define so it can be changed if necessary later.

#define SDLDHTA_DEBUG_FLAG true
//  I have named this cryptically so that there should not be any name conflicts
//    with other libraries.  This is a boolean flag to show debug info when running.

// serialSpeed setting has been moved into setup() so that I can adjust based on DEBUG_FLAG
//   if DEBUG_FLAG is true, then I want to set serialSpeed to 74880 to get additional debugging information
//   else I want serialSpeed set to 115200

#define DHTPIN 2 // 13     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

/*
  // Connect pin 1 (on the left) of the sensor to +5V
  // NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
  // to 3.3V instead of 5V!
  // Connect pin 2 of the sensor to whatever your DHTPIN is
  // Connect pin 4 (on the right) of the sensor to GROUND
  // Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

  // Initialize DHT sensor.
  // Note that older versions of this library took an optional third parameter to
  // tweak the timings for faster processors.  This parameter is no longer needed
  // as the current DHT reading algorithm adjusts itself to work on faster procs.

  // I have considered making this a different name, however dht is pretty standard
  //  and so I want to make it easier on all developers
*/

DHT dht(DHTPIN, DHTTYPE);

/* Global variable LED_BUILTIN = GPIO 2
      NodeMCU GPIO 2 (Blue LED on ESP8266 chip)
      NodeMCU GPIO 16 (Red LED close to microUSB port)
*/

void setup() {

  if (SDLDHTA_DEBUG_FLAG) {

    //  Should include a function to ping the other serial speeds or 
    //    check which serial speed the IDE is set to and pring a message 
    //    to switch to the right channel.

    Serial.begin(74880);

    Serial.println("\n\nRunning: " + String(__FILE__));
    String thisBoard = ARDUINO_BOARD;
    Serial.print("Board: "); Serial.println(ARDUINO_BOARD);
    Serial.println("Port Speed: " + String(serialSpeed));
    Serial.println("Last Upload:  " + String(__DATE__) + "\t" + String(__TIME__));

  } else {
    Serial.begin(serialSpeed);
  }

  Serial.println();

  Serial.println("tempC\tTempF\tHumid\tDewpt\tHtIdxC\tHtIdxF\tHumiIdx");
  Serial.println("(°c)\t(°F)\t(%)\t(°F)\t(°c)\t(°F)\t(%)");

  pinMode(LED_BUILTIN, OUTPUT);

  dht.begin();
}

float preTemp, preHumi = -1;
float currTemp, currHumi = -2;

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  float dht_humi, dht_tempc, dht_tempf, dht_dewpt, dht_heatidxc, dht_heatidxf, dht_humiidxc, dht_humiidxf = -1;
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on by making the voltage LOW

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  dht_humi = dht.readHumidity();
  // Read temperature as Celsius (the default)
  dht_tempc = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  dht_tempf = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(dht_humi) || isnan(dht_tempc) || isnan(dht_tempf)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  currTemp = dht_tempc;
  currHumi = dht_humi;
  if (currTemp != preTemp | currHumi != preHumi) {
    preTemp = currTemp;
    preHumi = currHumi;

    dht_dewpt = dht.computeDewpoint(dht_tempf, dht_humi);  // temp humi isFahrenheit

    // Compute heat index in Fahrenheit (the default)
    // dht_heatidx = heatIndex(Fahrenheit(dht_temp), dht_humi);
    dht_heatidxf = dht.computeHeatIndex(dht_tempf, dht_humi);  //  temp, humi, isFahrenheit
    // Compute heat index in Celsius (isFahrenheit = false)
    dht_heatidxc = dht.computeHeatIndex(dht_tempc, dht_humi, false);

    dht_humiidxc = dht.computeHumiIndex(dht_tempc, dht_dewpt, false);  // temp dewpoint isFahrenheit //  !! NMF
    dht_humiidxf = dht.computeHumiIndex(dht_tempf, dht_dewpt); // NMF

    Serial.print(dht_tempc, 0);
    Serial.print("\t");
    Serial.print(dht_tempf, 0);
    Serial.print("\t");
    Serial.print(dht_humi, 0);
    Serial.print("\t");
    Serial.print(dht_dewpt, 0);
    Serial.print("\t");
    Serial.print(dht_heatidxc, 0);
    Serial.print("\t");
    Serial.print(dht_heatidxf, 0);
    Serial.print("\t");
    Serial.print(dht_humiidxc, 0);

    Serial.println();
  }

  delay(200);

  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH

  //  Wait 10 seconds before next reading  (10000 = 10 seconds.  1000 = 1 second)
  delay(2000);
}
