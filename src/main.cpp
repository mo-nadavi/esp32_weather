#include <Arduino.h>
#include <_secret.h>
#include <MiUI.h>
#include <OpenWeather.h>

MiUI miui = MiUI();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

// OpenWeather open_weather = OpenWeather("67b6bff1964464654118e172e4e3a557");

void interface();
void btn();

void setup() 
{
  Serial.begin(115200);

  miui.init();

  miui.var("ssid", ssid);
  miui.var("passwd", passwd);
  miui.var("wifi_mode", String(WIFI_STA));

  miui.var("ow_api_key", "67b6bff1964464654118e172e4e3a557");
  miui.var("ow_language", "ru");
  miui.var("ow_units", "metric");
  miui.var("ow_id", "703448");
  miui.var("ow_refresh_rate", "10");
  miui.var("ow_last_refresh", "");

  miui.begin();
  miui.ui(interface);
  miui.debug();
}

void loop() 
{
  // обработчик
  miui.handle();
  // server.handleClient();
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
  // Настройки
  miui.page();
  // miui.text_block("Настройки модуля");
  miui.text("ow_api_key", "OpenWeather API Key");
  miui.option("ua", "Украинский");
  miui.option("en", "Английский");
  miui.option("ru", "Русский");
  miui.select("ow_language", "Язык денных в ответе");
  miui.option("metric", "metric");
  miui.option("imperial", "imperial");
  miui.select("ow_units", "Единицы измерения");
  miui.text("ow_id", "ID города");
  miui.text("ow_refresh_rate", "Частота обновления данных (в минутах)");
  miui.button("btnTest", "", "btn test");
  // Конец контента
  miui.end();
}

void btn() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  miui.response(digitalRead(LED_BUILTIN) ? "LED on" : "LED off");
}