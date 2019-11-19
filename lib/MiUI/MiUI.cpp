#include "MiUI.h"
#include <WiFi.h>
#include <WebServer.h>

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// construct
MiUI::MiUI() {

}

void MiUI::led(uint8_t pin) {

}

void MiUI::up(char* ssid, char* passwd) {

}

void MiUI::mode_ap() {
  WiFi.softAP(_ssid, _passwd);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);
}

void MiUI::mode_sta() {
  Serial.println("Connecting to ");
  Serial.println(_ssid);
  Serial.println("");

  //connect to your local wi-fi network
  WiFi.begin(_ssid, _passwd);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
}