#include "uploaddata.h"

uploaddata::uploaddata(QList<QPair<QString , float> > *dataList, QMutex *dataListLocker , QObject *parent) :
    QThread(parent)
{
    this->DataList = dataList;
    this->DataListLocker = dataListLocker;
}

uploaddata::uploaddata(QObject *parent)
{
    waterData.CN = "2011";
    atmosphereData.CN = "2011";

}

void uploaddata::run()
{
    while(true)
    {
        pushWaterData ();
        pushAtmosphereData ();
        sleep(3);
    }
}

void uploaddata::refreshData()
{
//    if (this->DataList->first ().first == "B03-Rtd")
//    {
//        this->dataToPush.CPOriginal.B03_Rtd = this->DataList->first ().second;

//    }
//    else if (this->DataList->first ().first == "12_Rtd")
//    {

//    }
//    else if (this->DataList->first ().first == "S01-Rtd")
//    {

    //    }
}

void uploaddata::pushWaterData()
{
    this->waterData.CPOriginal.S01_Rtd = QString::number (qrand() % ((300 + 1) - 100) + 100,'f',1);
    this->waterData.CPOriginal.Z12_Rtd = QString::number (qrand() % ((3000 + 1) - 1000) + 100,'f',3);
    this->waterData.ST="22";
    emit sendData (waterData.generatePackage ());
}

void uploaddata::pushAtmosphereData()
{
    this->atmosphereData.CPOriginal.B03_Rtd = QString::number (qrand() % ((300 + 1) - 100) + 100,'f',1);
    this->atmosphereData.ST="23";
    emit sendData (atmosphereData.generatePackage ());
}



