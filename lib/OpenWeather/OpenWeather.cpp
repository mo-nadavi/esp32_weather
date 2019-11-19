// ESP32 libraries: https://github.com/espressif/arduino-esp32/tree/master/libraries

#include "OpenWeather.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

// construct
OpenWeather::OpenWeather(char* apikey)
{
    _api_key = apikey;
    _url = "http://api.openweathermap.org/data/2.5/";
}

// public methods

void OpenWeather::set_language(char* language)
{
    // например: ru, en ...
    _option.lang = language;
}

void OpenWeather::set_units(char* units)
{
    // допустимые значения: imperial, metric
    _option.units = units;
}

void OpenWeather::set_q(char* q)
{
    // q={city name}
    // q={city name},{country code}
    _option.q = q;
}

void OpenWeather::set_id(unsigned int id)
{
    _option.id = id;
}

void OpenWeather::set_zip(char* zip)
{
    // zip={zip code},{country code}
    _option.zip = zip;
}

void OpenWeather::set_coordinates(float lat, float lon)
{
    // lat={lat}&lon={lon}
    _option.lat = lat;
    _option.lon = lon;
}

bool OpenWeather::current()
{
    request("weather");

    return parse_data();
}

bool OpenWeather::forecast()
{
    request("forecast/hourly");

    return parse_data();
}

bool OpenWeather::forecast_daily()
{
    request("forecast/daily");

    return parse_data();
}

String OpenWeather::get_error()
{
    return _error;
}

// private methods

void OpenWeather::build_query_params()
{
    _query_option = "";
    _query_option += _option.lang ? "&lang=" + String(_option.lang) : "";
    _query_option += _option.units ? "&units=" + String(_option.units) : "";
    _query_option += _option.q ? "&q=" + String(_option.q) : "";
    _query_option += _option.id ? "&id=" + String(_option.id) : "";
    _query_option += _option.zip ? "&zip=" + String(_option.zip) : "";
    _query_option += _option.lat ? "&lat=" + String(_option.lat, 6) : "";
    _query_option += _option.lon ? "&lon=" + String(_option.lon, 6) : "";
    _query_option += _api_key ? "&appid=" + String(_api_key) : "";

    _query_option = "?" + _query_option.substring(1);
}

void OpenWeather::request(String action)
{
    build_query_params();

    HTTPClient http;

    // configure traged server and url
    //http.begin("https://***", ca); //HTTPS
    http.begin(_url + action + _query_option);
    // start connection and send HTTP header
    int http_code = http.GET();

    // httpCode will be negative on error
    if (http_code > 0) {
        // file found at server
        if (http_code == HTTP_CODE_OK) {
            _data = http.getString();
        } else {
            _error = "File not found at server";
        }
    } else {
        _error = "Error on HTTP request";
    }

    http.end();
}

bool OpenWeather::parse_data()
{
    if (_error.length()) {
        return false;
    }

    // DynamicJsonBuffer jsonBuffer;
    // JsonObject& data = jsonBuffer.parseObject(_data);
    DynamicJsonDocument data(2000);
    DeserializationError error = deserializeJson(data, _data);

    if (error) {
        _error = "Json parsing failed!";
        Serial.println(error.c_str());

        return false;
    }

    // if (_http_code != HTTP_CODE_OK) {
    //     _error = data["message"];
    // }

    // Serial.println(_data);
    // Serial.println(_url + "weather" + _query_option);
    // Serial.println(error.c_str());

    // int cod = data["cod"];

    weather.weather_id       = data["weather"][0]["id"];
    weather.weather_main     = data["weather"][0]["main"];
    weather.weather_descript = data["weather"][0]["description"];
    weather.weather_icon     = data["weather"][0]["icon"];
    weather.temp       = data["main"]["temp"];
    weather.temp_min   = data["main"]["temp_min"];
    weather.temp_max   = data["main"]["temp_max"];
    weather.humidity   = data["main"]["humidity"];
    weather.pressure   = data["main"]["pressure"];
    weather.sea_level  = data["main"]["sea_level"];
    weather.grnd_level = data["main"]["grnd_level"];
    weather.wind_speed = data["wind"]["speed"];
    weather.wind_deg   = data["wind"]["deg"];
    weather.clouds     = data["clouds"]["all"];
    weather.rain_1h    = data["rain"]["1h"];
    weather.rain_3h    = data["rain"]["3h"];
    weather.snow_1h    = data["snow"]["1h"];
    weather.snow_3h    = data["snow"]["3h"];
    weather.visibility = data["visibility"];
    weather.sunrise    = data["sys"]["sunrise"];
    weather.sunset     = data["sys"]["sunset"];
    weather.dt         = data["dt"];

    _data = "";

    return true;
}