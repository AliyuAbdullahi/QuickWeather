#include "weathersummarypresenter.h"

WeatherSummaryPresenter::WeatherSummaryPresenter(WeatherSummaryView &view) : weatherSummaryView(&view)
{
    AppSingleton::getInstance().relay.subscribe(*this);
    QString place = getSavedPlace();
    if (!place.isEmpty()) {
        requestWeatherDataForPlace(place);
    }
}

/**
 * Smart Pointers isn't used here because Qt favor raw pointers on UI
 * <a href="response for why https://stackoverflow.com/questions/34433435/why-dont-the-official-qt-examples-and-tutorials-use-smart-pointers">
 * See this Stack Overflow response for details
 * </a>
 */
WeatherSummaryPresenter::~WeatherSummaryPresenter()
{
    Logger::debug("Cleanup for presenter...");
    if (weatherSummaryView) {
        weatherSummaryView = nullptr;
    }
}

void WeatherSummaryPresenter::onItemSelected(int position)
{
    auto data = AppSingleton::getInstance().repository.getSavedData();
    weatherSummaryView->showToday(data.weatherList[position]);
}

void WeatherSummaryPresenter::requestWeatherDataForPlace(const QString &place)
{
    AppSingleton::getInstance().repository.requestWeatherData(place);
    saveSearchedPlace(place);
}

void WeatherSummaryPresenter::saveSearchedPlace(const QString &placeName)
{
    std::string utf8_text = placeName.toUtf8().constData();
    std::ofstream stream("place.txt");
    stream << utf8_text;
    stream.close();
}

QString WeatherSummaryPresenter::getSavedPlace()
{
    std::mutex mutex;
    mutex.lock();
    auto result = std::async(std::launch::async, [=]{
        std::string place;
        std::ifstream stream("place.txt");
        if (stream.is_open())  {
            stream >> place;
            stream.close();
        } else {
            Logger::debug("File Not saved");
        }
        return place;
    });
    mutex.unlock();

    return QString::fromUtf8(result.get().c_str());
}

void WeatherSummaryPresenter::accept(const WeatherResponse &data)
{
    weatherSummaryView->hideLoadingMessage();
    weatherSummaryView->showCityInfo(data.city);
    weatherSummaryView->showWeathreLIst(data.weatherList);
}
