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

  // URL для файла «style.css»:
  server.on("/css/mg.min.css", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/template/css/mg.min.css.gz", "text/css");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // URL для файла «style.css»:
  // server.on("/css/grids-min.css", HTTP_ANY, [](AsyncWebServerRequest *request){
  //   AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/template/css/grids-min.css.gz", "text/css");
  //   response->addHeader("Content-Encoding", "gzip");
  //   request->send(response);
  // });

  // URL для файла «style.css»:
  // server.on("/css/side-menu.css", HTTP_ANY, [](AsyncWebServerRequest *request){
  //   AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/template/css/side-menu.css.gz", "text/css");
  //   response->addHeader("Content-Encoding", "gzip");
  //   request->send(response);
  // });

  // URL для файла ui.js:
  // server.on("/js/ui.js", HTTP_ANY, [](AsyncWebServerRequest *request){
  //   AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/template/js/ui.js.gz", "application/javascript");
  //   response->addHeader("Content-Encoding", "gzip");
  //   request->send(response);
  // });

  server.on("/js/app.js", HTTP_ANY, [](AsyncWebServerRequest *request){   
    request->send(SPIFFS, "/template/js/app.js", "application/javascript");
  });
 
  // URL для переключения GPIO-контакта на «HIGH»:
  // server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
  //   digitalWrite(LED_BUILTIN, HIGH);    
  //   request->send(SPIFFS, "/template/index.html", String(), false, processor);
  // });
 
  // URL для переключения GPIO-контакта на «LOW»:
  // server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
  //   digitalWrite(LED_BUILTIN, LOW);    
  //   request->send(SPIFFS, "/template/index.html", String(), false, processor);
  // });

  server.on("/post", HTTP_ANY, [this](AsyncWebServerRequest *request) {
    uint8_t params = request->params();
    AsyncWebParameter *param;
    boolean processing = false;
    unsigned long interval = millis();

    for (uint8_t i = 0; i < params; i++) {
      param = request->getParam(i);

      if (param->name().indexOf("BTN_") != -1) {
        btnui = param->name().substring(4, param->name().length());
        processing = true;
      } else {
        var(param->name(), param->value());
        conf_as();
      }
    }

    // if (processing) {
    //   for () {

    //   }
    // }
    
    request->send(200, "text/plain", buf);
  });

  server.on("/load", HTTP_ANY, [this](AsyncWebServerRequest *request) { 
    processor();
    request->send(200, "text/plain", buf);
    buf = "";
    Serial.println("ECHO RAM: " + String(ESP.getFreeHeap()));
  });

  // server.onNotFound(server.send(404, "text/plain", "Not found"););
 
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