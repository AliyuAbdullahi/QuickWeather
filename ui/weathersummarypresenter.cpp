#include "weathersummarypresenter.h"

WeatherSummaryPresenter::WeatherSummaryPresenter(WeatherSummaryView &view) : weatherSummaryView(&view)
{

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
    weatherSummaryView->showToday(weatherList[position]);
}

void WeatherSummaryPresenter::requestWeatherDataForPlace(const QString &place)
{
    weatherSummaryView->makeRequest(WeatherSearchUrlBuilder::buildWeatherApiUrl(place));
}

void WeatherSummaryPresenter::saveSearchedPlace(const QString &placeName)
{
    QFile file(SEARCHED_PLACE_TEXT_FILE);
    if (file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        QTextStream stream(&file);
        stream << placeName;
        file.close();
    } else {
        showFileFailedToLoadLogMessage();
    }
}

void WeatherSummaryPresenter::showFileFailedToLoadLogMessage() {
    QString errorKey = "FILE_OPEN";
    QString errorMessage = "Failed to openFile " + SEARCHED_PLACE_TEXT_FILE;
    Logger::debug(errorKey, errorMessage);
}

void WeatherSummaryPresenter::processData(QJsonObject &data)
{
    auto result = JsonObjectParser::parseWeatherObject(data);
    weatherSummaryView->showWeathreLIst(result.weatherList);
    weatherSummaryView->showToday(result.weatherList[0]);
    weatherSummaryView->showCityInfo(result.city);
    weatherList = result.weatherList;
}

QString WeatherSummaryPresenter::getSavedPlace()
{
    QString place;

    QFile file(SEARCHED_PLACE_TEXT_FILE);

    if (file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QTextStream stream(&file);
        place = stream.readLine();
        file.close();
    } else {
        showFileFailedToLoadLogMessage();
    }

    return place;
}
