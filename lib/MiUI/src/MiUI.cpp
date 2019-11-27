#include "MiUI.h"

// construct
MiUI::MiUI() 
{

}

void MiUI::led(uint8_t pin) 
{

}

void jeeui2::var(String key, String value) 
{ 
    DynamicJsonDocument doc(10000);
    String result;
    deserializeJson(doc, config);
    JsonObject obj = doc.as<JsonObject>();
    obj[key] = value;
    Serial.print("WRITE: ");
    Serial.println("key (" + key + ") value (" + value.substring(0, 15) + ")");
    serializeJson(doc, result);
    config = result;

} 

void MiUI::up(const char* ssid, const char* passwd, uint8_t wifi_mode) 
{
  mi_wifi.connect(ssid, passwd, wifi_mode);
  mi_server.run();
}