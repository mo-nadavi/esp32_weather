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

  miui.var("test_a", "");

  miui.begin();
  miui.ui(interface);
  miui.debug();
}

void btn() {
  static int cnt;
  cnt++;
  Serial.println("Btn " + String(cnt));
}

void loop() 
{
  miui.handle();
  miui.btnCallback("btnTest", btn);
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
  miui.wifi_settings();
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
  miui.text("test_a", "Test field");
  miui.button("btnTest", "", "btn test");
  miui.end();
}