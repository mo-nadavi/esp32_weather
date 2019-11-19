#ifndef MIUI_H
#define MIUI_H

#include <Arduino.h>

class MiUI
{
    public:
        // construct
        MiUI();
        void led(uint8_t pin);
        void up(char* ssid, char* passwd);

    private:
        const char* _ssid;
        const char* _passwd;

        void mode_ap();
        void mode_sta();
};

#endif