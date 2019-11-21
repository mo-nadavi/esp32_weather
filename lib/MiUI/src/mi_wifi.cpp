#include "mi_wifi.h"
#include <WebServer.h>

WebServer server(80);

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void MiWiFi::connect(const char* ssid, const char* passwd, uint8_t wifi_mode) 
{
  if (wifi_mode == WIFI_AP) {
    mode_ap(ssid, passwd);
  } else {
    mode_sta(ssid, passwd);
  }
}

void MiWiFi::mode_ap(const char* ssid, const char* passwd) 
{
  // WiFi.disconnect();
  // WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, passwd);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);

  Serial.println("Start Wi-Fi AP mode!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
}

void MiWiFi::mode_sta(const char* ssid, const char* passwd) 
{
  bool reconnect = false;

  Serial.print("Connecting to ");  Serial.println(ssid);
  Serial.println("");

  // WiFi.disconnect();
  // WiFi.mode(WIFI_OFF);
  // WiFi.mode(WIFI_STA);

  //connect to your local wi-fi network
  WiFi.begin(ssid, passwd);

  unsigned long interval = millis();

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    // delay(1000);
    // Serial.print(".");

    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);

    if (A_AP + interval < millis() && A_AP != 0) {
      reconnect = true;

      break;
    }
  }

  if (reconnect) {
    Serial.println("Fail start Wi-Fi as STA mode!");
    Serial.println("Restart as AP mode");

    // var("wifi", "AP");
    mode_ap(ssid, passwd);
  } else {
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  }
}