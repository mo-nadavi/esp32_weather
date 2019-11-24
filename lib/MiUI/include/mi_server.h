#ifndef MI_SERVER_H
#define MI_SERVER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

class MiServer
{
  public:
    void run();

  private:
    // String processor(const String& var);
        
};

#endif