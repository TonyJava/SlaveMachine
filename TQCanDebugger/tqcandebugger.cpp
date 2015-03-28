#include "tqcandebugger.h"
#include <QHBoxLayout>
#include <QRegExpValidator>
#include <QVBoxLayout>
#include <QtDebug>

TQCanDebugger::TQCanDebugger(QWidget *parent, bool bKeyShow) :
	QWidget(parent) {

	this->setWindowTitle(trUtf8("天嵌科技串口工具V1.0(www.EmbedSky.com)"));
	/*	QRect screen_size = QApplication::desktop()->screenGeometry();
	 m_iWidth = screen_size.width();
	 m_iHeight = screen_size.height();*/
	QLabel *leTitle = new QLabel(trUtf8("天嵌科技CAN测试程序"), this);
	QPixmap pixmap("/opt/PDA/app/images/background.jpg");
	QPalette palette;
	palette.setBrush(backgroundRole(), QBrush(pixmap));
	setPalette(palette);
	/*	QRegExp rx("^[A-Fa-f0-9Xx]+$");
	 //	QRegExp rx("-?\\d{0,9}");
	 QRegExpValidator *exp = new QRegExpValidator(rx, this);*/

	iShowKey = true;
	m_iRecvCount = 0;
	m_iSendCount = 0;
	m_bRecv = true;

	m_pAutoSend = new QTimer(this);
	connect(m_pAutoSend, SIGNAL(timeout()), this, SLOT(pbSendClicked()));

	m_pteDisplay = new QTextBrowser(this);
	QLabel *leLabel1 = new QLabel(trUtf8("接\n收"), this);
	QHBoxLayout *RecvLayout = new QHBoxLayout;
	RecvLayout->addSpacing(3);
	RecvLayout->addWidget(leLabel1);
	RecvLayout->addWidget(m_pteDisplay);

	m_leSend = new QTextEdit(this);
	m_leSend->setMinimumHeight(40);
	m_leSend->setText("11 11 22 33 44 55 66 77 88");
	//	m_leSend->setValidator(exp);
	QLabel *leLabel = new QLabel(trUtf8("发\n送"), this);
	QHBoxLayout *pteLayout = new QHBoxLayout;
	pteLayout->addSpacing(3);
	pteLayout->addWidget(leLabel);
	pteLayout->addWidget(m_leSend);

	QPixmap pix;

	/*	m_pbSelect = new QPushButton(this);
	 m_pbSelect->setFixedSize(60, 32);
	 m_pbSelect->setIconSize(QSize(60, 32));
	 pix.load("/opt/PDA/app/images/selectFile.png", 0, Qt::AutoColor);
	 pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	 m_pbSelect->setIcon(QIcon(pix));*/

	//	connect(m_pbSelect, SIGNAL(clicked()), this, SLOT(pbSelectClicked()));

	QHBoxLayout *controlsLayout = new QHBoxLayout;

	m_pbClearCount = new QPushButton(this);
	m_pbClearCount->setFixedSize(60, 32);
	m_pbClearCount->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/clearCount.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbClearCount->setIcon(QIcon(pix));

	m_pbSet = new QPushButton(this);
	m_pbSet->setFixedSize(60, 32);
	m_pbSet->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/setPara.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbSet->setIcon(QIcon(pix));

	m_pbSend = new QPushButton(this);
	m_pbSend->setFixedSize(60, 32);
	m_pbSend->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/send.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbSend->setIcon(QIcon(pix));

	m_pbKey = new QPushButton(this);
	m_pbKey->setFixedSize(60, 32);
	m_pbKey->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/key.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbKey->setIcon(QIcon(pix));
	m_pbKey->setEnabled(0);

	m_pbHelp = new QPushButton(this);
	m_pbHelp->setFixedSize(60, 32);
	m_pbHelp->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/help.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbHelp->setIcon(QIcon(pix));
	connect(m_pbHelp, SIGNAL(clicked()), this, SLOT(pbHelpClicked()));

	QPushButton *pbClose = new QPushButton(this);
	pbClose->setFixedSize(82, 32);
	pbClose->setIcon(QIcon("/opt/PDA/app/images/exit.png"));//设置退出案件图标
	pbClose->setIconSize(QSize(82, 32));

	pbClose->setFixedSize(60, 32);
	pbClose->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/exit.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	pbClose->setIcon(QIcon(pix));

	connect(pbClose, SIGNAL(clicked()), this, SLOT(Close()));

	connect(m_pbSend, SIGNAL(clicked()), this, SLOT(pbSendClicked()));
	connect(m_pbSet, SIGNAL(clicked()), this, SLOT(pbSetClicked()));
	connect(m_pbClearCount, SIGNAL(clicked()), this,
			SLOT(pbClearCountClicked()));

	controlsLayout->addSpacing(3);
	controlsLayout->addWidget(m_pbKey);
	controlsLayout->addWidget(m_pbHelp);
	controlsLayout->addWidget(m_pbSet);
	controlsLayout->addWidget(m_pbClearCount);
	//	controlsLayout->addWidget(m_pbSelect);
	controlsLayout->addWidget(m_pbSend);
	controlsLayout->addWidget(pbClose);
	controlsLayout->addSpacing(3);

	//状态栏
	m_pBar = new QStatusBar(this);
	m_pBar->setMaximumHeight(45);
	m_plbUrl = new QLabel("www.EmbedSky.com", this);
	m_plbUrl->setFrameShape(QFrame::WinPanel);
	m_plbUrl->setFrameShadow(QFrame::Sunken);
	m_pBar->addWidget(m_plbUrl, 20);

	m_plbSend = new QLabel("S:0", this);
	m_plbSend->setFrameShape(QFrame::WinPanel);
	m_plbSend->setFrameShadow(QFrame::Sunken);
	m_pBar->addWidget(m_plbSend, 10);

	m_plbRecv = new QLabel("R:0", this);
	m_plbRecv->setFrameShape(QFrame::WinPanel);
	m_plbRecv->setFrameShadow(QFrame::Sunken);
	m_pBar->addWidget(m_plbRecv, 10);

	m_plbComStatus = new QLabel(trUtf8("can0 can1 自发自收"), this);
	m_plbComStatus->setFrameShape(QFrame::WinPanel);
	m_plbComStatus->setFrameShadow(QFrame::Sunken);
	m_pBar->addWidget(m_plbComStatus, 32);

	m_pcbHexRecv = new QCheckBox(trUtf8("HEX收"), this);
	connect(m_pcbHexRecv, SIGNAL(clicked()), this, SLOT(cbDisplay()));
	m_pcbHexSend = new QCheckBox(trUtf8("HEX发"), this);
	connect(m_pcbHexSend, SIGNAL(clicked()), this, SLOT(cbHexSendClicked()));

	m_pcbExtendSend = new QCheckBox(trUtf8("扩展帧发"), this);
	//	connect(m_pcbExtendSend, SIGNAL(stateChanged(int)), this, SLOT(cbSendDisplayStateChanged()));

	m_pbClearRecv = new QPushButton(this);
	m_pbClearRecv->setFixedSize(60, 32);
	m_pbClearRecv->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/clearRec.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbClearRecv->setIcon(QIcon(pix));
	connect(m_pbClearRecv, SIGNAL(clicked()), this, SLOT(pbClearRecvClicked()));

	m_pbClearSend = new QPushButton(this);
	m_pbClearSend->setFixedSize(60, 32);
	m_pbClearSend->setIconSize(QSize(60, 32));
	pix.load("/opt/PDA/app/images/clearSend.png", 0, Qt::AutoColor);
	pix = pix.scaled(60, 32, Qt::IgnoreAspectRatio);//图片大小
	m_pbClearSend->setIcon(QIcon(pix));

	connect(m_pbClearSend, SIGNAL(clicked()), this, SLOT(pbClearSendClicked()));

	m_pcbLoopSend = new QCheckBox(trUtf8("自动发"));
	connect(m_pcbLoopSend, SIGNAL(clicked()), this, SLOT(cbAutoSendClicked()));

	m_cbFilte = new QCheckBox(trUtf8("过滤帧"));
	connect(m_cbFilte, SIGNAL(clicked()), this, SLOT(cbDisplay()));

	m_leFrame = new QLineEdit();
	m_leFrame->setFixedSize(60, 32);
	m_leFrame->setText("1000");
	m_leFrame->setMinimumWidth(60);

	m_leFilte = new QLineEdit();
	m_leFilte->setFixedSize(60, 32);
	m_leFilte->setText("01");
	m_leFilte->setMinimumWidth(60);

	QRegExp rx("^[A-Fa-f0-9Xx]+$");
	QRegExpValidator *exp = new QRegExpValidator(rx, this);

	QRegExp rx1("-?\\d{0,9}");
	QRegExpValidator *exp1 = new QRegExpValidator(rx1, this);

	m_leFrame->setValidator(exp1);
	m_leFilte->setValidator(exp);
	QLabel *lbInterval = new QLabel(trUtf8("ms"));

	QHBoxLayout *sendLayout = new QHBoxLayout;
	sendLayout->addSpacing(22);
	sendLayout->addWidget(m_pcbHexRecv);
	sendLayout->addWidget(m_pcbHexSend);
	sendLayout->addWidget(m_pcbExtendSend);
	sendLayout->addWidget(m_cbFilte);
	sendLayout->addWidget(m_leFilte);
	sendLayout->addWidget(m_pcbLoopSend);
	sendLayout->addWidget(m_leFrame);
	sendLayout->addWidget(lbInterval);
	sendLayout->addWidget(m_pbClearRecv);
	sendLayout->addWidget(m_pbClearSend);
	sendLayout->addSpacing(7);

	QHBoxLayout *titleLayout = new QHBoxLayout;
	titleLayout->addStretch(0);
	titleLayout->addWidget(leTitle);
	titleLayout->addStretch(0);

	QVBoxLayout *centralLayout = new QVBoxLayout;
	centralLayout->addSpacing(10);
	centralLayout->addLayout(titleLayout);
	centralLayout->addLayout(RecvLayout);
	centralLayout->addLayout(sendLayout);
	centralLayout->addLayout(pteLayout);
	centralLayout->addLayout(controlsLayout);
	centralLayout->addWidget(m_pBar);
	centralLayout->setMargin(1);

	this->setLayout(centralLayout);
	m_pteDisplay->clear();
	setPara = new uiSetCanPara(this);
	connect(setPara, SIGNAL(stateChanged()), this, SLOT(cbStateChanged()));

	m_cptr = {"candump","can0",""};
	m_threadRecv = new ThreadRec(2,m_cptr);
	connect(m_threadRecv,SIGNAL(mesRecv(QString)), this, SLOT(ShowCanMsg(QString)));
	m_threadRecv->start();

	if (bKeyShow)
	 {
	 m_pbKey->setEnabled(1);
	 connect(m_pbKey, SIGNAL(clicked()), this, SLOT(pbKeyShowHide()));
     //im = new TQInputMethod;
	 QWSServer::setCurrentInputMethod(im);
     //((TQInputMethod *) im)->setVisible(false);
	 }
}

