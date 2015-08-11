#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QDebug>

#include <QXmlStreamReader>

#include <QMap>
#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTime>


class WeatherData : public QObject
{
    Q_OBJECT
public:
    WeatherData();
    ~WeatherData();

    void read();

    QString GetTemperature();
    QString GetPressure();
    QString GetWindSpeed();
    void InitUpdateWeatherData();
    void Test();
signals:
    void trySendWeatherData();
private:
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
