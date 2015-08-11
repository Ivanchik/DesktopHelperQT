#ifndef BASE_H
#define BASE_H

#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QMessageBox>
#include <QHostInfo>
#include <QXmlStreamReader>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include "mainwindow.h"

class MainWindow;

class Base : public QObject
{
    Q_OBJECT
private:
    QByteArray ipAddress;
    MainWindow* view;

public:
    Base(MainWindow* view);
    QString getIP();
    void Test();
    QString dollarValue = "No data";
    QString euroValue = "No data";

    QString getDollarValue() const;
    void setDollarValue(const QString &value);

    QString getEuroValue() const;
    void setEuroValue(const QString &value);

signals:
    void tryGetValuteData();


public slots:
    void OnLoad(QNetworkReply *reply);
};

#endif // BASE_H
