#include "base.h"





Base::Base(MainWindow *view)
{
    // save view form
    this->view = view;

    //get ip address

}


void Base::Test()
{
    QNetworkAccessManager *m_nam = new QNetworkAccessManager();

    connect(m_nam, SIGNAL(finished(QNetworkReply*)), SLOT(OnLoad(QNetworkReply*)));

    QUrlQuery postData;
    // postData.addQueryItem("ID", "R01235");
    QNetworkRequest req(QUrl("http://www.cbr.ru/scripts/XML_daily.asp?"));
     req.setHeader(QNetworkRequest::ContentTypeHeader,
                   "application/x-www-form-urlencoded");

     m_nam->post(req, postData.toString(QUrl::FullyEncoded).toUtf8());

}

void Base::OnLoad(QNetworkReply *reply)
{


//// TODO
/// Refactor code

     QByteArray allData = reply->readAll();
     QXmlStreamReader xmlDoc(allData);
     //QXmlStreamReader::TokenType token;
     QXmlStreamAttributes attrib;

     bool flag = false;

     while (!xmlDoc.atEnd() && !xmlDoc.hasError())
     {

         xmlDoc.readNext();
         if (xmlDoc.name() == "Valute")
         {
           attrib = xmlDoc.attributes();

           qDebug() << attrib.data()->value().toString();
           if ( attrib.value("ID").toString() == "R01235" ||
                attrib.value("ID").toString() == "R01239") //  EURO Dollar
           {
               xmlDoc.readNext();
               flag = true;
           }
           else
           {
               flag = false;
           }
         }

         if (xmlDoc.name() == "Value" && flag)
         {
             qDebug() << xmlDoc.readElementText();
         }
    }
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

