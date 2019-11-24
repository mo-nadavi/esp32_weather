#include "MiUI.h"

// construct
MiUI::MiUI() {

}

void MiUI::led(uint8_t pin) 
{

}

void MiUI::up(const char* ssid, const char* passwd, uint8_t wifi_mode) 
{
  mi_wifi.connect(ssid, passwd, wifi_mode);
  mi_server.run();
}