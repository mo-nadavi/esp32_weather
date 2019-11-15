#include <Arduino.h>
#include "JeeUI2.h"

jeeui2 jee;

void interface();

void setup() {
  Serial.begin(11520);

  jee.ap(10000);
  jee.led(2, true);

  jee.var("ssid", "");
  jee.var("passwd", "");
  jee.var("wifi", "STA");

  Serial.println(jee.buf);

  jee.ui(interface);
  jee.begin();
}

void btn()
{
  static int cnt;
  cnt++;

  Serial.println("Button: " + String(cnt));
}

void loop() {
  jee.handle();
  jee.btnCallback("btn", btn);
}

void interface()
{
  jee.app("Wearther");

  jee.menu("home");
  jee.menu("wifi");
  jee.menu("settings");

  // start page "home" 
  jee.page();
  jee.text("ssid", "Name WiFi");
  jee.text("passwd", "Password WiFi");

  jee.option("STA", "STA");
  jee.option("STA", "STA");
  jee.select("wifi", "Mode WiFi");
  jee.button("btn", "#00FF00", "Button");

  // end page
  jee.page();
}