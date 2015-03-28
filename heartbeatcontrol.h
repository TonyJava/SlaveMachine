#ifndef HEARTBEATCONTROL_H
#define HEARTBEATCONTROL_H

#include <QThread>
#include "dataprotocol.h"

class heartbeatcontrol : public QThread
{
    Q_OBJECT
public:
    QString heartBeatString;
public:
    explicit heartbeatcontrol(QObject *parent = 0);

public:
    void run();

signals:
    void sendHeartBeat(QString);

public slots:
    void heartBeat();

};

#endif // HEARTBEATCONTROL_H
