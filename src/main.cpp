#include <Arduino.h>
#include <_secrets.h>
#include "MiUI.h"

#define BTN_LED 2

MiUI miui = MiUI();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

void setup() {
  Serial.begin(115200);

  pinMode(BTN_LED, OUTPUT);

  miui.up(ssid, passwd, MODE_STA);
}

void loop() {
  
}