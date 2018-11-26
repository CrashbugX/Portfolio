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

// ### LIBRARIES ###
#include <DHT.h>
//#include <SparkFunCCS811.h>
//#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal.h>

// ### DEFINITIONS ###
//#define CCS811_ADDR 0x5B // default I2C address
#define DHTTYPE DHT22 // Model of the DHT for the library
#define minutes 5 // PREHEAT TIME: 5 minutes
#define DHTTYPE DHT22     // Model of the DHT for the library

// ### DIGITAL INPUT PINS ###
#define DHTPIN 8
#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2

// ### ANALOG INPUT PINS ###
#define tempbot1 A2
#define tempbot2 A1
#define MQ4 A0


// ### VARIABLES ###
DHT dht(DHTPIN, DHTTYPE); // define the DHT
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//CCS811 myCCS811(CCS811_ADDR);

float temp_bot = 0;
int temp_bot1 = 0;
int temp_bot2 = 0;

float temp_top = 0;

float humidity;
float methane;
float methane_ppm;
//float c_dioxide;


// #################
// ### FUNCTIONS ###
// #################

void get_values(){
  // Getting the average bottom temperature
  temp_bot1 = analogRead(tempbot1);
  temp_bot2 = analogRead(tempbot2);
  temp_bot = (temp_bot1 + temp_bot2)/2;
  temp_bot = temp_bot * (500/1024); // temp is displayed in celcius

  // Getting the average top temperature
  temp_top = dht.readTemperature(); // dht should be given in celcius

  // Getting the Methane percentage
  methane = analogRead(MQ4);
  methane = methane * (5/1024);
  methane = ((5.0 * 10.0)/methane) - 10.0;
  methane = methane / 11.820;
  methane = (log10(methane) - 1.133) / -0.318;
  methane_ppm = pow(10, methane);
  methane_ppm = methane_ppm/10000;

  // Reading Humidity
  humidity = dht.readHumidity();

  // Getting the CO2 value
  //if(myCCS811.dataAvailable()){
    //myCCS811.readAlgorithmResults();
    //c_dioxide = myCCS811.getCO2(); // shows ppm already, no need for function
  //}  
}

void print_data(){
  // 1/3
  lcd.setCursor(0,0);
  lcd.print(String("DATA:"));
  lcd.setCursor(0,1);
  lcd.print(String("Humidity:") + String(humidity));
  delay(10000);
   
  // 2/3
  lcd.setCursor(0,0);
  lcd.print(String("Temp. Top: ") + String(temp_top));
  lcd.setCursor(0,1);
  lcd.print(String("Temp. Bot: ") + String(temp_bot));
  delay(10000);

  // 3/3
  lcd.setCursor(0,0);
  lcd.print(String("Methane: ") + String(methane_ppm));
  lcd.setCursor(0,1);
  //lcd.print(String("C,Dioxide: ") + String(c_dioxide));
  delay(10000);
}

void wait_minutes(int t){
  for(int j = 0; j < t; j++){
    for(int k = 0; k < 60; k ++){
      delay(1000);
    }
  }
}

void setup(){
  Serial.begin(9600);

  // inits
  dht.begin();
  //myCCS811.begin();
  lcd.begin(16, 2);
}

void loop(){
  lcd.print("Pre-calentando");
  wait_minutes(minutes);
  get_values();
  print_data();
}
