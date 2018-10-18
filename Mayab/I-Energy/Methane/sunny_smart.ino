// Biodigestor

 // In this project we will set up the following sensors for a biodigestor focused on methane production


// === BOTTOM ===
// Two temperature sensors for the botton   http://www.electronica60norte.com/producto/sensor-de-temperatura-encapsulado-ds18b20


// === TOP ===
// CO2 Sensor at the top                    http://www.electronica60norte.com/producto/mg-811-sensor-gas-co2
//                                          https://learn.sparkfun.com/tutorials/ccs811-air-quality-breakout-hookup-guide#arduino-library-and-usage
//
// Methane Sensor at the top                http://www.electronica60norte.com/producto/mq-4-sensor-de-gas-metano
// Humidity and Temp Sensor at the top      http://www.electronica60norte.com/producto/dht22-sensor-temperatura-y-humedad

// === CONTROL ===
// RTC                                      http://www.electronica60norte.com/producto/reloj-de-tiempo-real-ensamblado-ds1307
// DATA LOG                                 http://www.electronicstore.mx/inicio/113-shield-data-logger.html?search_query=shield&results=14


// WRITING ONTO THE SD CARD                 https://www.prometec.net/data-logger-shield/


// PREHEAT TIME: 5 minutes

// ### LIBRARIES ###
#include <DHT.h>;
#include <SparkFunCCS811.h>
#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include "RTClib.h"

// ### DEFINITIONS ###
#define eco true;
#define CCS811_ADDR 0x5B  // default I2C Address 
#define DHTTYPE DHT22     // Model of the DHT for the library
#define MQ4_min 256       // Minimum value readable in the MQ4
#define MQ4_slope 23      // Characteristic slope of the MQ4

// ### DIGITAL INPUTS PINS ###
#define DHTPIN          // DATA PIN of the DHT22

// ### ANALOG INPUTS PINS ###
#define tempbot1
#define tempbot2
#define MQ4

// ### VARIABLES ###
DHT dht(DHTPIN, DHTTYPE); // define the DHT
RCT_DS1307 RTC;           // define the Real Time Clock

File logfile;

const int chipSelect = 10;  // SD card pin select

float temp_bot = 0;
int temp_bot1 = 0;
int temp_bot2 = 0;

float temp_top = 0;

float humidity = 0;
float methane = 0;
float c_dioxide = 0;

CCS811 myCCS811(CCS811_ADDR);

void setup() {
  Serial.begin(9600);

  // inits
  DHT_init();
  CSS811_init();
  MQ4_init();
  LM35_init();
  SD_init();
  RTC_init();
}

void loop() {
  DateTime now;

  now = RTC.now();
  
  if(((now.minute()%10) == 0) && (now.second() == 0)){
    get_values();
    Print_Data();   // print values;
  }
  delay(1000);      // looping every second
}


void get_values(){
  // Getting the average bottom temperature
  temp_bot1 = analogRead(tempbot1);
  temp_bot2 = analogRead(tempbot2);
  temp_bot = (temp_bot1 + temp_bot2)/2;
  temp_bot = temp_bot * (5/1024);

  // Getting the average top temperature
  temp_top = dht.readTemperature();
  
  // Getting the Methane percentage
  methane = analogRead(MQ4);
  methane = methane - MQ4_min;
  methane = methane * MQ4_slope;

  // reading humidity
  humidity = dht.readHumidity();

  if(myCCS811.dataAvailable(){
    myCCS811.readAlgorithmResults();
    c_dioxide = myCCS811.getCO2(); // shows ppm already, no need to function
  }
}

void Print_Data(){
  // Printing Date
  logfile.print(now.day());
  logfile.print("/");
  logfile.print(now.month());
  logfile.print("/");
  logfile.print(now.year());
  logfile.print(" ; ");

  // Printing Time
  logfile.print(now.hour());
  logfile.print(":");
  logfile.print(now.minute());
  logfile.print(":");
  logfile.print(now.second());
  logfile.print(":");

  // Printing BTemp
  logfile.print(temp_bot);
  logfile.print(" ; "); 

  
  // Printing TTemp
  logfile.print(temp_top);
  logfile.print(" ; "); 

  // Printing Humidity
  logfile.print(humidity);
  logfile.print(" ; "); 

  // Printing CO2
  logfile.print(c_dioxide);
  logfile.print(" ; "); 

  // Printing Methane
  logfile.print(methane);
  logfile.print(" ; ");

  if( count++ > 64){
      logfile.flush();
      count = 0;
  }

  if(ECHO){
    // Printing date
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.print(now.year());
  Serial.print(" ; ");

  // Printing Time
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(":");

  // Printing BTemp
  Serial.print(temp_bot);
  Serial.print(" ; "); 

  
  // Printing TTemp
  Serial.print(temp_top);
  Serial.print(" ; "); 

  // Printing Humidity
  Serial.print(humidity);
  Serial.print(" ; "); 

  // Printing CO2
  Serial.print(c_dioxide);
  Serial.print(" ; "); 

  // Printing Methane
  Serial.print(methane);
  Serial.print(" ; ");
  }
}

void error (char *str){
  Serial.print("error: ");
  Serial.print(str);
  while(1); // halting after an error
}

// ### INITS ###
void SD_init(){
  pinMode(10, OUTPUT);
  
  if(!SD.begin(chipSelect)){
    error("No hay tarjeta SD.");
  } else {
    Serial.println("Tarjeta SD inicializada");
  }

  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }
  
  if (! logfile) {
    error("couldnt create file");
  }
  
  Serial.print("Logging to: ");
  Serial.println(filename);
}

void RTC_init(){
  Wire.begin();
  if(!RTC.begin()){
    logfile.println("No hay RTC.");
  } else {
    Serial.println("RTC correcto. Iniciando captura de datos");
  }
}

void DHT_init(){
  dht.begin();
}

void CCS811_init(){
  myCCS811.begin();
}

void MQ4_init(){
  // void
}

void LM35_init(){
  // void
}
