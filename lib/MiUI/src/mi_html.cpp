#include "MiUI.h"

void MiUI::app_name(String name)
{
    buf = "{\"app\":\"" + name + "\",";
}

void MiUI::app_by(String text)
{
    buf += "\"by\":\"" + text + "\",";
}

void MiUI::text(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"text\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::number(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"number\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::time(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"time\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::range(String id, int min, int max, float step, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"min\":\"" + String(min) + "\",";
    buf += "\"max\":\"" + String(max) + "\",";
    buf += "\"step\":\"" + String(step) + "\",";
    buf += "\"type\":\"range\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::email(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"email\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::password(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"password\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::option(String value, String label)
{
    op += "{\"label\":\"" + label + "\",\"value\":\"" + value + "\"},";
}

void MiUI::select(String id, String label)
{
    int lastIndex = op.length() - 1;
    op.remove(lastIndex);

    buf += "{\"html\":\"select\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\",";
    buf += "\"options\":[" + op + "]";
    buf += "},";
    op = "";
}

void MiUI::checkbox(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"type\":\"checkbox\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::radio(String id, String value)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"radio\",";
    buf += "\"value\":\"" + value + "\",";
    buf += "},";
}

void MiUI::color(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"color\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::button(String id, String color, String label, String style)
{
    buf += "{\"html\":\"button\",";
    buf += "\"type\":\"button\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"style\":\"" + style + "\",";
    buf += "\"color\":\"" + color + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::textarea(String id, String label)
{
    buf += "{\"html\":\"textarea\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"text\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiUI::text_block(String text, String tag)
{
    buf += "{\"html\":\"text_block\",";
    buf += "\"tag\":\"" + tag + "\",";
    buf += "\"text\":\"" + text + "\"";
    buf += "},";
}

void MiUI::list_item(String text)
{
    op += "{\"text\":\"" + text + "\"},";
}

void MiUI::list(String tag)
{
    int lastIndex = op.length() - 1;
    op.remove(lastIndex);

    buf += "{\"html\":\"list\",";
    buf += "\"tag\":\"" + tag + "\",";
    buf += "\"list\":[" + op + "]";
    buf += "},";
    op = "";
}

void MiUI::hr(String text, String direction)
{
    buf += "{\"html\":\"hr\",";
    buf += "\"direction\":\"" + direction + "\",";
    buf += "\"text\":\"" + text + "\"";
    buf += "},";
}

void MiUI::wifi_settings()
{
    text_block("MAC-адрес: " + WiFi.macAddress());
    hr("");
    option(String(WIFI_AP), "Точка доступа (AP)");
    option(String(WIFI_STA), "Клиент (STA)");
    select("wifi_mode", "Режим WiFi");
    text("ssid", "SSID WiFi");
    password("passwd", "Пароль WiFi");
    button("syster_reload", "", "Перезагрузить");
}

void MiUI::menu(String route, String name)
{
    if (mn == 0) {
        buf += "\"menu\":[";
    } else {
        int lastIndex = buf.length() - 1;
        buf.remove(lastIndex);
        buf.remove(lastIndex - 1);
        buf += ",";
    }

    buf += "\"" + name + "\"],";
    mn++;
}

void MiUI::page()
{
    if (pg == 0) {
        buf += "\"content\":[[";
    } else {
        int lastIndex = buf.length() - 1;

        if (buf[lastIndex] == ',') {
             buf.remove(lastIndex);
        }

        buf += "],[";
    }

    if (pg != mn) {
        pg++;
    }
}

void MiUI::end()
{
    int lastIndex = buf.length() - 1;

    if (buf[lastIndex] == ',') {
            buf.remove(lastIndex);
    }

    if (pg) {
        buf += "]]";
    }

    buf += "}";
    pg = 0;
    mn = 0;

    Serial.println(buf);
}