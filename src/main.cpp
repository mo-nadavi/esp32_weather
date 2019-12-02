#include <Arduino.h>
#include <_secret.h>
#include <MiUI.h>

MiUI miui = MiUI();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

void interface();

void setup() 
{
  Serial.begin(115200);

  miui.begin();
  miui.ui(interface);
  miui.debug();
}

void loop() 
{
  miui.handle();
}

void interface()
{
  miui.app_name("ESP32");
  miui.menu("", "Главная");
  miui.menu("wifi", "WiFi");
  miui.menu("settings", "Настройки");
  miui.page();
  miui.text_block("Какая то сводная ифва о модуле");
  miui.page();
  // miui.wifi_settings();
  miui.text_block("MAC-адрес: " + WiFi.macAddress());
  miui.hr("");
  miui.option(String(WIFI_AP), "Точка доступа (AP)");
  miui.option(String(WIFI_STA), "Клиент (STA)");
  miui.select("wifi_mode", "Режим WiFi");
  miui.text("ssid", "SSID WiFi");
  miui.password("passwd", "Пароль WiFi");
  miui.button("syster_reload", "", "Перезагрузить");
  // miui.text_block("Подключенные сети");
  // miui.text_block("Доступные сети");

  // int n = WiFi.scanNetworks();

  // if (n) {
  //   for (int i = 0; i < n; ++i) {
  //     miui.list_item(WiFi.SSID(i) + "   (" + String(WiFi.RSSI(i)) + " dBm)   " + ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "" : "&#128274;"));
  //   }

  //   miui.list();
  // }

  miui.page();
  miui.text_block("Настройки модуля");
  miui.end();
}