#ifndef MI_WIFI_H
#define MI_WIFI_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#define A_AP 10000

class MiWiFi
{
    public:
        void connect(const char* ssid, const char* passwd, uint8_t wifi_mode);

    private:
        void mode_ap(const char* ssid, const char* passwd);
        void mode_sta(const char* ssid, const char* passwd);
};

#endif