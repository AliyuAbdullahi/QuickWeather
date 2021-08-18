#ifndef JSONOBJECTPARSER_H
#define JSONOBJECTPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "models/City.h"
#include "models/WeatherObject.h"
#include "models/WeatherResponse.h"

class JsonObjectParser
{
public:
    JsonObjectParser();
public:
    WeatherResponse parseWeatherObject(QJsonObject const &object);
};

#endif // JSONOBJECTPARSER_H
