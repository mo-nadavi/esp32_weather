#include "mi_html.h"

void MiHtml::app(String name)
{
    buf = "{\"app\":\"" + name + "\",";
}

void MiHtml::text(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"text\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::number(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"number\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::time(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"time\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::range(String id, int min, int max, float step, String label)
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

void MiHtml::email(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"email\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::password(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"password\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::option(String value, String label)
{
    op += "{\"label\":\"" + label + "\",\"value\":\"" + value + "\"},";
}

void MiHtml::select(String id, String label)
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

void MiHtml::checkbox(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"type\":\"checkbox\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::color(String id, String label)
{
    buf += "{\"html\":\"input\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"color\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::button(String id, String color, String label)
{
    buf += "{\"html\":\"button\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"color\":\"" + color + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::textarea(String id, String label)
{
    buf += "{\"html\":\"textarea\",";
    buf += "\"id\":\"" + id + "\",";
    buf += "\"type\":\"text\",";
    buf += "\"value\":\"" + param(id) + "\",";
    buf += "\"label\":\"" + label + "\"";
    buf += "},";
}

void MiHtml::menu(String name)
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

void MiHtml::page()
{
    if (pg == 0) {
         buf += "\"content\":[[";
    } else {
        int lastIndex = buf.length() - 1;
        buf.remove(lastIndex);
        buf += "],[";
    }

    if (pg == mn) {
        int lastIndex = buf.length() - 1;
        buf.remove(lastIndex);
        buf.remove(lastIndex - 1);
        buf.remove(lastIndex - 2);
        //buf.remove(lastIndex - 3);
        buf += "]]}";
    } else {
        pg++;
    }
}