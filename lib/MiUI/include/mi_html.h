#ifndef MI_HTML_H
#define MI_HTML_H

#include <Arduino.h>

class MiHtml
{
    public:
        void app_name(String name);
        void text(String id, String label);
        void number(String id, String label);
        void time(String id, String label);
        void range(String id, int min, int max, float step, String label);
        void email(String id, String label);
        void MiHtml::password(String id, String label);
        void option(String value, String label);
        void select(String id, String label);
        void checkbox(String id, String label);
        void color(String id, String label);
        void button(String id, String color, String label);
        void textarea(String id, String label);
        void menu(String name);
        void page();
    private:
        String buf;
};

#endif