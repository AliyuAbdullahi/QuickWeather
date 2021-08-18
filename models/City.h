#ifndef CITY_H
#define CITY_H

#include <QJsonObject>
#include <QString>

struct City{
    QString country;
    long id;
    QString name;
    long population;
    int timezone;

    static City fromJson(const QJsonObject &object) {
        City city;

        QJsonObject cityObject = object.value("city").toObject();
        QJsonValue country = cityObject.value("country");
        QJsonValue id = cityObject.value("id");
        QJsonValue name = cityObject.value("name");
        QJsonValue populaton = cityObject.value("population");
        QJsonValue timeZone = cityObject.value("timezone");

        city.country = country.toString();
        city.id = id.toVariant().toLongLong();
        city.name = name.toString();
        city.population = populaton.toVariant().toInt();
        city.timezone = timeZone.toVariant().toLongLong();

        return city;
    }


    QString toString() const {
        return "Country: " + country
                + ", name: " + name
                + ", id " + QString::number(id)
                + ", Population " + QString::number(population)
                + ", timezone: " + QString::number(timezone);
    }
};

#endif // CITY_H
