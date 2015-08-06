#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weatherdata.h"

#include "base.h"

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

private:
    Ui::MainWindow *ui;
    WeatherData *wd;
    Base *baseWindow;
    void SetIpAddress();
};

#endif // MAINWINDOW_H
