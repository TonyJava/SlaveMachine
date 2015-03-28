#include "heartbeatcontrol.h"

heartbeatcontrol::heartbeatcontrol(QObject *parent) :
    QThread(parent)
{

}

void heartbeatcontrol::run()
{
    while (true)
    {
        heartBeat ();
        sleep (15);
    }
}

void heartbeatcontrol::heartBeat()
{
    DataProtocol dp;
    QString Message;
    dp.CN = "3015";
    dp.PW = "666663";
    dp.MN = "88888880000001";
    dp.ST = "91";
    Message = dp.generatePackage ();
    emit sendHeartBeat (Message);
}
