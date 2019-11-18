#include <Arduino.h>
#include "JeeUI2.h"

#define BTN_LED 2

jeeui2 jee;

void interface();

void setup() {
  Serial.begin(115200);

  pinMode(BTN_LED, OUTPUT);

  jee.ap(10000);
  // jee.led(2, true);

  jee.var("ssid", "Mistim_2G");
  jee.var("pass", "231401M7#m7!");
  jee.var("wifi", "STA");

  jee.var("brightness", "25");
  jee.var("mode", "1");
  jee.var("speed", "25");
  jee.var("scale", "25");
  jee.var("text", "");

  Serial1.println(jee.buf);

  jee.ui(interface);
  jee.begin();
}

void btn()
{
  Serial.println("Button: " + String(digitalRead(BTN_LED)));

  digitalWrite(BTN_LED, !digitalRead(BTN_LED));
}

void loop() {
  jee.handle();
  jee.btnCallback("GPIO2", btn);
}

void interface()
{
  jee.app("Wearther");

  jee.menu("Главная");
  // jee.menu("WiFi");

  jee.page();

  jee.option("1", "Конфети");
  jee.option("2", "Огонь");
  jee.option("3", "Радуга вертикальная");
  jee.select("mode", "Режим");

  jee.text("text", "Test text");

  jee.range("brightness", 0, 100, 1, "Яркость");
  jee.range("speed", 0, 100, 1, "Скорость");
  jee.range("scale", 0, 100, 1, "Масштаб");

  jee.button("GPIO2", "#00FF00", "LED");

  jee.page();
}