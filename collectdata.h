#ifndef COLLECTDATA_H
#define COLLECTDATA_H

#include <QThread>
#include <QList>
#include <QPair>
#include <QMutex>
//#include <list>
//#include <queue>
//using namespace std;
class collectdata : public QThread
{
    Q_OBJECT
public:
    explicit collectdata(QList<QPair<QString , float> > *dataList, QMutex *dataListLocker , QObject *parent = 0);

public:
    void run();

signals:
    void needPushData(QString , float);

public slots:

    void getData();
public:

    QList <QPair<QString , float> > *DataList;

    float S01_Rtd;
    float Z12_Rtd;
    float B03_Rtd;

    QMutex *dataListLocker;

    //S01-Rtd
    //12-Rtd
    //B03-Rtd


//    list<pair<QString,int > > l1;
//    priority_queue<> p1;
//    pair<QString,int> f = l1.front ();
//    f.
//    l1.push_front ();
};

#endif // COLLECTDATA_H
