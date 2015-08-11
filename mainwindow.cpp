#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wd = new WeatherData();

    qDebug() << "t: " << (wd->GetTemperature());
    ui->temperatureValueLabel->setText(QString::number(wd->GetTemperature()) + "ºC");
    ui->pressureValueLabel->setText(QString::number(wd->GetPressure()) + "mm");
    ui->windValueLabel->setText(QString::number(wd->GetWindSpeed()) + "m/s");


    baseWindow = new Base(this);

    //Set IP Address to form
    SetIpAddress();

    //Set valute values


}

void MainWindow::SetIpAddress()
{
    QString bufferIP = baseWindow->getIP();
    if ( bufferIP!= NULL)
        ui->ipAddressValue->setText(bufferIP);
}

MainWindow::~MainWindow()
{
    delete ui;
}
