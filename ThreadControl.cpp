#include "ThreadControl.h"
SocketThread::SocketThread(QString MasterMachineAddr , qint16 MasterMachinePort, QObject *parent) :QThread(parent)
{
    this->ServerAddr = MasterMachineAddr;
    this->ServerPort = MasterMachinePort;

}

void SocketThread::run()
{
    this->ClientSocket = new QTcpSocket();
    this->connectToServer ();
    connect (this->ClientSocket , SIGNAL(disconnected()) , this , SLOT (connectToServer ()) , Qt::QueuedConnection);

    this->exec ();

}


void SocketThread::reportRealtimeData()
{

}


void SocketThread::sendData(QString Message)
{
    long long i = 1;
    for (i = 1  ; i < 999999 ; i ++)
    {
        qDebug ()<<i;
    }
                                                 // Client should be locked here
    QByteArray MessageArray;                                         // Byte array to be send
    MessageArray.append (Message);                                   // append the message to byte array


    qDebug()<<this->ClientSocket->write (MessageArray);

    SocketLocker.lock ();
    if (!ClientSocket->waitForBytesWritten(3000))                           // try to send data to server
    {
        disconnect (this , SIGNAL(needSendMessage(QString)) , this , SLOT(sendData(QString)));
        qDebug () << "Connection lost , retrying connect to the server\n"; // if not success , connect to server again

        connectToServer ();
    }
    SocketLocker.unlock (); // unlock the ClientSocket.
}

void SocketThread::connectToServer()
{
    disconnect (this , SIGNAL(needSendMessage(QString)) , this , SLOT(sendData(QString)));
    do
    {
        this->ClientSocket->connectToHost (this->ServerAddr , this->ServerPort , QIODevice::ReadWrite);
        qDebug () << "Trying connect to server...\n";
        sleep (1);

    }
    while (!ClientSocket->waitForConnected (3000));
    onlineNotification ();

    connect (this , SIGNAL(needSendMessage(QString)) , this , SLOT(sendData(QString)) , Qt::QueuedConnection);

}

void SocketThread::onlineNotification()
{
    QString *message = new QString("##0017CN=1011;PW=123456e101\r\n");

    QByteArray MessageArray;                                         // Byte array to be send
    MessageArray.append (*message);                                   // append the message to byte array
                                        // Client should be locked here
    qDebug()<<this->ClientSocket->write (MessageArray);
}

