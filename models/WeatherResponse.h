#ifndef WEATHERRESPONSE_H
#define WEATHERRESPONSE_H

#include <QVector>
#include <QString>
#include "City.h"
#include "models/WeatherObject.h"

struct WeatherResponse {
    QVector<Weather> weatherList;
    City city;

    QString toString() const {
        QString string;
        string += city.toString();
        for (int i = 0; i < weatherList.size(); i++) {
            string += weatherList.at(i).toString();
        }

        return string;
    }
};

#endif // WEATHERRESPONSE_H
