#ifndef APPSINGLETON_H
#define APPSINGLETON_H

#include "repository/weatherrepository.h"
#include "globals/UrlBuilder.h"
#include "relays/publishrelay.h"


class AppSingleton final
{
private:
    AppSingleton();
    WeatherSearchUrlBuilder urlBuilder;

public:
    static AppSingleton& getInstance();
    WeatherRepository repository;
    QString weatherUrlPath(QString const &place);
    PublishRelay relay;

    AppSingleton(AppSingleton &copy) = delete;
    void operator=(AppSingleton const &other) = delete;
};

#endif // APPSINGLETON_H