TQCanDebugger::~TQCanDebugger() {
	delete m_pAutoSend;
}

void TQCanDebugger::ShowCanMsg(QString str) {
	if (m_pteDisplay->toPlainText().length() > 2000)
		m_pteDisplay->clear();
	m_strDisplay = m_strDisplay + str + "\n";
	m_pteDisplay->setText(m_strDisplay);
	QTextCursor cursor = m_pteDisplay->textCursor();
	cursor.movePosition(QTextCursor::End);
	m_pteDisplay->setTextCursor(cursor);
	cbDisplay();
	m_iRecvCount++;
	QString strRecv = "R:" + QString::number(m_iRecvCount);
	m_plbRecv->setText(strRecv);
}
void TQCanDebugger::pbClearRecvClicked() {
	m_pteDisplay->clear();
	m_strDisplay = "";
}
//清空发区
void TQCanDebugger::pbClearSendClicked() {
	m_leSend->clear();
}

//清空计数器
void TQCanDebugger::pbClearCountClicked() {
	m_iRecvCount = 0;
	m_iSendCount = 0;
	m_plbRecv->setText("R:0");
	m_plbSend->setText("S:0");
}

void TQCanDebugger::pbSendClicked() {
	QProcess *process3 = new QProcess(this);
	QString str = m_leSend->toPlainText();
	QStringList List = str.split("\n");
	for(int j=0;j<List.length();j++){
		QStringList list = List[j].trimmed().simplified().split(" ");
		if(m_pcbHexSend->isChecked())
		{
			for(int i=0;i<list.length();i++){
				list[i] = "0x" + list[i];
			}
		}
		list.insert(0, "-i");
		list.insert(0, setPara->m_strCan);
		if (m_pcbExtendSend->isChecked())
			list << "-e";
		if(process3->execute("cansend", list) == 0){
			m_iSendCount++;
			QString strRecv = "S:" + QString::number(m_iSendCount);
			m_plbSend->setText(strRecv);
		}
	}
}

