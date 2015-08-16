#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);

    weatherData = new WeatherData();
    baseWindow = new Base(this);

    //Set IP Address to form
    SetIpAddress();

    //connect weather sig/slot
    TryGetWeatherData();
    connect(weatherData, SIGNAL(trySendWeatherData()), this, SLOT(TryGetWeatherData()));

    //connect valute sig/slot
    connect(baseWindow,SIGNAL(tryGetValuteData()),this,SLOT(TryGetValuteData()));

    //init timer
    timer = new QTimer(this);
    timer->setInterval(15000);
    timer->start();
    connect(timer,SIGNAL(timeout()), this, SLOT(UpdateAllData()));

    //install filter
    this->installEventFilter(this);
}

void MainWindow::SetIpAddress()
{
    QString bufferIP = baseWindow->getIP();
    if ( bufferIP != NULL)
        ui->ipAddressValue->setText(bufferIP);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TryGetValuteData()
{
    //Set valute values
    try
    {
        ui->dollarValueLabel->setText(baseWindow->getDollarValue());
        ui->euroValueLabel->setText(baseWindow->getEuroValue());
    }
    catch (...)
    {
        qWarning() << "Something wrong with getting valute";
    }
}

void MainWindow::UpdateAllData()
{
    try
    {
        SetIpAddress();
        weatherData->InitUpdateWeatherData();
        baseWindow->InitUpdateValuteData();

    }
    catch (...)
    {
        qWarning() << "Something wrong with update data";
    }

}

void MainWindow::TryGetWeatherData()
{
    ui->temperatureValueLabel->setText(weatherData->GetTemperature() + "ºC");
    ui->pressureValueLabel->setText(weatherData->GetPressure() + "mm");
    ui->windValueLabel->setText(weatherData->GetWindSpeed() + "m/s");

}

void MainWindow::OnTrayActivate(QSystemTrayIcon::ActivationReason active)
{
    if (active == QSystemTrayIcon::DoubleClick)
    {
        this->show();
        //this->showNormal();

    }

}

// Check for pressed keys
bool MainWindow::eventFilter(QObject * obj, QEvent * event)
{
    if(event->type()==QEvent::KeyPress) {

        pressedKeys += ((QKeyEvent*)event)->key();

        if ( pressedKeys.contains(Qt::Key_Escape))
            this->hide();

        if( pressedKeys.contains(Qt::Key_Escape) &&
                pressedKeys.contains(Qt::Key_Shift) )
            this->close();

    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }


    return false;
}
