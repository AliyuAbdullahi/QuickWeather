#ifndef APPUTIL_H
#define APPUTIL_H

#include "models/WeatherObject.h"
#include "globals/Logger.h"

struct AppUtil
{
    static double kelvinToCelcius(double temp)
    {
        return temp - 273.15;
    }

    static double kelvinToFahrenheit(double temp)
    {
        return (temp - 273.15) * 9/5 + 32;
    }

    static QString getWeatherEmoji (const Weather &weather) {
        QString main  = weather.content.main;
        QString emoji = "";
        QString filter = main.toLower();

        if (filter.contains("rain")) {
            emoji = "🌧";
        } else if (filter.contains("thunder")) {
            emoji = "⛈";
        } else if (filter.contains("sun")) {
            emoji = "🌤";
        } else if (filter.contains("cloud")) {
            emoji = "🌥";
        } else if (filter.contains("snow")) {
            emoji = "🌨";
        } else {
            emoji = "🌥";
        }

        return emoji;
    }

    static QString getFormattedWeatherDate(Weather &weather) {
         auto time = QDateTime::fromSecsSinceEpoch(weather.date);
         auto currentMonth = months()[time.date().month() - 1];
         auto currentDay = time.date().dayOfWeek();
         return days()[currentDay - 1] + ", " + currentMonth + " " + QString::number(time.date().day());
    }

    static QString getSummarizedWeatherInfo(Weather &weather) {
        return getFormattedWeatherDate(weather) + " " + getWeatherEmoji(weather);
    }

private:
    static QStringList months() {
        return {"Jan", "Feb", "Mar", "Apr", "May", "June", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    }
    static QStringList days() {
        return {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    }
};

#endif // APPUTIL_H
