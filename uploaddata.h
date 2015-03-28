#ifndef UPLOADDATA_H
#define UPLOADDATA_H

#include <QThread>
#include <QMutex>
#include <QList>
#include <QPair>
#include "dataprotocol.h"
class uploaddata : public QThread
{
    Q_OBJECT
public:
    explicit uploaddata(QList<QPair<QString, float> > *dataList, QMutex *dataListLocker, QObject *parent = 0);
    explicit uploaddata(QObject *parent = 0);
public:
    void run();

signals:
    void sendData(QString);


public slots:
    void refreshData();
    void pushAtmosphereData();
    void pushWaterData();

public:
    QList<QPair<QString, float> > *DataList;
    QMutex *DataListLocker;

    DataProtocol waterData;
    DataProtocol atmosphereData;

};

#endif // UPLOADDATA_H
