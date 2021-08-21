#ifndef WEATHERSUMMARYPRESENTER_H
#define WEATHERSUMMARYPRESENTER_H

#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QJsonObject>
#include "models/WeatherResponse.h"
#include "globals/UrlBuilder.h"
#include "globals/Logger.h"
#include "parser/jsonobjectparser.h"
#include "ui/WeatherSummaryView.h"

class WeatherSummaryPresenter
{
public:
    WeatherSummaryPresenter(WeatherSummaryView &view);
    ~ WeatherSummaryPresenter();

    void requestWeatherDataForPlace(QString const &place);
    void onItemSelected(int position);
    void saveSearchedPlace(QString const &placeName);
    void showFileFailedToLoadLogMessage();
    void processData(QJsonObject &data);
    QString getSavedPlace();

private:
    WeatherSummaryView *weatherSummaryView;
    QVector<Weather> weatherList;
};

#endif // WEATHERSUMMARYPRESENTER_H
