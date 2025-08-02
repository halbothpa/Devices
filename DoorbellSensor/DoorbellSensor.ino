#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
}

// configure WiFi credentials and bridge IP
const char* ssid = "WiFi name";        // replace with your wifi name
const char* password = "WiFi password"; // replace with your wifi password
const char* bridgeIp = "192.168.xxx.xxx"; //replace with the hue emulator device ip

// static ip configuration to reduce boot time
IPAddress strip_ip ( 192,  168,   0,  98); // choose an unique IP address
IPAddress gateway_ip ( 192,  168,   0,   1);
IPAddress subnet_mask(255, 255, 255,   0);

#define doorbell_pin 4 // optocoupler output connected to this GPIO

uint8_t mac[6];

void goingToSleep() {
  yield();
  delay(100);
  ESP.deepSleep(0);
  yield();
  delay(100);
}

String macToStr(const uint8_t* mac) {
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5) {
      result += ':';
    }
  }
  return result;
}

void sendDoorbellEvent() {
  WiFiClient client;
  String url = "/switch?mac=" + macToStr(mac) + "&button=1";
  client.connect(bridgeIp, 80);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + bridgeIp + "\r\n" +
               "Connection: close\r\n\r\n");
}

void setup() {
  pinMode(doorbell_pin, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(strip_ip, gateway_ip, subnet_mask);
  WiFi.macAddress(mac);

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
  }

  if (digitalRead(doorbell_pin) == HIGH) {
    sendDoorbellEvent();
  }

  goingToSleep();
}

void loop() {
}

