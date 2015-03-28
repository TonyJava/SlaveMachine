#ifndef COMMANDPARAMETER_H
#define COMMANDPARAMETER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDateTime>

class commandparameter : public QObject
{
    Q_OBJECT
public:
    explicit commandparameter(QObject *parent = 0);

signals:

public slots:
    void stringParsing(QString PackedCommandParameter);
    QString generateCommandParameter();


public:
    QString DataTime;
    QString S01_Rtd;
    QString Z12_Rtd;
    QString B03_Rtd;
    QString PW;

    QString CP;



};

#endif // COMMANDPARAMETER_H
