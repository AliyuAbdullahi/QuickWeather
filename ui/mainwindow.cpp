#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    presenter = new WeatherSummaryPresenter(*this);
    qTimer = new QTimer(this);

    networkManager = new QNetworkAccessManager(this);

    ui->setupUi(this);
    ui->weatherList->setFlow(QListView::LeftToRight);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::dataObtained);
    connect(ui->weatherList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSelect()));
    connect(qTimer, SIGNAL(timeout()), this, SLOT(onShowTime()));
    qTimer->start(1000);
    QString place = presenter->getSavedPlace();
    if (!place.isEmpty())
    {
       presenter->requestWeatherDataForPlace(place);
    }
}

/**
 * Smart Pointers isn't used here because Qt favor raw pointers on UI
 * <a href="response for why https://stackoverflow.com/questions/34433435/why-dont-the-official-qt-examples-and-tutorials-use-smart-pointers">
 * See this Stack Overflow response for details
 * </a>
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete presenter;
}

void MainWindow::showWeathreLIst(const QVector<Weather> &weatherList)
{
    if (!weatherList.isEmpty())
    {
        showToday(weatherList.at(0));
        ui->weatherList->clear();
        for (int i = 0; i < weatherList.size(); i++)
        {
            Weather weather = weatherList.at(i);
            QListWidgetItem *item = new QListWidgetItem(ui->weatherList);
            item->setTextAlignment(Qt::AlignCenter);
            item->setText(AppUtil::getSummarizedWeatherInfo(weather));

            ui->weatherList->setStyleSheet(LIST_ITEM_BACKGROUND);

            ui->weatherList->addItem(item);
        }
    }
    else
    {
       ui->statusbar->showMessage(NO_WEATHER_LIST_FOUND);
    }
}

void MainWindow::showToday(const Weather &weather)
{
    ui->temperature->setText("<p>" + QString::number(AppUtil::kelvinToCelcius(((weather.temprature.maxTemp + weather.temprature.minTemp))/2), 'G', 2) + "<sup>oc</sup></p>" +"&nbsp;" + AppUtil::getWeatherEmoji(weather));
    ui->description->setText(weather.content.description);
    ui->morningTemp->setText("<p>Morning : " + QString::number(AppUtil::kelvinToCelcius(weather.temprature.morningTemp), 'G', 2) + " <sup>oc</sup></p>");
    ui->noonTemp->setText("<p>Noon : " + QString::number(AppUtil::kelvinToCelcius(weather.temprature.dayTemp), 'G', 2) + " <sup>oc</sup></p>");
    ui->nightTemp->setText("<p>Night : " + QString::number(AppUtil::kelvinToCelcius(weather.temprature.nightTemp), 'G', 2) + " <sup>oc</sup></p>");
    ui->humidity->setText("Humidity: " + QString::number(weather.humidity));
}

void MainWindow::showCityInfo(const City &city)
{
    ui->placeLabel->setText(city.name + ", " + city.country);
}

void MainWindow::showLoadingMessage(QString const &message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::hideLoadingMessage()
{
    ui->statusbar->showMessage("");
}

void MainWindow::makeRequest(const QString &path)
{
    request.setUrl(QUrl(path));
    networkManager->get(request);
}

void MainWindow::onSelect()
{
    auto currentItem = ui->weatherList->currentRow();
    presenter->onItemSelected(currentItem);
}

void MainWindow::onShowTime()
{
    QTime time = QTime::currentTime();
    QString timeText = time.toString("hh : mm : ss");
    ui->localTime->setText("⏰ " + timeText);
}


void MainWindow::on_placeSearch_returnPressed()
{
    showLoadingMessage("🔎Searching for " + ui->placeSearch->text() + "...");
    presenter->requestWeatherDataForPlace(QString(ui->placeSearch->text()));
}

void MainWindow::dataObtained(QNetworkReply *reply)
{
    std::unique_ptr<QNetworkReply, NetworkReplyDeleteDelegate> guard_reply(reply);
    if (reply->error())
    {
        QString errorMessage = reply->errorString();
        Logger::error(errorMessage);

        return;
    }

    QString answer = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject theObject = jsonResponse.object();
    presenter->processData(theObject);
    showLoadingMessage("");
}

