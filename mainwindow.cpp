/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        佛祖保佑       永无BUG   该模块已开光
佛曰:
              写字楼里写字间，写字间里程序员；
              程序人员写程序，又拿程序换酒钱。
              酒醒只在网上坐，酒醉还来网下眠；
              酒醉酒醒日复日，网上网下年复年。
              但愿老死电脑间，不愿鞠躬老板前；
              奔驰宝马贵者趣，公交自行程序员。
              别人笑我忒疯癫，我笑自己命太贱；
              不见满街漂亮妹，哪个归得程序员？
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataprotocol.h"



//************Thread controlling should be like this:
//************1.Create a thread
//************2.Create a thread control object , the object contains the signals to emit.
//************3.Connect source thread's signal and thread control object's signal.(QueuedConnection)
//************4.Connect thread control object's signal and thread's slot(DirectConnection)
//************5.Emit the signal in source thread.
//************Tip:Do not connect signals/slots between source thread and destination thread.
//************Use an object to connect thease two things(recommend)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    SlaveMachineSocket = new SocketThread("172.16.120.194" , 6021 , this); // Chr_Wonder's Machine
    //SlaveMachineSocket = new SocketThread("172.16.120.154" , 6666 , this); // netcat -lp 6666
    threadControl = new ThreadControl(this);
    heartBeat = new heartbeatcontrol(this);
    uploadDataThread = new uploaddata(this);


    threadControl->moveToThread (SlaveMachineSocket);
    connect (this,SIGNAL(sendMessage(QString)) ,
             this->threadControl , SIGNAL(sendData(QString)) , Qt::QueuedConnection);// for debug

    connect (this->heartBeat , SIGNAL(sendHeartBeat(QString)) ,
             this->threadControl , SIGNAL(sendData(QString)) , Qt::QueuedConnection); // for heart beat thread
    connect (this->uploadDataThread , SIGNAL(sendData(QString)),
             this->threadControl , SIGNAL(sendData(QString)) , Qt::QueuedConnection);


    connect (this->threadControl , SIGNAL(sendData(QString)) ,
             SlaveMachineSocket , SIGNAL (needSendMessage(QString)) , Qt::DirectConnection);

    SlaveMachineSocket->start ();
    heartBeat->start ();
    uploadDataThread->start ();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnConnectServerTest_clicked()
{


}

void MainWindow::on_BtnSendMessageTest_clicked()
{
    QString Message = "##0017CN=1011;PW=123456e101\r\n";

    emit this->sendMessage (Message);
}

void MainWindow::on_BtnGenerateString_clicked()
{

}
