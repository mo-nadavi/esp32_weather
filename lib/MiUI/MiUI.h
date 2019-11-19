#ifndef MIUI_H
#define MIUI_H

#include <Arduino.h>

#define MODE_AP "AP"
#define MODE_STA "STA"

class MiUI
{
    public:
        // construct
        MiUI();
        void led(uint8_t pin);
        void up(const char* ssid, const char* passwd, char* mode);

    private:
        void mode_ap(const char* ssid, const char* passwd);
        void mode_sta(const char* ssid, const char* passwd);
};

#endif