void TQCanDebugger::Close() {
	m_threadRecv->stop();
	QStringList list;
	list << setPara->m_strCan << "stop";
	QProcess* process1;
	process1 = new QProcess();
	process1->execute("canconfig", list);
	close();
}
void TQCanDebugger::pbSetClicked() {
	setPara->showFullScreen();
	//	setPara->show();
}
void TQCanDebugger::cbStateChanged() {

	if(setPara->m_strCan.contains("can0"))
	{
		if(setPara->m_bTest)
			m_cptr[1] = "can1";
		else
			m_cptr[1] = "can0";
	}
	else if(setPara->m_strCan.contains("can1"))
	{
		if(setPara->m_bTest)
			m_cptr[1] = "can0";
		else
			m_cptr[1] = "can1";
	}

	m_cptr[0] = "candump";
	m_cptr[2] = " ";
	m_threadRecv = new ThreadRec(2,m_cptr);
	connect(m_threadRecv,SIGNAL(mesRecv(QString)), this, SLOT(ShowCanMsg(QString)));
	m_threadRecv->start();

	QString send;
	if(setPara->m_bTest)
	{
		send = "can0";
		send = send + " ";
		send = send +"can1";
		send = send + " ";
		send = send + trUtf8("自发自收");
	}
	else
	{
		send = setPara->m_strCan + "   " + setPara->m_strRate + "bps" + "   "
		+ setPara->m_strMode;
	}
	m_plbComStatus->setText(send);
}
void TQCanDebugger::pbHelpClicked() {
	QStringList list;
	list << "-appname=" + QApplication::applicationFilePath();
	QProcess* process = new QProcess(this);
	process->start("/opt/PDA/bin/tqhelp", list);
}
void TQCanDebugger::cbAutoSendClicked()
{
	if (m_pcbLoopSend->isChecked())
	{
		if (m_leFrame->text() != "")
		{
			m_pAutoSend->start(m_leFrame->text().toInt());
			m_leFrame->setEnabled(false);
		}
	}
	else
	{
		m_pAutoSend->stop();
		m_leFrame->setEnabled(true);
	}
}
void TQCanDebugger::cbDisplay(){
	QString strFilter = m_strDisplay;
	if(m_cbFilte->isChecked()){
		QString str = m_leFilte -> text();
		m_leFilte->setEnabled(false);
//		strFilter = m_strDisplay;
		QStringList list = strFilter.split("\n");
		strFilter = "";
		QStringList listSub;
		for(int i=0;i<list.length();i++){
			bool ok;
			int filter;
			int filter2;
			listSub = list[i].split(" ");
			listSub[0].replace("<","");
			listSub[0].replace(">","");
			filter = listSub[0].toInt(&ok,16);
			if(!m_pcbHexRecv->isChecked()){
				filter2 = str.toInt(&ok,10);
			}
			else{
				filter2 = str.toInt(&ok,16);
			}
			if(filter == filter2)
				strFilter = strFilter+list[i]+"\n";
		}
	}
	else
	{
		m_leFilte->setEnabled(true);
//		strFilter = m_strDisplay;
	}
	if(!m_pcbHexRecv->isChecked())
	{
		m_pteDisplay->setText(hex2Decimal(strFilter));

	}
	else
		m_pteDisplay->setText(strFilter);
	QTextCursor cursor = m_pteDisplay->textCursor();
	cursor.movePosition(QTextCursor::End);
	m_pteDisplay->setTextCursor(cursor);
}

