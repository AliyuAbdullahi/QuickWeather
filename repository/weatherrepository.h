#ifndef WEATHERREPOSITORY_H
#define WEATHERREPOSITORY_H

#include "repository/IRepository.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "parser/jsonobjectparser.h"
#include "models/WeatherResponse.h"
#include "relays/publishrelay.h"
#include <iostream>

class WeatherRepository : public QObject, public IRepository
{
public:
    WeatherRepository();
    ~WeatherRepository();

public slots:
    void onDataObtained(QJsonObject data);
    void establishConnection();
    WeatherResponse getSavedData() const;

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkRequest request;
private:
    WeatherResponse response;

public:
    void requestWeatherData(QString place);
};

#endif // WEATHERREPOSITORY_H
