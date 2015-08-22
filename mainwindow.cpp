#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);
    ui->setupUi(this);

    // Instances
    weatherData = new WeatherData();
    baseWindow = new Base(this);

    //Set First Position
    SetLoadPosition();

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

    //install filter for key press
    this->installEventFilter(this);

    //Push default cities to comboBox
    SetDefaultCitiesComboBox();
}

void MainWindow::SetIpAddress()
{
    QString bufferIP = baseWindow->getIP();
    if ( bufferIP != NULL)
        ui->ipAddressValue->setText(bufferIP);
}

void MainWindow::SetLoadPosition()
{
    int width = 50; // Just for people, who have start menu on left side.
    int height = 0;
    this->move(width, height);
}

void MainWindow::SetDefaultCitiesComboBox()
{
    ui->comboBox->addItem("Kazan");
    ui->comboBox->addItem("Magnitogorsk");
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
    ui->temperatureValueLabel->setText(weatherData->GetTemperature() + " ºC");
    ui->pressureValueLabel->setText(weatherData->GetPressure() + " mm");
    ui->windValueLabel->setText(weatherData->GetWindSpeed() + " m/s");

}

void MainWindow::OnTrayActivate(QSystemTrayIcon::ActivationReason active)
{
    if (active == QSystemTrayIcon::DoubleClick)
    {
        this->show();
        UpdateAllData();
    }
}

// Check for pressed keys
bool MainWindow::eventFilter(QObject * obj, QEvent * event)
{

    if(event->type()==QEvent::KeyPress) {

        pressedKeys += ((QKeyEvent*)event)->key();

        if( pressedKeys.contains(Qt::Key_Escape) &&
                pressedKeys.contains(Qt::Key_Shift) )
            this->close();

        if ( pressedKeys.contains(Qt::Key_Escape))
        {
            this->hide();
            pressedKeys.clear();
        }
    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys.clear();
    }

    return false;
}





// Drag and drop window on the screen

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        this->move(event->globalPos() + windowLocation);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        windowLocation = this->pos() - event->globalPos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        this->move(event->globalPos());
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
//    if (arg1 == "Kazan")

}
