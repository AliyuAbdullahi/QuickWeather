#ifndef URLBUILDER_H
#define URLBUILDER_H
#include <QString>

struct WeatherSearchUrlBuilder {

    QString buildWeatherApiUrl(QString const &place) {
        return "https://api.openweathermap.org/data/2.5/forecast/daily?q=" + place + "&cnt=7&appid=0f3f6fe168123fe341116010edc625c1";
    }
};

#endif // URLBUILDER_H
