#ifndef MIUI_H
#define MIUI_H

#include <Arduino.h>

#ifdef ESP8266
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#else
#include "SPIFFS.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>

#include "mi_config.h"
#include "mi_wifi.h"
#include "mi_server.h"
#include "mi_html.h"

class MiUI
{
    typedef void (*uiCallback) ();
    typedef void (*buttonCallback) ();

    public:
        // construct
        MiUI();
        String param(String key);
        uiCallback processor;
        void led(uint8_t pin);
        void var(String key, String value);
        void init();
        void begin();
        void debug();
        void ui(void (*uiFunction) ());
        void handle();
        void btnCallback(String name, buttonCallback response);
        // html
        void app_name(String name);
        void app_by(String text);
        void menu(String route, String name);
        void page();
        void text(String id, String label);
        void number(String id, String label);
        void time(String id, String label);
        void range(String id, int min, int max, float step, String label);
        void email(String id, String label);
        void password(String id, String label);
        void option(String value, String label);
        void select(String id, String label);
        void checkbox(String id, String label);
        void radio(String id, String value);
        void color(String id, String label);
        void button(String id, String color, String label, String = BTN_DEFAULT);
        void textarea(String id, String label);
        void text_block(String text, String tag = "p");
        void list_item(String text);
        void list(String tag = "ul");
        void hr(String text, String direction = "left");
        void wifi_settings();
        // TODO блок по типу jtype=ready - который по указанному таймигу обновляет указанный текстовый блок
        void end();
        // server
        void response(String text);
        void response(String key, String value);

    private:
        // config
        bool do_save = false;
        unsigned long avto_save_timer;
        unsigned int asave = 1000; // ?
        String config = "{}";
        void conf_load();
        void conf_save();
        void conf_autosave();
        void conf_as();
        void non_wifi_var();
        void full_reset();
        // wifi
        const char* ssid_ap = "ESP32_AP";
        String ssid;
        String passwd;
        String ssid_list;
        String passwd_list;
        void wifi_connect();
        void wifi_mode_ap();
        void wifi_mode_sta();
        void wifi_scan();
        // server
        String buf;
        String op = "";
        uint8_t mn = 0;
        uint8_t pg = 0;
        String btnui = "";
        void server_run();
};

#endif