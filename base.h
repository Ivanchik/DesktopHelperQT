#ifndef BASE_H
#define BASE_H

#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QMessageBox>
#include <QHostInfo>

#include "mainwindow.h"

class MainWindow;

class Base
{
private:
    QByteArray ipAddress;
    MainWindow* view;

public:
    Base(MainWindow* view);
    QString getIP();
};

#endif // BASE_H
