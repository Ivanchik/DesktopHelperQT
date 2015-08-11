#ifndef WEATHERDATA_H
#define WEATHERDATA_H

//#define USE_READ_ELEMENT_TEXT 1

#include <QXmlStreamReader>
#include <QMap>
#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

class WeatherData : public QObject
{
    Q_OBJECT
public:
    WeatherData(QString path);
    ~WeatherData();

    void read();

    int GetTemperature();
    int GetPressure();
    int GetWindSpeed();

    void Test();
public slots:

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
