#ifndef MI_CONFIG_H
#define MI_CONFIG_H

#include <Arduino.h>

#ifdef ESP8266
#include <FS.h>
#else
#include "SPIFFS.h"
#endif

class MiConfig
{
    private:
        String config = "{}";
        void load();
        void save();
        void as();
};

#endif