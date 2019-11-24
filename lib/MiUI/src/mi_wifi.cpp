#include "mi_wifi.h"

const char* ssid_ap = "ESP32_AP";
int wifi_status = WL_IDLE_STATUS; 

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void MiWiFi::connect(const char* ssid, const char* passwd, uint8_t wifi_mode) 
{
  if (wifi_mode == WIFI_STA) {
    mode_sta(ssid, passwd);
  } else {
    mode_ap(ssid_ap, passwd);
  }
}

void MiWiFi::mode_ap(const char* ssid, const char* passwd) 
{
  WiFi.disconnect();
  // WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, passwd);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);

  Serial.println("");
  Serial.print("Start Wi-Fi AP mode: ");  Serial.println(ssid_ap);
  Serial.print("Got IP: ");  Serial.println(WiFi.softAPIP());
}

void MiWiFi::mode_sta(const char* ssid, const char* passwd) 
{
  pinMode(LED_BUILTIN, OUTPUT);

  bool reconnect = false;
  static uint8_t cnt_try = 1;

  WiFi.disconnect();

  Serial.print("Connecting to ");  Serial.println(ssid);

  while (wifi_status != WL_CONNECTED) {
    if (cnt_try > MAX_CNT_TRY) {
      reconnect = true;
      break;
    }

    //connect to your local wi-fi network
    wifi_status = WiFi.begin(ssid, passwd);
    unsigned long interval = millis();

    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

      if (TIME_CONNECT + interval < millis() && TIME_CONNECT != 0) {
        Serial.println("");
        break;
      }
    }

    cnt_try++;
  }

  if (reconnect) {
    Serial.println("");
    Serial.println("Fail start Wi-Fi as STA mode!");
    Serial.println("Restart as AP mode");

    // var("wifi", "AP");
    mode_ap(ssid_ap, passwd);
  } else {
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  }
}