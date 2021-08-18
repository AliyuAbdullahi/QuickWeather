#include "repository/weatherrepository.h"
#include "globals/appsingleton.h"
#include "globals/Logger.h"

WeatherRepository::WeatherRepository()
{
    establishConnection();
}

WeatherRepository::~WeatherRepository()
{
    delete networkAccessManager;
}

void WeatherRepository::onDataObtained(QJsonObject data)
{
    JsonObjectParser parser;
    WeatherResponse response = parser.parseWeatherObject(data);
    this->response = response;
    AppSingleton::getInstance().relay.accept(response);
}

void WeatherRepository::establishConnection()
{
    networkAccessManager = new QNetworkAccessManager();

    QObject::connect(
        networkAccessManager,
        &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply
    )
    {
        if (reply->error())
        {
            QString errorMessage = reply->errorString();
            Logger::error(errorMessage);
            return;
        }

        QString answer = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
        QJsonObject theObject = jsonResponse.object();

        onDataObtained(theObject);
    }
    );
}

WeatherResponse WeatherRepository::getSavedData() const
{
    return response;
}

void WeatherRepository::requestWeatherData(QString place)
{
    request.setUrl(QUrl(AppSingleton::getInstance().weatherUrlPath(place)));
    networkAccessManager->get(request);
}
