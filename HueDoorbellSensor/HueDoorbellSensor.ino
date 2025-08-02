#include <ESP8266WiFi.h>

// WiFi credentials
const char* ssid = "WiFi name";       // replace with your wifi name
const char* password = "WiFi password";   // replace with your wifi password

// IP address of diyHue bridge/emulator
const char* bridgeIp = "192.168.xxx.xxx"; // replace with the hue emulator device ip

// GPIO where the optocoupler output is connected
#define DOORBELL_PIN 5

byte mac[6];
int lastState = HIGH;

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5) {
      result += ':';
    }
  }
  return result;
}

void sendHttpRequest()
{
  WiFiClient client;
  String url = "/switch?mac=" + macToStr(mac) + "&button=1000";
  client.connect(bridgeIp, 80);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + bridgeIp + "\r\n" +
               "Connection: close\r\n\r\n");
}

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(DOORBELL_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.macAddress(mac);

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
  }

  // register device
  WiFiClient client;
  String url = "/switch?devicetype=ZLLSwitch&mac=" + macToStr(mac);
  client.connect(bridgeIp, 80);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + bridgeIp + "\r\n" +
               "Connection: close\r\n\r\n");
}

void loop()
{
  int state = digitalRead(DOORBELL_PIN);
  if (state == LOW && lastState == HIGH) {
    sendHttpRequest();
  }
  lastState = state;
  delay(50);
}

