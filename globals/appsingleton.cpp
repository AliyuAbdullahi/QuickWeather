#include "globals/appsingleton.h"

AppSingleton::AppSingleton(){}

AppSingleton &AppSingleton::getInstance()
{
    static AppSingleton instance;
    return instance;
}

QString AppSingleton::weatherUrlPath(const QString &place)
{
    return urlBuilder.buildWeatherApiUrl(place);
}

