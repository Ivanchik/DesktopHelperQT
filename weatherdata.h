#ifndef WEATHERDATA_H
#define WEATHERDATA_H

//XMLStreamReader for read xml file
#include <QXmlStreamReader>

//Instruments for access to the internet
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>

//Time to get current temperature
#include <QMap>
#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QTime>


class WeatherData : public QObject
{
    Q_OBJECT


public:
    WeatherData();
    ~WeatherData();

    QString GetTemperature();
    QString GetPressure();
    QString GetWindSpeed();
    void InitUpdateWeatherData();
    void Test();
signals:
    void trySendWeatherData();
private:
    //function for read and parse data from api xml
    void read();

    //functions for finding need data
    void processForecast();
    void processFact();
    void processDay();
    void processHour();

    QString readNextText();
    QString errorString();
    int current_hour;

    QString _filname;
    QXmlStreamReader xmlReader;

    QString temperature = "No Data";
    QString pressure = "No Data";
    QString wind_speed = "No Data";
};

#endif // WEATHERDATA_H
