#ifndef MIUI_H
#define MIUI_H

#include <Arduino.h>

#ifdef ESP8266
// #include <ESPAsyncTCP.h>
#include <FS.h>
#else
// #include <AsyncTCP.h>
#include "SPIFFS.h"
#endif

// #include <ESPAsyncWebServer.h>
#include "ArduinoJson.h"
#include <WebServer.h>
#include "mi_config.h"
#include "mi_wifi.h"
#include "mi_server.h"

class MiUI
{
    public:
        // construct
        MiUI();
        void led(uint8_t pin);
        void up(const char* ssid, const char* passwd, uint8_t wifi_mode);

    private:
        MiWiFi mi_wifi;
        MiServer mi_server;
};

#endif