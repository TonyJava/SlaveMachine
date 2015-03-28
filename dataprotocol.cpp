#include "dataprotocol.h"
//#include "cstdio"
DataProtocol::DataProtocol()
{
    QDateTime _generagedtime = QDateTime::currentDateTime ();

    this->MN = "88888880000001";
    this->QN = (_generagedtime.toString ("yyyyMMddhhmmsszzz"));
    this->PW = "666663";
}

DataProtocol::DataProtocol(QString PackedPackage)
{
    stringParsing (PackedPackage);
}

void DataProtocol::stringParsing(QString PackedPackage)
{
//    QString       str = "QQ#34241988;E-mail#songwei_163@163.com;Address#Chengdu,Sichuan;MSN#songwei_163@163.com;Home Page#http://www.google.com";
    QString str = PackedPackage.mid (6,PackedPackage.length ()-12);
    QStringList   strlist = str.split(";");

    for(int i=0;i<strlist.count();i++)
    {
        QStringList strstrlist=strlist.at(i).split("=");
        for(int j=0;j<strstrlist.count();)
        {
            qDebug("Field:%s",strstrlist.at(j++).toLocal8Bit().data());
            qDebug("Value:%s",strstrlist.at(j++).toLocal8Bit().data());

            if (strcmp (strstrlist.at(j++).toLocal8Bit() , "QN"))
            {
                this->QN = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "PNUM"))
            {
                this->PNUM = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "PNO"))
            {
                this->PNO = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "CN"))
            {
                this->CN = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "PW"))
            {
                this->PW = strstrlist.at(j++).toLocal8Bit().data();
            }
            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "MN"))
            {
                this->MN = strstrlist.at(j++).toLocal8Bit().data();
            }
            //            else if (strcmp(strstrlist.at(j++).toLocal8Bit() , "CP"))
            //            {
            //                this->CP = strstrlist.at(j++).toLocal8Bit().data();
            //            }
            else
            {

            }
        }
        this->Length = PackedPackage.mid (2,4);
        this->CRC = PackedPackage.mid (PackedPackage.length ()-6,4);
    }

}
QString DataProtocol::generatePackage()
{
    QString _package = "";
    unsigned short _crc;
    QString _crcqstring;

    if (!this->QN.operator == (""))
    {
        _package.append ("QN="+this->QN+";");
    }
    if (!this->PNUM.operator == (""))
    {
        _package.append ("PNUM="+this->PNUM+";");
    }
    if (!this->PNO.operator == (""))
    {
        _package.append ("PNO="+this->PNO+";");
    }
    if (!this->CN.operator == (""))
    {
        _package.append ("CN="+this->CN+";");
    }
    if (!this->PW.operator == (""))
    {
        _package.append ("PW="+this->PW+";");
    }
    if (!this->MN.operator == (""))
    {
        _package.append ("MN="+this->MN+";");
    }
    if (!this->ST.operator == (""))
    {
        _package.append ("ST="+this->ST+";");
    }

    this->CP = CPOriginal.generateCommandParameter ();

    _package.append ("CP=&&"+this->CP+"&&");

    if (_package.operator == ("&&&&"))
    {
        return "ERROR";
    }

    this->Length = QString::number (_package.length ());
    if(this->Length.size()<4)
    {
        this->Length = QString(4-this->Length.size(), '0')+this->Length;
    }

    _crc = CRCCheck ((unsigned char*)(_package.toAscii ().data ()), (short)_package.length ());

    _crcqstring = QString::number(_crc , 16);
    if(_crcqstring.size()<4)
    {
        _crcqstring = QString(4-_crcqstring.size(), '0')+_crcqstring;
    }

    _package.insert(0,this->Length);
    _package.insert (0,"##");
    _package.append (_crcqstring);
    _package.append ("\r\n");

    return _package;
}

unsigned short DataProtocol::CRCCheck(unsigned char *puchMsg, unsigned short usDataLen)
{

    unsigned short reg16=0xFFFF;			// ① 装一个16位寄存器，所有数位均为1。
    unsigned char	 regHi, regLow;
    unsigned char  charCheck,charOut;
    for(int i=0;i<usDataLen;i++)
    {
        regHi=(reg16>>8)&0x00FF;
        regLow=reg16&0x00FF;
        charCheck=puchMsg[i];		// ② 取被校验串的一个字节   ⑥ 取被校验串的下一个字节
        reg16=regHi^charCheck;		// 与16位寄存器的高位字节进行"异或"运算。运算结果放入这个16位寄存器(这里有放入高位和低位之分)。
        //	reg16=(regHi^charCheck)<<8;
        for(int j=0;j<8;j++)
        {
            charOut=reg16&0x0001;
            reg16=reg16>>1;		// ③  把这个16寄存器向右移一位。
            if(0x0001==charOut)	// ④ 若向右（标记位）移出的数位是1，
            {					//4 则生成多项式1010 0000 0000 0001和这个寄存器进行"异或"运算；

                reg16=reg16^0xA001;                
            }
            //	若向右移出的数位是0，则返回③。
        }	// ⑤ 重复③和④，直至移出8位。
    }	// ⑦ 重复③~⑥，直至被校验串的所有字节均与16位寄存器进行"异或"运算，并移位8次。
    return reg16;		// ⑧ 这个16位寄存器的内容即2字节CRC错误校验码.
}