QString TQCanDebugger::hex2Decimal(QString str){
	QStringList strHex = str.split("\n");
	QString strReturn = "";
	bool b = false;
	for(int i=0;i<(strHex.length()-1);i++)
	{
		QStringList strHexSub = strHex[i].split(" ");
		if(strHexSub[0].contains("<"))
		{
			strHexSub[0].replace("<","");
			strHexSub[0].replace(">","");
			strHexSub[1].replace("[","");
			strHexSub[1].replace("]","");
			b = true;
		}
		for(int j = 0;j<(strHexSub.length()-1);j++){
			bool ok;
			int iTmp = strHexSub[j].toInt(&ok,16);
			QString strTmp = QString::number(iTmp, 10);
			if(j==0&&b){
				strReturn = strReturn + "<";
				strReturn = strReturn + strTmp;
				strReturn = strReturn + ">";
				strReturn = strReturn + " ";
			}
			else if(j==1)
				strReturn = strReturn +"[" + strTmp + "]" + " ";
			else if(j == (strHexSub.length()-2))
				strReturn = strReturn + strTmp + "\n";
			else
				strReturn = strReturn + strTmp + " ";
		}
	}
	return strReturn;
}
void TQCanDebugger::cbHexSendClicked(){
	QString str = m_leSend->toPlainText();
	QStringList List = str.split("\n");
	str = "";
	for(int j = 0;j<List.length();j++)
	{
		QStringList list = List[j].trimmed().simplified().split(" ");
		int n = list.length();
		if(n>9)
			n=9;
		if(m_pcbHexSend->isChecked())
		{
			for(int i = 0;i<n;i++){
				bool ok;
				int iTmp = list[i].toInt(&ok,10);
				QString strTmp = QString::number(iTmp, 16);
				str = str + strTmp;
				if(i != (n-1))
					str = str + " ";
			}
		}else{
			for(int i = 0;i<n;i++){
				bool ok;
				int iTmp = list[i].toInt(&ok,16);
				QString strTmp = QString::number(iTmp, 10);
				str = str + strTmp;
				if(i != (n-1))
					str = str + " ";
			}
		}
		if(j!= (List.length()-1))
			str = str + "\n";
	}
	m_leSend->setText(str);
}
void TQCanDebugger::pbKeyShowHide() {
    //((TQInputMethod *) im)->setVisible(true);
}
