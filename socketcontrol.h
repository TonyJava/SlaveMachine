#ifndef SOCKETCONTROL_H
#define SOCKETCONTROL_H
#include <QThread>
#include <QtNetwork/QTcpSocket>
#include <iostream>
#include <QMutex>
using namespace std;
class SocketThread : public QThread
{
    Q_OBJECT
public:
    explicit SocketThread(QString MasterMachineAddr , qint16 MasterMachinePort, QObject *parent = 0);

public:
    void run();
signals:
    void needSendMessage(QString Message);
public slots:
    void reportRealtimeData();
    void sendData(QString Message); // send messages
    void connectToServer();
    void onlineNotification();


public:
    QTcpSocket *ClientSocket;
private:
    QString ServerAddr;
    qint16 ServerPort;
    QMutex SocketLocker;
};

#endif // SOCKETCONTROL_H
