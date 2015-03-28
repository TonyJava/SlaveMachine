#include "socketcontrol.h"
#include "dataprotocol.h"
SocketThread::SocketThread(QString MasterMachineAddr , qint16 MasterMachinePort, QObject *parent) :QThread(parent)
{
    this->ServerAddr = MasterMachineAddr;
    this->ServerPort = MasterMachinePort;

}

void SocketThread::run()
{
    //thread starts here
    this->ClientSocket = new QTcpSocket();
    this->connectToServer ();
    connect (this->ClientSocket , SIGNAL(disconnected()) ,
             this , SLOT (connectToServer ()) , Qt::DirectConnection);
    this->exec (); // go to listening signals

}


void SocketThread::reportRealtimeData()
{

}

///
/// \brief SocketThread::sendData
/// send a Qstring data
/// \param Message
///Data to send
void SocketThread::sendData(QString Message)
{    
                                                 // Client should be locked here
    QByteArray MessageArray;                                         // Byte array to be send
    MessageArray.append (Message);                                   // append the message to byte array

    SocketLocker.lock ();
    qDebug()<<this->ClientSocket->write (MessageArray);
    if (!ClientSocket->waitForBytesWritten(3000))                           // try to send data to server
    {
        disconnect (this , SIGNAL(needSendMessage(QString)) ,
                    this , SLOT(sendData(QString)));
        qDebug () << "Connection lost , retrying connect to the server\n"; // if not success , connect to server again
        connectToServer ();
    }
    SocketLocker.unlock (); // unlock the ClientSocket.
}
///
/// \brief SocketThread::connectToServer
///Connect to server,and send a package to online.
///
void SocketThread::connectToServer()
{
    disconnect (this , SIGNAL(needSendMessage(QString)) ,
                this , SLOT(sendData(QString)));
    // disable send data at this time
    qDebug () << "Connecting to server...";
    do
    {
        this->ClientSocket->connectToHost (this->ServerAddr ,
                                           this->ServerPort , QIODevice::ReadWrite);
        qDebug () << ".";
        sleep (1);

    }
    while (!ClientSocket->waitForConnected (3000));
    qDebug () << "Connecting to server successfully\n";
    onlineNotification ();
    connect (this , SIGNAL(needSendMessage(QString)) ,
             this , SLOT(sendData(QString)) , Qt::DirectConnection);
    //enable send data

}

///Send an online Notification
/// \brief SocketThread::onlineNotification
///
void SocketThread::onlineNotification()
{
    DataProtocol dp;
    QString Message;
    dp.CN = "3015";
    dp.PW = "666663";
    dp.MN = "88888880000001";
    dp.ST = "91";
    Message = dp.generatePackage ();
    qDebug () << Message;

    QByteArray MessageArray;                                         // Byte array to be send
    MessageArray.append (Message);                                   // append the message to byte array
    this->ClientSocket->write (MessageArray);
    ClientSocket->waitForBytesWritten (3000);
}

