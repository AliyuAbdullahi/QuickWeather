#ifndef WEATHERSUMMARYPRESENTER_H
#define WEATHERSUMMARYPRESENTER_H

#include <QString>
#include <future>
#include <thread>
#include <mutex>
#include <fstream>
#include <relays/publishrelay.h>
#include "ui/Isubscriber.h"
#include "models/WeatherResponse.h"
#include "globals/appsingleton.h"
#include "globals/Logger.h"
#include "ui/WeatherSummaryView.h"

class WeatherSummaryPresenter : public Isubscriber
{
public:
    WeatherSummaryPresenter(WeatherSummaryView &view);
    ~ WeatherSummaryPresenter();

    void requestWeatherDataForPlace(QString const &place);
    void onItemSelected(int position);
    void saveSearchedPlace(QString const &placeName);
    QString getSavedPlace();

private:
    WeatherSummaryView *weatherSummaryView;

    // Isubscriber interface
public:
    void accept(const WeatherResponse &data) override;
};

#endif // WEATHERSUMMARYPRESENTER_H
