#include <Arduino.h>
#include <_secrets.h>
#include "MiUI.h"

#define BTN_LED 2

MiUI miui = MiUI();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

// WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(BTN_LED, OUTPUT);

  
}

void loop() {
  
}