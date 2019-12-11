#include <Arduino.h>
#include <_secret.h>
#include <MiUI.h>
#include <OpenWeather.h>

#define SEC_TO_TIME 60000 // 60 sec

MiUI miui = MiUI();
OpenWeather ow = OpenWeather();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

unsigned long ow_interval = 0;
unsigned int ow_refresh_rate = 1;

void interface();
void btn();
void btnA();
void btnOwUpdate();
void after_save(String name);
void ow_update();

void setup() 
{
  Serial.begin(115200);

  miui.init();

  ow.option.api_key = miui.param("ow_api_key", "67b6bff1964464654118e172e4e3a557");
  ow.option.lang = miui.param("ow_language", "en");
  ow.option.units = miui.param("ow_units", "metric");
  ow.option.id = miui.param("ow_id", "703448").toInt();

  miui.var("ssid", ssid);
  miui.var("passwd", passwd);
  miui.var("wifi_mode", String(WIFI_STA));

  miui.var("ow_api_key", ow.option.api_key);
  miui.var("ow_language", ow.option.lang);
  miui.var("ow_units", ow.option.units);
  miui.var("ow_id", String(ow.option.id));
  miui.var("ow_refresh_rate", miui.param("ow_refresh_rate", String(ow_refresh_rate)));
  miui.var("ow_last_refresh", "");

  miui.setCallback([]() {
    miui.btnCallback("btnTest", btn);
    miui.btnCallback("btnA", btnA);
    miui.btnCallback("btnOwUpdate", btnOwUpdate);
  });

  miui.setCallback([](String name) {
    miui.saveCallback(name, after_save);
  });

  miui.begin();
  miui.ui(interface);
  miui.debug();
}

void loop() 
{
  ow_update();
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

  if(ow.get_error().length()) {
    miui.text_block("Ошибка обновления данных!");
    miui.text_block(ow.get_error());
  } else {
    Serial.println("Город: " + String(ow.weather.city));
    Serial.println(String(ow.weather.weather_descript));
    miui.text_block("Город: " + String(ow.weather.city));
    miui.text_block("Температура: " + String(ow.weather.temp));
    miui.text_block("Минимальная температура: " + String(ow.weather.temp_min));
    miui.text_block("Максимальная температура: " + String(ow.weather.temp_max));
    miui.text_block("Влажность: " + String(ow.weather.humidity));
    miui.text_block("Погодные условия: " + String(ow.weather.weather_descript));
    miui.text_block("Далление: " + String(ow.weather.pressure));
  }
  
  miui.button("btnOwUpdate", "", "Обновить");
  
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
  miui.text("ow_refresh_rate", "Частота обновления данных, мин.");
  miui.button("btnTest", "", "btn test");
  miui.button("btnA", "", "Test A");
  // Конец контента
  miui.end();
}

void btn() 
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  miui.response(digitalRead(LED_BUILTIN) ? "LED on" : "LED off");
}

void btnA()
{
  delay(500);
  miui.response("Test A!");
}

void btnOwUpdate()
{
  ow_interval = 0;
  miui.response("Обновите страницу!");
}

void after_save(String name)
{
  String param_ = miui.param(name);

  if (name == "ow_refresh_rate") {
    ow_refresh_rate = param_.toInt();
  }
  else if (name == "ow_api_key") {
    ow.option.api_key = param_.c_str();
  }
  else if (name == "ow_language") {
    ow.option.lang = param_.c_str();
  }
  else if (name == "ow_units") {
    ow.option.units = param_.c_str();
  }
  else if (name == "ow_id") {
    ow.option.id = param_.toInt();
  }

  Serial.println(name + ": " + param_);
}

void ow_update()
{
  if (ow_interval && ow_refresh_rate * SEC_TO_TIME + ow_interval > millis()) {
    return;
  } else {
    ow_interval = millis();
  }

  if (ow.current()) {
    miui.var("ow_last_refresh", String(millis()));

    Serial.println("OpenWeather success update!");
  } else {
    Serial.println("OpenWeather error update!");
  }
}