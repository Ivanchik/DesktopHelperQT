#include "base.h"

Base::Base(MainWindow *view)
{
    // save view form
    this->view = view;

    InitUpdateValuteData();

    CreateTrayIcon();

}

void Base::CreateTrayIcon()
{
    try
    {
        if (!QSystemTrayIcon::isSystemTrayAvailable()) return;
        trayIcon = new QSystemTrayIcon(QIcon("://images/superman.ico"), this);
        QMenu *menu = new QMenu("Desktop Helper");
        trayIcon->setContextMenu(menu);

        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                                 view, SLOT(OnTrayActivate(QSystemTrayIcon::ActivationReason)));

        ShowSystemTray();
    }
    catch (...)
    {
        qWarning() << "Error in System Tray creating";
    }
}

void Base::ShowSystemTray()
{
   if (trayIcon != NULL) trayIcon->show();
}

void Base::InitUpdateValuteData()
{
    //Init valute data taker
    QNetworkAccessManager *m_nam = new QNetworkAccessManager();

    connect(m_nam, SIGNAL(finished(QNetworkReply*)), SLOT(OnLoad(QNetworkReply*)));

    QUrlQuery postData;
    QNetworkRequest req(QUrl("http://www.cbr.ru/scripts/XML_daily.asp?"));
     req.setHeader(QNetworkRequest::ContentTypeHeader,
                   "application/x-www-form-urlencoded");

     m_nam->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());
}

//Only for testing some code.
void Base::Test()
{


}

QString Base::getEuroValue() const
{
    return euroValue;
}

void Base::setEuroValue(const QString &value)
{
    euroValue = value;
}

QString Base::getDollarValue() const
{
    return dollarValue;
}

void Base::setDollarValue(const QString &value)
{
    dollarValue = value;
}

void Base::OnLoad(QNetworkReply *reply)
{

    #ifdef QT_DEBUG
        qDebug() << "This is debug";
    #endif

    //// TODO
    /// Refactor code
    ///

    QByteArray allData = reply->readAll();
    QXmlStreamReader xmlDoc(allData);
     //QXmlStreamReader::TokenType token;
     QXmlStreamAttributes attrib;

     bool dollar = false;
     bool euro = false;

     while (!xmlDoc.atEnd() && !xmlDoc.hasError())
     {
         xmlDoc.readNext();
         if (xmlDoc.name() == "Valute")
         {
           attrib = xmlDoc.attributes();

           //qDebug() << attrib.data()->value().toString();
           if ( attrib.value("ID").toString() == "R01235") // Dollar
           {
               xmlDoc.readNext();
               dollar = true;
           }

           if (attrib.value("ID").toString() == "R01239") //  EURO
           {
               xmlDoc.readNext();
               euro = true;
           }
         }

         if (xmlDoc.name() == "Value" && dollar)
         {
             dollarValue = xmlDoc.readElementText();
             dollar = false;
         }

         if (xmlDoc.name() == "Value" && euro)
         {
             euroValue = xmlDoc.readElementText();
             euro = false;
         }
    }

    emit tryGetValuteData();
    delete reply;
}

QString Base::getIP()
{
    try
    {
        QTcpSocket socket;

        //google DNS
        QString testAddress = "8.8.8.8";
        int port = 53;

        socket.connectToHost(testAddress, port);
        if (socket.waitForConnected()) {
            qDebug()
                << "local IPv4 address for Internet connectivity is"
                << socket.localAddress();
        } else {
            qWarning()
                << "could not determine local IPv4 address:"
                << socket.errorString();
        }

        return socket.localAddress().toString();
    }
    catch (...)
    {
        qWarning() << "Something wrong with getting ip";

        return NULL;
    }
}

