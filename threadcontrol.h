#ifndef THREADCONTROL_H
#define THREADCONTROL_H

#include <QObject>

class ThreadControl : public QObject
{
    Q_OBJECT
public:
    explicit ThreadControl(QObject *parent = 0);

signals:
    void sendData(QString Message);


public slots:

};

#endif // THREADCONTROL_H
