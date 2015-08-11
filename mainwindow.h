#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weatherdata.h"

#include "base.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class Base;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void TryGetValuteData();
    void UpdateAllData();
    void TryGetWeatherData();

private:
    Ui::MainWindow *ui;
    WeatherData *weatherData;
    Base *baseWindow;
    void SetIpAddress();
    QTimer *timer;

};

#endif // MAINWINDOW_H
