#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wd = new WeatherData("http://export.yandex.ru/weather-ng/forecasts/27595.xml");

    ui->temperatureValueLabel->setText(static_cast<QString>(wd->GetTemperature()));
    ui->pressureValueLabel->setText(static_cast<QString>(wd->GetPressure()));
    ui->windValueLabel->setText(static_cast<QString>(wd->GetWindSpeed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
