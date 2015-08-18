#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weatherdata.h"

#include "base.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>

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
    void OnTrayActivate(QSystemTrayIcon::ActivationReason active);
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


private:
    Ui::MainWindow *ui;
    WeatherData *weatherData;
    Base *baseWindow;
    void SetIpAddress();
    void SetLoadPosition();
    QTimer *timer;
    QSet<int> pressedKeys;
    QPoint windowLocation;



};

#endif // MAINWINDOW_H
