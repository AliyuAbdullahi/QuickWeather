#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    presenter = new WeatherSummaryPresenter(*this);
    ui->setupUi(this);
    ui->weatherList->setFlow(QListView::LeftToRight);
    ui->weatherList->setItemAlignment(Qt::AlignCenter);
    connect(ui->weatherList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_listItem_clicked(QListWidgetItem*)));
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
    if (!weatherList.isEmpty()) {
        showToday(weatherList.at(0));
        ui->weatherList->clear();
        for (int i = 0; i < weatherList.size(); i++)
        {
            Weather weather = weatherList.at(i);
            QListWidgetItem *item = new QListWidgetItem(ui->weatherList);
            item->setTextAlignment(Qt::AlignCenter);
            item->setText(AppUtil::getSummarizedWeatherInfo(weather));

            ui->weatherList->setStyleSheet(
              "QListWidget::item {border-style: solid; border-width:4px;selection-color: green;border-color:black; background-color:grey}"
            );

            ui->weatherList->addItem(item);
        }
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

void MainWindow::on_placeSearch_returnPressed()
{
    showLoadingMessage("🔎Searching for " + ui->placeSearch->text() + "...");
    presenter->requestWeatherDataForPlace(QString(ui->placeSearch->text()));
}

void MainWindow::on_listItem_clicked(QListWidgetItem *item)
{
    auto position = ui->weatherList->row(item);
    presenter->onItemSelected(position);
}

