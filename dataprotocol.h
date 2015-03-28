#ifndef DATAPROTOCOL_H
#define DATAPROTOCOL_H
#include <QObject>
#include <QtCore>
#include <QCoreApplication>
#include <QDateTime>
#include <cstdio>
#include <cstdlib>
#include "commandparameter.h"

class DataProtocol : QObject
{
    Q_OBJECT
public:
    explicit DataProtocol();
    explicit DataProtocol(QString PackedPackage);
public:

public slots:
    unsigned short CRCCheck(unsigned char *puchMsg, unsigned short usDataLen);    
    void stringParsing(QString PackedPackage);
    QString generatePackage();

public:
    QString QN;
    QString PNUM;
    QString PNO;
    QString ST;
    QString CN;
    QString PW;
    QString CP;
    QString MN;
    commandparameter CPOriginal;

    QString Length;
    QString CRC ;

};



#endif // DATAPROTOCOL_H
