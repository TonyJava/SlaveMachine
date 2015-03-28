#include "commandparameter.h"

commandparameter::commandparameter(QObject *parent) :
    QObject(parent)
{



}

void commandparameter::stringParsing(QString PackedCommandParameter)
{
    QStringList tobeParse;
    tobeParse = PackedCommandParameter.split ("##");
    QString str = tobeParse.at(1);

    QStringList   strlist = str.split(";");

    for(int i=0;i<strlist.count();i++)
    {

        QStringList strstrlist=strlist.at(i).split("=");
        for(int j=0;j<strstrlist.count();)
        {
            qDebug("Field:%s",strstrlist.at(j++).toLocal8Bit().data());
            qDebug("Value:%s",strstrlist.at(j++).toLocal8Bit().data());

            if (strcmp (strstrlist.at(j++).toLocal8Bit() , "DataTime"))
            {
                this->DataTime = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "S01_Rtd"))
            {
                this->S01_Rtd = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "Z12_Rtd"))
            {
                this->Z12_Rtd = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "B03_Rtd"))
            {
                this->B03_Rtd = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "PW"))
            {
                this->PW = strstrlist.at(j++).toLocal8Bit().data();
            }

            //            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "CP"))
            //            {
            //                this->CP = strstrlist.at(j++).toLocal8Bit().data();
            //            }
            else
            {

            }
        }
    }
}

QString commandparameter::generateCommandParameter()
{
    CP = "";
    QDateTime _generagedtime = QDateTime::currentDateTime ();
    this->DataTime = (_generagedtime.toString ("yyyyMMddhhmmsszzz"));

    CP.append ("DataTime="+this->DataTime+";");

    if (!this->S01_Rtd.operator == (""))
    {
        CP.append ("S01-Rtd="+this->S01_Rtd+";");
    }
    if (!this->Z12_Rtd.operator == (""))
    {
        CP.append ("12-Rtd="+this->Z12_Rtd+";");
    }
    if (!this->B03_Rtd.operator == (""))
    {
        CP.append ("B03-Rtd="+this->B03_Rtd+";");
    }
    if (!this->PW.operator == (""))
    {
        CP.append ("PW="+this->PW+";");
    }

    if (this->CP.right (1) == (";"))
    {
        this->CP = this->CP.mid (0,this->CP.length ()-1);
    }

    return CP;
}
