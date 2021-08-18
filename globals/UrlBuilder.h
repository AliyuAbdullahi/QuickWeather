#ifndef URLBUILDER_H
#define URLBUILDER_H
#include <QString>

struct WeatherSearchUrlBuilder {

    QString buildWeatherApiUrl(QString const &place) {
        return "https://api.openweathermap.org/data/2.5/forecast/daily?q=" + place + "&cnt=7&appid=";
    }
};

#endif // URLBUILDER_H
