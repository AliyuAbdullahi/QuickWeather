#ifndef URLBUILDER_H
#define URLBUILDER_H
#include <QString>
#include <globals/Constants.h>

struct WeatherSearchUrlBuilder {

    static QString buildWeatherApiUrl(QString const &place) {
        return "https://api.openweathermap.org/data/2.5/forecast/daily?q=" + place + "&cnt=7&appid=" + API_KEY;
    }
};

#endif // URLBUILDER_H

