#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QDebug>

#include <QXmlStreamReader>

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

    int GetTemperature();
    int GetPressure();
    int GetWindSpeed();

private:
    void processForecast();
    void processFact();
    void processDay();
    void processHour();
    void parseWeatherXML();
    QString readNextText();
    QString errorString();
    int current_hour;

    QString _filname;
    QXmlStreamReader xmlReader;

    int temperature;
    int pressure;
    int wind_speed;
};

#endif // WEATHERDATA_H
