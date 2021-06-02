/*
   OTA enabled firmware for the automatic mister https://github.com/Bdenouden/automatic-mister
   Based on the basicOTA example from the arduino ide

   Author: B. den Ouden
   02-06-2021
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <NTPClient.h>
#include <Servo.h>
#include "configuration.h"  // user defined configuration

// 'credentials.h' stores your credentials based on the 'credentials.h.default' template
// The actual credentials.h should never be pushed to a version control system like git
#include "credentials.h"

// set wifi credentials to const char type
const char* ssid = STASSID;
const char* password = STAPSK;

// create and configure NTP object
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, NTP_OFFSET, NTP_UPDATE);

// create servo object to control a serv
Servo servo;  


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("mister_automatic");

  // No authentication by default
  ArduinoOTA.setPassword(OTA_PASSWORD);

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  pinMode(LED_BUILTIN, OUTPUT);

  // start NTP client
  timeClient.begin();
  
  // attaches the servo on the pin defined by SERVO_PIN to the servo object
  servo.attach(SERVO_PIN);  
}

// init both variables to invalid value
uint8_t hour = 99;
uint8_t prevHour = 99; // prevents multiple triggers within a single valid hour

void loop() {
  ArduinoOTA.handle();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // get NTP time
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  hour = timeClient.getHours(); // returns hours in 24h format

  if (hour != prevHour && hour == 14) {
    //    water round 1
    prevHour = hour;
    spray();
  }
  else if (hour != prevHour && hour == 15) {
    //    water round 2
    prevHour = hour;
    spray();
  }
  delay(5000);

}

// activate motor and spray plants
void spray()
{
  uint8_t pos;
  Serial.println("Now misting the farm");
  for (uint8_t pump = 0; pump < 5; pump++)
  {
      servo.write(0);
      delay(500);
      servo.write(110);
      delay(500);
      yield();
  }
}
