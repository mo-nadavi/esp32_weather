#include "MiUI.h"

void MiUI::conf_load()
{
  if(!SPIFFS.begin(true)){
    Serial.println("Error while mounting SPIFFS");
    
    return;
  }

  File pre_configFile = SPIFFS.open(F("/config.json"), "r");
  
  if (pre_configFile.readString() == "") {
      Serial.println(F("Failed to open config file"));
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
  save_result = configFile.print(config);
  Serial.println(F("Save Config"));
}

void MiUI::non_wifi_var()
{
    String wifi_mode = param("wifi_mode");
    String ssid = param("ssid");
    String passwd = param("passwd");

    if(wifi_mode == "null") var("wifi_mode", String(WIFI_AP));
    if(ssid == "null") var("ssid", String(ssid_ap));
    if(passwd == "null") var("passwd", String(ssid_ap));
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