#include <Arduino.h>
#include <_secret.h>
#include <MiUI.h>

MiUI miui = MiUI();

const char* ssid = WIFI_SSID;
const char* passwd = WIFI_PASSWD;

void setup() 
{
  Serial.begin(115200);

  miui.up(ssid, passwd, WIFI_STA);
}

void loop() 
{
  // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // delay(1000);
}