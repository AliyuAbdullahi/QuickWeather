#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QListWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>

#include <iostream>
#include <thread>
#include "globals/UrlBuilder.h"
#include "ui/NetworkReplyDeleteDelegate.h"
#include "ui/WeatherSummaryView.h"
#include "ui/weathersummarypresenter.h"
#include "globals/apputil.h"
#include "globals/Constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public WeatherSummaryView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WeatherSummaryPresenter* presenter;
    QTimer *qTimer;
    QNetworkAccessManager* networkManager;
    QNetworkRequest request;


    // WeatherSummaryView interface
public:
    void showWeathreLIst(const QVector<Weather> &weatherList) override;
    void showToday(const Weather &weather) override;
    void showCityInfo(const City &city) override;
    void showLoadingMessage(QString const &message) override;
    void hideLoadingMessage() override;
    void makeRequest(const QString &path) override;

private slots:
    void onSelect();
    void onShowTime();
    void on_placeSearch_returnPressed();
    void dataObtained(QNetworkReply* reply);
};
#endif // MAINWINDOW_H
