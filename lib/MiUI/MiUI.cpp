#include "MiUI.h"
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// construct
MiUI::MiUI() {

}

void MiUI::led(uint8_t pin) {

}

void MiUI::up(const char* ssid, const char* passwd, char* mode) {
  if (mode == MODE_AP) {
    mode_ap(ssid, passwd);
  } else {
    mode_sta(ssid, passwd);
  }
}

void MiUI::mode_ap(const char* ssid, const char* passwd) {
  WiFi.softAP(ssid, passwd);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);
}

void MiUI::mode_sta(const char* ssid, const char* passwd) {
  Serial.println("Connecting to ");
  Serial.println(ssid);
  Serial.println("");

  //connect to your local wi-fi network
  WiFi.begin(ssid, passwd);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
}