/**
 * Заголовочный файл содержит характеристики библиотеки, 
 * т.е. список всего что содержится в ней. 
 */

// проверка, что библиотека еще не подключена
#ifndef OPENWEATHER_H // если библиотека не подключена
#define OPENWEATHER_H // тогда подключаем ее

#include <Arduino.h>

/**
 * Заголовочный файл содержит класс, в котором объявляются функций и используемые переменные
 */
class OpenWeather
{
  public:
    // construct
    OpenWeather();
    // properties
    String url;
    struct option_struct {
      String api_key;
      String lang;
      String units;
      String q;
      unsigned int id;
      String zip;
      float lat;
      float lon;
      String appid;
    } option;
    struct weather_structure {
      unsigned int weather_id;        // Идентификатор погодного условия
      const char* weather_main;       // Группа параметров погоды (дождь, снег, экстрим и т.д.)
      const char* weather_icon;       // Идентификатор значка погоды
      const char* weather_descript;   // Погодные условия в группе
      float temp;         // Температура
      float temp_min;     // Минимальная температура на данный момент
      float temp_max;     // Максимальная температура на данный момент
      float pressure;     // Атмосферное давление (на уровне моря, если нет данных sea_level или grnd_level), гПа     
      byte  humidity;     // Влажность,%
      float sea_level;    // Атмосферное давление на уровне моря, гПа
      float grnd_level;   // Атмосферное давление на уровне земли, гПа
      float wind_speed;   // Скорость ветра. Единица измерения по умолчанию: метр/сек, metric: метр/сек, imperial: миль/час.
      float wind_deg;     // Направление ветра, град (метеорологическое)
      byte clouds;        // Облачность,%
      byte rain_1h;       // Объем дождя за последние 1 час, мм
      byte rain_3h;       // Объем дождя за последние 3 часа, мм
      byte snow_1h;       // Объем снега за последние 1 час, мм
      byte snow_3h;       // Объем снега за последние 3 часа, мм
      unsigned int visibility;    // Видимость, метр
      unsigned int sunrise;       // Время восхода, Unix, UTC
      unsigned int sunset;        // Время заката, Unix, UTC
      unsigned int dt;            // Время расчета данных, Unix, UTC
      const char* city;           // Название города
    } weather;
    // methods
    bool current();
    bool forecast();
    bool forecast_daily();
    String get_error();

  private:
    // properties
    String _query_option; 
    String _error;
    String _data;
    // methods
    void build_query_params();
    void request(String action);
    bool parse_data();
};
 
#endif