#include "MiUI.h"

const char* ssid_ap = "ESP32_AP";

void MiUI::conf_load()
{
  if(!SPIFFS.begin(true)){
    Serial.println("Error while mounting SPIFFS");
    
    return;
  }

  File pre_configFile = SPIFFS.open(F("/config.json"), "r");
  
  if (pre_configFile.readString() == "") {
      Serial.println(F("Failed to open config file"));
      // default params
      var("wifi_mode", String(WIFI_AP));
      var("ssid", String(ssid_ap));
      var("passwd", String(ssid_ap));
      var("wifi_cnt", "0");
      // create file
      conf_save();

      return;
  }

  File configFile = SPIFFS.open(F("/config.json"), "r");
  config = configFile.readString();
  Serial.println(F("JSON config loaded"));
}

void MiUI::conf_save()
{
  if (!SPIFFS.begin(true)) {
    Serial.println("Error while mounting SPIFFS");

    return;
  }

  File configFile = SPIFFS.open(F("/config.json"), "w");
  configFile.print(config);
  Serial.println(F("Save Config"));
}

void MiUI::conf_autosave()
{    
  if (!do_save) return;

  if (do_save && avto_save_timer + asave < millis()){
      conf_save();
      do_save = false;
      Serial.println("AutoSave");
      
      // upd();
      // mqtt_update();
  } 
}

void MiUI::conf_as(){
  do_save = true;
  avto_save_timer = millis();
}

void MiUI::full_reset()
{
  if (!SPIFFS.begin(true)) {
    Serial.println("Error while mounting SPIFFS");

    return;
  }

  if (SPIFFS.remove(F("/config.json"))){
    Serial.println("File successfully deleted");
  } else {
    Serial.print("Deleting file failed!");
  }
}