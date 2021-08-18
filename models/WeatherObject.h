#ifndef WEATHEROBJECT_H
#define WEATHEROBJECT_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <globals/Logger.h>

struct Temprature {
    double dayTemp;
    double eveningTemp;
    double morningTemp;
    double nightTemp;
    double minTemp;
    double maxTemp;

    static Temprature fromJson(QJsonObject &object) {
        Logger::debug(object);
        Temprature temperature;
        QJsonObject tempObject = object.value("temp").toObject();
        QJsonValue dayTemp = tempObject.value("day");
        QJsonValue nightTemp = tempObject.value("night");
        QJsonValue morningTemp = tempObject.value("morn");
        QJsonValue eveningTemp = tempObject.value("eve");
        QJsonValue minTemp = tempObject.value("min");
        QJsonValue max = tempObject.value("max");

        temperature.dayTemp = dayTemp.toVariant().toDouble();
        temperature.eveningTemp = eveningTemp.toVariant().toDouble();
        temperature.morningTemp = morningTemp.toVariant().toDouble();
        temperature.nightTemp = nightTemp.toVariant().toDouble();
        temperature.minTemp = minTemp.toVariant().toDouble();
        temperature.maxTemp = max.toVariant().toDouble();

        return temperature;
    }

    QString toString() const {
        return "Daytemp: " + QString::number(dayTemp)
                + ", EveningTemp: " + QString::number(eveningTemp)
                + ", MorningTemp: " + QString::number(morningTemp)
                + ", NightTemp: " + QString::number(nightTemp) + ", MinTemp:" + QString::number(minTemp) + ", MaxTemp: " + QString::number(maxTemp);
    }
};

struct WeatherContent {
    QString description;
    QString icon;
    QString main;

    static WeatherContent fromJson(QJsonObject &object) {
        WeatherContent content;
        QJsonValue weatherArrayObject = object.value("weather");
        QJsonArray weatherArray = weatherArrayObject.toArray();

        if (weatherArray.size() > 0) {
            QJsonObject weatherObject = weatherArray.at(0).toObject();
            QJsonValue description = weatherObject.value("description");
            QJsonValue icon = weatherObject.value("icon");
            QJsonValue main = weatherObject.value("main");

            content. description = description.toString();
            content.icon = icon.toString();
            content. main = main.toString();
        }

        return content;
    }

    QString toString() const {
        return "Description: " + description + ", Icon: " + icon + ", Main: " + main;
    }
};

struct Weather {
    long long date;
    int humidity;
    int pressure;
    double rain;
    long long sunRiseAt;
    long long sunSetAt;

    Temprature temprature;
    WeatherContent content;

    static Weather fromJson(QJsonObject &object) {
        Weather weather;

        QJsonValue sunRiseAt = object.value("sunrise");
        QJsonValue sunSetAt = object.value("sunset");
        QJsonValue humidity = object.value("humidity");
        QJsonValue pressure = object.value("pressure");
        QJsonValue date = object.value("dt");
        QJsonValue rain = object.value("rain");

        weather.date = date.toVariant().toLongLong();
        weather.humidity = humidity.toVariant().toInt();
        weather.pressure = pressure.toVariant().toInt();
        weather.rain = rain.toVariant().toDouble();
        weather.sunRiseAt = sunRiseAt.toVariant().toLongLong();
        weather.sunSetAt = sunSetAt.toVariant().toLongLong();
        weather.temprature = Temprature::fromJson(object);
        weather.content = WeatherContent::fromJson(object);

        return weather;
    }

    QString toString() const {
        return "{Date: " + QString::number(date) + ", Humidity: " + QString::number(humidity)
                + ", Pressure: " + QString::number(pressure) + ", Rain: " + QString::number(rain)
                + ", SunRise: " + QString::number(sunRiseAt) + ", Sunset: " + QString::number(sunSetAt)
                + ", Content: " + content.toString()
                + ", Temperature{ " + temprature.toString() + "}"
                + "}";
    }
};

#endif // WEATHEROBJECT_H
