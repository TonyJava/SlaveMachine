#include "collectdata.h"

collectdata::collectdata(QList<QPair<QString , float> > *dataList ,QMutex *dataListLocker ,QObject *parent) :
    QThread(parent)
{
    this->dataListLocker = dataListLocker;
    this->DataList = dataList;
}

void collectdata::run()
{
    int i = 0;
    while(true)
    {
        i++;
        this->getData ();
        sleep(1);
        if (i == 15)
        {
            dataListLocker->lock ();

            this->DataList->clear ();

            dataListLocker->unlock ();
        }
    }
}



void collectdata::getData()
{
    dataListLocker->lock ();
    this->B03_Rtd = qrand() % ((300 + 1) - 100) + 100;
    this->Z12_Rtd = qrand() % ((3000 + 1) - 1000) + 1000;
    this->S01_Rtd = qrand() % ((300 + 1) - 100) + 100;
    if (DataList->length () <= 60)
    {
        this->DataList->append (qMakePair<QString , float>("B03-Rtd" , this->B03_Rtd));
        this->DataList->append (qMakePair<QString , float>("12_Rtd" , this->Z12_Rtd));
        this->DataList->append (qMakePair<QString , float>("S01-Rtd" , this->S01_Rtd));
    }
    else
    {
        DataList->removeFirst ();
        DataList->removeFirst ();
        DataList->removeFirst ();
        this->DataList->append (qMakePair<QString , float>("B03-Rtd" , this->B03_Rtd));
        this->DataList->append (qMakePair<QString , float>("12_Rtd" , this->Z12_Rtd));
        this->DataList->append (qMakePair<QString , float>("S01-Rtd" , this->S01_Rtd));
    }
    dataListLocker->unlock ();

}
