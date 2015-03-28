#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socketcontrol.h"
#include "threadcontrol.h"
#include "heartbeatcontrol.h"
#include "uploaddata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BtnConnectServerTest_clicked();

    void on_BtnSendMessageTest_clicked();

    void on_BtnGenerateString_clicked();

private:
    Ui::MainWindow *ui;
    SocketThread *SlaveMachineSocket;
    heartbeatcontrol *heartBeat;
    uploaddata *uploadDataThread;
public:
    ThreadControl *threadControl;

signals:
    void sendMessage(QString Message);
};

#endif // MAINWINDOW_H
