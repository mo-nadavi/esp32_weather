#include <Arduino.h>
#include <_secret.h>
#include <MiUI.h>

MiUI miui = MiUI();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

void interface();
void btn();

void setup() 
{
  Serial.begin(115200);

  miui.var("test_a", "");
  miui.var("ssid", ssid);
  miui.var("passwd", passwd);
  miui.var("wifi_mode", String(WIFI_STA));

  miui.begin();
  miui.ui(interface);
  miui.debug();
}

void loop() 
{
  // обработчик
  miui.handle();
  // calbacks
  miui.btnCallback("btnTest", btn);
}

void interface()
{
  miui.app_name("ESP32 Weather Station");
  miui.app_by("By Mistim");
  // Меню
  miui.menu("", "Главная");
  miui.menu("wifi", "WiFi");
  miui.menu("settings", "Настройки");
  // Главная
  miui.page();
  miui.text_block("Какая то сводная ифва о модуле");
  // WiFi
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

  // Настройки
  miui.page();
  miui.text_block("Настройки модуля");
  miui.text("test_a", "Test field");
  miui.button("btnTest", "", "btn test");
  // Конец контента
  miui.end();
}

void btn() {
  static int cnt;
  cnt++;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Btn " + String(cnt));
}