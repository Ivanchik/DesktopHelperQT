#include "base.h"





Base::Base(MainWindow *view)
{
    // save view form
    this->view = view;

    //get ip address





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

