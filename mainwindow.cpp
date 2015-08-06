#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    baseWindow = new Base(this);

    //Set IP Address to form
    SetIpAddress();

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
