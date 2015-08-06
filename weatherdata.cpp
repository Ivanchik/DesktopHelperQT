#include "weatherdata.h"

WeatherData::WeatherData(QString path)
{
    xml = new QXmlStreamReader(path);
    _filname = path;
    read();
}

WeatherData::~WeatherData()
{

}

void WeatherData::read()
{
    if (xml->readNextStartElement() && xml->name() == "forecast")
        processRates();

    if (xml->tokenType() == QXmlStreamReader::Invalid)
        xml->readNext();

    if (xml->hasError()) {
        xml->raiseError();
        qDebug() << errorString();
    }
}

int WeatherData::GetTemperature()
{
    return 0;
}

int WeatherData::GetPressure()
{
    return pressure;
}

int WeatherData::GetWindSpeed()
{
    return wind_speed;
}

void WeatherData::processRates()
{
    if (!xml->isStartElement() || xml->name() != "forecast")
        return;
    while (xml->readNextStartElement()) {
        if (xml->name() == "fact")
            processRate();
        else
            xml->skipCurrentElement();
    }
}

void WeatherData::processRate()
{
    if (!xml->isStartElement() || xml->name() != "fact")
        return;

    while (xml->readNextStartElement()) {
        if (xml->name() == "pressure")
            pressure = readNextText().toInt();
        else if (xml->name() == "wind_speed")
            wind_speed = readNextText().toInt();
//        else if (xml.name() == "conversion")
//            conversion = readNextText();
#ifndef USE_READ_ELEMENT_TEXT
        xml->skipCurrentElement();
#endif
    }

//    if (!(from.isEmpty() || to.isEmpty() || conversion.isEmpty()))
//        Currency::addRate(from, to, conversion);
}

QString WeatherData::readNextText()
{
#ifndef USE_READ_ELEMENT_TEXT
    xml->readNext();
    return xml->text().toString();
#else
    return xml->readElementText();
#endif
}

QString WeatherData::errorString()
{
    return "xml error!";
}

