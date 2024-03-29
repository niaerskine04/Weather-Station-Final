//##################################################################################################################
//##                                      ELET_2415 WEATHER STATION SYSTEM CODE                                   ##
//##                                                                                                              ##
//##################################################################################################################

//SECTION 1: LIBRARY IMPORTS
//note: Please add in library for Soil moisture sensor

#include "Arduino.h"
#include <rom/rtc.h>
#include <math.h>  // https://www.tutorialspoint.com/c_standard_library/math_h.htm
#include <ctype.h>
#include <SPI.h>
#include <Wire.h>

//LIBRARIES FOR CIRCUIT COMPONENTS
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


#ifndef FORECAST_H
#include "foreCast.h"
#endif



#ifndef ARDUINO_H
#include <Arduino.h>
#endif

#ifndef ARDUINOJSON_H
#include <ArduinoJson.h>
#endif

#ifndef _WIFI_H
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#include <stdio.h>
#endif

// IMPORT FONTS FOR TFT DISPLAY
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define ARDUINOJSON_USE_DOUBLE      1 

//SECTION 2: DEINITION OF PINS ON ESP32
#define TFT_DC 17
#define TFT_CS 5
#define TFT_RST 16
#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO 19
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST, TFT_MISO);

#define DHT_OUT 15
#define DHTTYPE DHT22
DHT dht(DHT_OUT, DHTTYPE);

#define BMP_SDA (21)
#define BMP_CS (5)
#define BMP_SD0 (25)
#define BMP_SCL (22)

Adafruit_BMP280 bmp;  // I2C Interface

#define SOIL_OUT 33

#define BTN_A 25
#define BTN_B 26

//SECTION 3: MQTT LABELS, CREDENTIALS AND HANDLES
static const char* pubtopic = "620155827";                         // Add your ID number here
static const char* subtopic[] = { "620155827_sub", "/elet2415" };  // Array of Topics(Strings) to subscribe to
static const char* mqtt_server = "www.yanacreations.com";          // Broker IP address or Domain name as a String
static uint16_t mqtt_port = 1883;

// WIFI CREDENTIALS
const char* ssid       = "CWC-6848515"; // Add your Wi-Fi ssid
const char* password   = "ddcdwwSWg4cb"; // Add your Wi-Fi password

// const char* ssid = "MonaConnect";  // Add your Wi-Fi ssid
// const char* password = "";         // Add your Wi-Fi password

// TASK HANDLES
TaskHandle_t xMQTT_Connect = NULL;
TaskHandle_t xNTPHandle = NULL;
TaskHandle_t xLOOPHandle = NULL;
TaskHandle_t xUpdateHandle = NULL;
TaskHandle_t xButtonCheckeHandle = NULL;

//FUNCTION DECLARATIONS
void checkHEAP(const char* Name);  // RETURN REMAINING HEAP SIZE FOR A TASK
void initMQTT(void);               // CONFIG AND INITIALIZE MQTT PROTOCOL
unsigned long getTimeStamp(void);  // GET 10 DIGIT TIMESTAMP FOR CURRENT TIME
void callback(char* topic, byte* payload, unsigned int length);
void initialize(void);
bool publish(const char* topic, const char* payload);  // PUBLISH MQTT MESSAGE(PAYLOAD) TO A TOPIC
void vButtonCheck( void * pvParameters );
void vUpdate(void* pvParameters);


////important imports
#ifndef NTP_H
#include "NTP.h"
#endif

#ifndef MQTT_H
#include "mqtt.h"
#endif
//VARIABLE DECLARATION
double humidity;
double temperature;
double heatIndex;
double pressure;
double alt;
int soil_m = 0;
int count=0;

const int AirValue = 3600;   //you need to replace this value with Value_1
const int WaterValue = 1500;  //you need to replace this value with Value_2
int soilMPercent=0;


//WEATHER STATION SETUP SECTION
void setup() {
  // put your setup code here, to run once:
  /* Default settings from datasheet.  */
  Serial.begin(115200);  // INIT SERIAL
  tft.begin();
  dht.begin();
  bmp.begin(0x76);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);

  // tft.drawBitmap(100, 25, partlyCloudyDay, 50, 50, ILI9341_WHITE, ILI9341_BLACK);
  // tft.drawBitmap(100, 75, sun, 50, 50, ILI9341_WHITE, ILI9341_BLACK);
  // tft.drawBitmap(100, 125, snow, 50, 50, ILI9341_WHITE, ILI9341_BLACK);
  // tft.setCursor(30, 220);
  // tft.setTextColor(ILI9341_GREEN);
  // tft.setTextSize(3);
  // tft.print("WEATHER");
  // tft.setCursor(80, 250);
  // tft.setTextSize(3);
  // tft.setTextColor(ILI9341_GREEN);
  // tft.print("STATION");
  // tft.setCursor(100,290);
  // tft.setTextSize(2);
  // tft.setTextColor(ILI9341_ORANGE);
  // tft.print("2024");
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  initialize();
  vButtonCheckFunction();
}

void loop() {
  // vTaskDelay(1000 / portTICK_PERIOD_MS);
}

