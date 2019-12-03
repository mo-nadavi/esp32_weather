#include "MiUI.h"

// construct
MiUI::MiUI() 
{

}

void MiUI::led(uint8_t pin) 
{

}

String MiUI::param(String key) 
{ 
  DynamicJsonDocument doc(10000);
  deserializeJson(doc, config);
  String value = doc[key];
  Serial.print("READ: ");
  Serial.println("key (" + key + ") value (" + value + ")");
  
  return value;
  //serializeJson(doc, config);
} 

void MiUI::var(String key, String value) 
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

void MiUI::debug() 
{ 
  Serial.print("CONFIG: ");
  Serial.println(config);
  Serial.println("RAM: " + String(ESP.getFreeHeap()));
}

// void MiUI::init()
// {
//   conf_load();
// }

void MiUI::begin()
{
  // full_reset();
  
  conf_load();
  non_wifi_var();
  wifi_connect();
  server_run();
}

void MiUI::ui(void (*uiFunction) ())
{
  processor = uiFunction;
}

void MiUI::handle()
{
  static unsigned long timer;
  unsigned int interval = 300;
  
  if (timer + interval > millis()) {
    return;
  }

  timer = millis();

  // btn();
  // led_handle();
  conf_autosave();
}

void MiUI::btnCallback(String name, buttonCallback response)
{
  // if (name == "GPIO0" && !digitalRead(BUTTON)){
  //     response();
  //     btn();
  // }
  
  if (btnui == name) {
    btnui = "";
    response();
  }
}