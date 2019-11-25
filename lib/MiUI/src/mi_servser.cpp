#include "mi_server.h"

AsyncWebServer server(80);

// Меняем заглушку на текущее состояние светодиода:
String processor(const String& var)
{
  // Создаем переменную для хранения состояния светодиода:
  String ledState;

  if(var == "STATE") {
    if(digitalRead(LED_BUILTIN)) {
      ledState = "ON";
    } else {
      ledState = "OFF";
    }

    Serial.print(ledState);

    return ledState;
  }
  
  return String();
}

void MiServer::run()
{
  // Инициализируем SPIFFS:
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
                // "При монтировании SPIFFS произошла ошибка"
    return;
  }

  // URL для корневой страницы веб-сервера:
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/favicon.ico", "image/x-icon", false);
  });

  // URL для файла «style.css»:
  server.on("/pure-min.css", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/pure-min.css.gz", "text/css");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // URL для файла «style.css»:
  server.on("/grids-responsive-min.css", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/grids-responsive-min.css.gz", "text/css");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // URL для файла «style.css»:
  server.on("/side-menu.css", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/side-menu.css.gz", "text/css");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // URL для файла ui.js:
  server.on("/ui.js", HTTP_ANY, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/ui.js.gz", "application/javascript");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
 
  // URL для переключения GPIO-контакта на «HIGH»:
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_BUILTIN, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
 
  // URL для переключения GPIO-контакта на «LOW»:
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_BUILTIN, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
 
  // Запускаем сервер:
  server.begin();
}