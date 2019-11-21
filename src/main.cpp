#include <Arduino.h>
#include <_secrets.h>
#include "MiUI.h"

// #define BTN_LED 2

MiUI miui = MiUI();

const char* ssid = "Mistim_2G";
const char* passwd = "231401M7#m7!";

void setup() 
{
  Serial.begin(115200);

  // pinMode(BTN_LED, OUTPUT);

  miui.up(ssid, passwd, WIFI_STA);
}

void loop() 
{
  
}