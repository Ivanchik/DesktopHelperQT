#ifndef WEATHERDATA_H
#define WEATHERDATA_H

//#define USE_READ_ELEMENT_TEXT 1

#include <QXmlStreamReader>
#include <QMap>
#include <QDebug>

class WeatherData
{
public:
    WeatherData(QString path);
    ~WeatherData();

    void read();

    int GetTemperature();
    int GetPressure();
    int GetWindSpeed();

private:
    void processRates();
    void processRate();
    QString readNextText();
    QString errorString();

    QString _filname;
    QXmlStreamReader *xml;

    int temperature;
    int pressure;
    int wind_speed;
};

#endif // WEATHERDATA_H
