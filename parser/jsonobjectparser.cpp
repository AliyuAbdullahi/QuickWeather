#include "parser/jsonobjectparser.h"

JsonObjectParser::JsonObjectParser()
{

}

WeatherResponse JsonObjectParser::parseWeatherObject(const QJsonObject &object)
{
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