//####################################################################
//#             UTIL FUNCTIONS FOR WEATHER STATION                   #
//####################################################################
void vButtonCheck(void* pvParameters) {
  configASSERT(((uint32_t)pvParameters) == 1);

  for (;;) {
    // Add code here to check if a button(S) is pressed
    // then execute appropriate function if a button is pressed

    // 1. Implement button1  functionality
   
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void vUpdate(void* pvParameters) {
       configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

      for( ;; ) {
         
        //reading data from the sensors
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  heatIndex = dht.computeHeatIndex(temperature, humidity);
  pressure = bmp.readPressure();
  alt = bmp.readAltitude(1013.25);
  soil_m = analogRead(SOIL_OUT);


  //printing data to the serial monitor
  Serial.print("***********Today's Stats************");
  Serial.println();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("*C");
  Serial.println();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println();
  Serial.print("Heat Index: ");
  Serial.print(heatIndex);
  Serial.print(" Celcius");
  Serial.println();
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print("Pa");
  Serial.println();
  Serial.print("Altitude: ");
  Serial.print(alt);
  Serial.print("m");
  Serial.println();
  Serial.print("Soil Moisture: ");

  soilMPercent = map(soil_m, AirValue, WaterValue, 0, 100);//calibration of soil mpisture sensor
  if(soilMPercent >= 100)
  {
    soilMPercent= 100;
    
  }
  else if(soilMPercent <=0)
  {
    soilMPercent= 0;

  }

  Serial.print(soilMPercent);
  Serial.println("%");
    
  
  Serial.print("************end of stats************");
  Serial.println();
  
   
    //tft.setFont(&FreeSansBold18pt7b);
    tft.drawRoundRect(10,10,220,50,5,ILI9341_WHITE);
    tft.setCursor(43,18);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_MAGENTA);
    tft.print("TODAY'S STATS ");
    tft.setCursor(60,35);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("LET'S G0:)");

    tft.drawRoundRect(65,65,165,50,5,ILI9341_WHITE);
    tft.drawBitmap(5,68, partlyCloudyDay, 50, 50, ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(70,70);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_GREEN);
    tft.print("TEMP:");
    tft.setCursor(90,93);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
    tft.println(temperature);
    tft.setCursor(160,93);
    tft.print("*C");

    tft.drawRoundRect(10,120,165,50,5,ILI9341_WHITE);
    tft.drawBitmap(185,125, sun, 50, 50, ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(15,125);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_GREEN);
    tft.print("HUMIDITY:");
    tft.setCursor(50,150);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.print(humidity);

    tft.drawLine(120,178,120,315,ILI9341_MAGENTA);
    tft.drawLine(10,250,230,250,ILI9341_MAGENTA);

    tft.setCursor(10,185);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_ORANGE);
    tft.print("HEAT");
    tft.setCursor(10,200);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_ORANGE);
    tft.print("INDEX");
    tft.setCursor(10,230);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.print(heatIndex);
    tft.setCursor(72,237);
    tft.setTextSize(1);
    tft.print("Celcius");

    tft.setCursor(135,185);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_ORANGE);
    tft.print("PRESSURE");
    tft.setCursor(123,230);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.print(pressure);
    tft.setCursor(220,235);
    tft.setTextSize(1);
    tft.println(" Pa");

    tft.setCursor(10,260);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_ORANGE);
    tft.print("ALTITUDE");
    tft.setCursor(10,300);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
    tft.print(alt);
    tft.println(" m");

    tft.setCursor(135,255);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_ORANGE);
    tft.print("SOIL");
    tft.setCursor(135,270);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_ORANGE);
    tft.print("MOISTURE");
    tft.setCursor(132,300);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.print(soilMPercent);
    tft.setCursor(170,305);
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_WHITE);
    tft.println("Percent");

            // Task code goes here.
          // 1. Create JSon object
          StaticJsonDocument<1000> doc;
          // 2. Create message buffer/array to store serialized JSON object
          char message[1100]  = {0};
          // 3. Add key:value pairs to JSon object based on above schema
          doc["id"] = "620155827";
          doc["timestamp"] = getTimeStamp();
          doc["temperature"] =temperature;
          doc["humidity"]= humidity;
          doc["heatindex"]=heatIndex;
          doc["pressure"]=pressure;
          doc["altitude"]=alt;
          doc["soilmoisture"]=soilMPercent;
          // 4. Seralize / Covert JSon object to JSon string and store in message array
          serializeJson(doc, message);
          // 5. Publish message to a topic sobscribed to by both backend and frontend
          if(mqtt.connected()){
            publish(pubtopic, message);
          }

           vTaskDelay(5000 / portTICK_PERIOD_MS);
       }
}

unsigned long getTimeStamp(void) {
   // RETURNS 10 DIGIT TIMESTAMP REPRESENTING CURRENT TIME
   time_t now;
   time(&now); // Retrieve time[Timestamp] from system and save to &now variable
   return now;
}

void callback(char* topic, byte* payload, unsigned int length) {
  // ############## MQTT CALLBACK  ######################################
  // RUNS WHENEVER A MESSAGE IS RECEIVED ON A TOPIC SUBSCRIBED TO

  Serial.printf("\nMessage received : ( topic: %s ) \n",topic );
  char *received = new char[length + 1] {0};

  for (int i = 0; i < length; i++) {
    received[i] = (char)payload[i];
  }

  // PRINT RECEIVED MESSAGE
  Serial.printf("Payload : %s \n",received);


  // CONVERT MESSAGE TO JSON
  StaticJsonDocument<1200> doc;
  DeserializationError error = deserializeJson(doc, received);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // PROCESS MESSAGE
  
}

bool publish(const char* topic, const char* payload) {
     bool res = false;
     try{
        res = mqtt.publish(topic,payload);
        // Serial.printf("\nres : %d\n",res);
        if(!res){
          res = false;
          throw false;
        }
     }
     catch(...){
      Serial.printf("\nError (%d) >> Unable to publish message\n", res);
     }
  return res;
}
