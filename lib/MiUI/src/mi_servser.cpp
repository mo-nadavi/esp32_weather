#include "MiUI.h"

AsyncWebServer server(80);

void MiUI::server_run()
{
  // Инициализируем SPIFFS:
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
                // "При монтировании SPIFFS произошла ошибка"
    return;
  }

  // URL для корневой страницы веб-сервера:
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/template/index.html", String(), false);
  });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/template/favicon.ico", "image/x-icon", false);
  });

  server.on("/css/mg.min.css", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/template/css/mg.min.css.gz", "text/css");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  server.on("/js/app.js", HTTP_ANY, [](AsyncWebServerRequest *request){   
    request->send(SPIFFS, "/template/js/app.js", "application/javascript");
  });

  server.on("/post", HTTP_ANY, [this](AsyncWebServerRequest *request) {
    uint8_t params = request->params();
    AsyncWebParameter *param;
    String buf_;

    for (uint8_t i = 0; i < params; i++) {
      param = request->getParam(i);

      if (param->name().indexOf("BTN_") != -1) {
        btnui = param->name().substring(4, param->name().length());
        callback();
      } else {
        var(param->name(), param->value());
        handle();
      }
    }

    buf_ = buf;
    buf = "";
    
    request->send(200, "text/plain", buf_);
  });

  server.on("/load", HTTP_ANY, [this](AsyncWebServerRequest *request) { 
    interface();
    request->send(200, "text/plain", buf);
    buf = "";
    Serial.println("ECHO RAM: " + String(ESP.getFreeHeap()));
  });

  server.onNotFound([this](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });
 
  // Запускаем сервер:
  server.begin();
}

void MiUI::response(String text)
{
  if (buf) {
     buf += "\n" + text;
  } else {
     buf = text;
  }
}

void MiUI::response(String key, String value)
{
  buf = "TODO";
}