// Example testing sketch for various DHT humidity/temperature sensors
// Modified from code originally written by ladyada, public domain
// Code re-written and re-named by Alex Dornback April 2020

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "SDL_DHT_ARDUINO.h"

#define serialSpeed 115200
// I pulled this into a variable so that we can re-use it if needed throughout 
//   the code and it is easier to change up here.

#define SDLDHTA_DEBUG_FLAG true
//  I have named this cryptically so that there should not be any name conflicts 
//    with other libraries.  This is a boolean flag to show debug info when running.

#define DHTPIN 3     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

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

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(serialSpeed);
  
  if (SDLDHTA_DEBUG_FLAG) {
	  Serial.println("\n\nRunning: " + String(__FILE__));
	  String thisBoard = ARDUINO_BOARD;
	  Serial.println("Board: " + thisBoard);
	  Serial.println("Port Speed: " + String(serialSpeed));
	  Serial.println("Last Upload:  " + String(__DATE__) + "\t" + String(__TIME__));
  }
  
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  
  float dht_humi,dht_tempc,dht_tempf,dht_dewpt,dht_heatidxc,dht_heatidxf,dht_humiidxc,dht_humiidxf = -1;

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

  dht_dewpt = dht.computeDewPoint(dht_tempc, dht_humi);  // temp humi isFahrenheit

  // Compute heat index in Fahrenheit (the default)
  // dht_heatidx = heatIndex(Fahrenheit(dht_temp), dht_humi);
  dht_heatidxf = dht.computeHeatIndex(dht_tempf, dht_humi);  //  temp, humi, isFahrenheit
  // Compute heat index in Celsius (isFahrenheit = false)
  dht_heatidxc = dht.computeHeatIndex(dht_tempc, dht_humi, false);

  dht_humiidxc = dht.computeHumiIndex(dht_tempc, dht_dewpt, false);  // temp dewpoint isFahrenheit
  dht_humiidxf = dht.computeHumiIndex(dht_tempf, dht_dewpt);


  Serial.print(F("Humidity: "));
  Serial.print(dht_humi);
  Serial.print(F("%  Temperature: "));
  Serial.print(dht_tempc);
  Serial.print(F("°C "));
  Serial.print(dht_tempf);
  Serial.print(F("°F  Dew Point: "));
  Serial.print(dht_dewpt);
  Serial.print(F("  Heat index: "));
  Serial.print(dht_heatidxc);
  Serial.print(F("°C "));
  Serial.print(dht_heatidxf);
  Serial.print(F("°F  Humi index: "));
  Serial.print(dht_humiidxc);
  Serial.print(F("°C "));
  Serial.print(dht_humiidxf);
  Serial.print(F("°F"));
  
  Serial.println();
}
