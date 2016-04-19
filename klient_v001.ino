#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.println();

    for(uint8_t t = 8; t > 0; t--)
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
    WiFiMulti.addAP("Rob", "xxxYourPwd");
}

void loop()
{
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
        http.POST("{\"readings\": [10, 20, 15]}"); //

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

