#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

//#include <Base64.h>
//#include <DallasTemperature.h>
//#include <OneWire.h>
//#include <DS18B20.h>
#include <Base64.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS (2)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

double temperature;

ESP8266WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println();
    WiFiMulti.addAP("Rob", "xxxYourPwd");
}

void loop()
{
    sensors.requestTemperatures(); 
    temperature = sensors.getTempCByIndex(0);
    String stringToPrint = "Temperature = ";
    stringToPrint += temperature;
    stringToPrint += "*C.";
    Serial.println(stringToPrint);
    
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED))
    {
        Serial.println("WiFiMulti.run() == WL_CONNECTED");
        
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");

        http.begin("http://192.168.4.106:8010/"); //HTTP
        //http.begin("http://127.0.0.1:8010/");

        Serial.print("[HTTP] addHeader...\n");
        http.addHeader("Content-Type", "application/json");

        Serial.print("[HTTP] POST...\n");
        //String stringToPost += sprintf("%s%f%s", "{\"readings\": [", temperature, "]}");
        //http.POST(stringToPost);
        http.POST("{\"readings\": [10, 20, 15]}"); // przykladowe dane

        Serial.print("[HTTP] writeToStream...\n");
        http.writeToStream(&Serial);

        Serial.print("\n[HTTP] end...\n");
        http.end();
    }
    else
    {
      Serial.println("WiFiMulti.run() !!!!!!!= WL_CONNECTED");
    }

    delay(1000);
}
