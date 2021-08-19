#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include <QListWidgetItem>
#include <iostream>
#include <thread>
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

    // WeatherSummaryView interface
public:
    void showWeathreLIst(const QVector<Weather> &weatherList) override;
    void showToday(const Weather &weather) override;
    void showCityInfo(const City &city) override;
    void showLoadingMessage(QString const &message) override;
    void hideLoadingMessage() override;

private slots:
    void on_placeSearch_returnPressed();
    void on_listItem_clicked(QListWidgetItem* item);
};
#endif // MAINWINDOW_H
