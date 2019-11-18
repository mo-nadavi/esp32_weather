# JeeUI 2

## Dependencing

```
    ESPAsyncTCP
    AsyncTCP
    ESPAsyncWebServer
    ArduinoJson
    AsyncMqttClient
```

Подключаем библиотеку
```
    #include "JeeUI2.h"
```

Create objeck class
```
    jeeui2 jee;
```

Таймаут, если в течении указанного времени не смогли подключится к WiFi будет запущена точка доступа
Иначе все время будет поисходить попытка подключения к точке доступа
```
    jee.ap(10000);
```

Подключение светодиода
```
    jee.led(2, true);
```
