#ifndef WEATHERDATA_H
#define WEATHERDATA_H

//XMLStreamReader for read xml file
#include <QXmlStreamReader>

//Instruments for access to the internet
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>

//Time to get current temperature
#include <QTime>

class WeatherData : public QObject
{
    Q_OBJECT
public:
    WeatherData();
    ~WeatherData();

    //functions for getting data from api
    int GetTemperature();
    int GetPressure();
    int GetWindSpeed();

private:
    //function for read and parse data from api xml
    void read();

    //functions for finding need data
    void processForecast();
    void processFact();
    void processDay();
    void processHour();

    //parse XML
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
