#include "mi_config.h"

void MiConfig::save()
{
    if(SPIFFS.begin()) {
    }

    File configFile = SPIFFS.open(F("/config.json"), "w");
    configFile.print(config);
    Serial.println(F("Save Config"));
}

void MiConfig::as(){
    // sv = true;
    // astimer = millis();
}

void MiConfig::load()
{
    if(SPIFFS.begin()) {
    }

    File pre_configFile = SPIFFS.open(F("/config.json"), "r");
    
    if (pre_configFile.readString() == "") {
        Serial.println(F("Failed to open config file"));
        save();
        return;
    }

    File configFile = SPIFFS.open(F("/config.json"), "r");
    config = configFile.readString();
    Serial.println(F("JSON config loaded"));
}