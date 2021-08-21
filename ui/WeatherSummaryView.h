#ifndef WEATHERSUMMARYVIEW_H
#define WEATHERSUMMARYVIEW_H

#include <QVector>

#include "models/WeatherObject.h"
#include "models/City.h"
#include <QString>

class WeatherSummaryView {
public:
    virtual void showWeathreLIst(QVector<Weather> const &weatherList) = 0;
    virtual void showToday(Weather const &weather) = 0;
    virtual void showCityInfo(City const &city) = 0;
    virtual void showLoadingMessage(QString const &message) = 0;
    virtual void makeRequest(QString const &path) = 0;
    virtual void hideLoadingMessage() = 0;
};

#endif // WEATHERSUMMARYVIEW_H
