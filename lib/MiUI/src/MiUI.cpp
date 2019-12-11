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

String MiUI::param(String key, String def_val)
{
  String value = param(key);

  if (value.length()) {
    return value;
  } else {
    return def_val;
  }
} 

void MiUI::var(String key, String value) 
{ 
  DynamicJsonDocument doc(10000);
  String result;
  deserializeJson(doc, config);
  JsonObject obj = doc.as<JsonObject>();
  obj[key] = value;
  Serial.print("WRITE: ");
  Serial.println("key (" + key + ") value (" + value + ")");
  serializeJson(doc, result);
  config = result;
}

void MiUI::debug() 
{ 
  Serial.print("CONFIG: ");
  Serial.println(config);
  Serial.println("RAM: " + String(ESP.getFreeHeap()));
}

void MiUI::init()
{
  conf_load();
}

void MiUI::begin()
{
  // full_reset();
  non_wifi_var();
  wifi_connect();
  server_run();
}

void MiUI::ui(void (*uiFunction) ())
{
  interface = uiFunction;
}

void MiUI::setCallback(void (*uiCallback) ())
{
  btn_callback = uiCallback;
}

void MiUI::setCallback(void (*saveCallback) (String name))
{
  save_callback = saveCallback;
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
  conf_save();
  response(save_result > 0 ? "Save" : "Not Save");
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

void MiUI::saveCallback(String name, paramCallback s_response)
{  
  s_response(name);
}