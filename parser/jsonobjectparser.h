#ifndef JSONOBJECTPARSER_H
#define JSONOBJECTPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "models/City.h"
#include "models/WeatherObject.h"
#include "models/WeatherResponse.h"

struct JsonObjectParser
{

    static WeatherResponse parseWeatherObject(QJsonObject const &object) {
        QVector<Weather> weatherList;
        City city = City::fromJson(object);
        QJsonValue arrayValue = object.value("list");
        QJsonArray responseArray = arrayValue.toArray();

        for (const QJsonValue &v : responseArray)
        {
            QJsonObject object = v.toObject();
            Weather weather = Weather::fromJson(object);
            weatherList.emplace_back(weather);
        }

        WeatherResponse response;
        response.city = std::move(city);
        response.weatherList = std::move(weatherList);

        return response;
    }
};

#endif // JSONOBJECTPARSER_H
