#include "MiUI.h"

int wifi_status = WL_IDLE_STATUS; 

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void MiUI::wifi_connect() 
{
  if (param("wifi_mode").toInt() == WIFI_STA) {
    // wifi_scan();
    wifi_mode_sta();
  } else {
    wifi_mode_ap();
  }
}

void MiUI::wifi_mode_ap() 
{
  ssid = param("ssid");
  passwd = param("passwd");

  WiFi.disconnect();
  // WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), passwd.c_str());
  // WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(100);

  Serial.println("");
  Serial.print("Start Wi-Fi AP mode: ");  Serial.println(ssid);
  Serial.print("Password: "); Serial.println(String(passwd));
  Serial.print("Got IP: ");  Serial.println(WiFi.softAPIP());
}

void MiUI::wifi_mode_sta() 
{
  pinMode(LED_BUILTIN, OUTPUT);

  ssid = param("ssid");
  passwd = param("passwd");

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
    wifi_status = WiFi.begin(ssid.c_str(), passwd.c_str());
    unsigned long interval = millis();

    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
      delay(50);
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(50);
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      Serial.print(".");

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
    wifi_mode_ap();
  } else {
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  }
}

void MiUI::wifi_scan()
{
  uint8_t wifi_cnt = param("wifi_cnt").toInt();
  int n = WiFi.scanNetworks();
  char* list_ssid[n + 1] = {}; 

  if (wifi_cnt && n) {
    for (int i = 0; i < n; ++i) {
      list_ssid[i] = (char*) WiFi.SSID(i).c_str();

      for (int i = 0; i < wifi_cnt; ++i) {
        if (WiFi.SSID(i) == param("ssid_" + String(i))) {
          var("ssid", WiFi.SSID(i).c_str());
          var("passwd", param("passwd_" + String(i)));
        }
      }
    }
  }
}