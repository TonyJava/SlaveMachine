#include "uiSetCanPara.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QWindowsXPStyle>

#include <iostream>
using namespace std;
 uiSetCanPara:: uiSetCanPara(QWidget *parent) :
	QDialog(parent, Qt::FramelessWindowHint)
{
	QRect screen_size = QApplication::desktop()->screenGeometry();

	this->setWindowTitle(trUtf8("天嵌科技串口工具V1.0"));
	this->setAutoFillBackground(true);

	QPixmap pixmap("/opt/PDA/app/images/background.jpg");
	QPalette palette;
	palette.setBrush(backgroundRole(), QBrush(pixmap));
	setPalette(palette);
	m_strCan = "can0";
	m_strMode = "普通模式";
	m_strRate = "50000";

	m_bTest = true;
//	m_strPacketID = "01";

	QPixmap pix;

	pbConfirm = new QPushButton();
	pbConfirm->setFixedSize(70 , 32 );
	pbConfirm->setIconSize(QSize(70 , 32 ));
	pix.load("/opt/PDA/app/images/confirm.png", 0, Qt::AutoColor);
	pix = pix.scaled(70 , 32 , Qt::IgnoreAspectRatio);//图片大小
	pbConfirm->setIcon(QIcon(pix));

	pbCancel = new QPushButton();
	pbCancel->setFixedSize(70 , 32 );
	pbCancel->setIconSize(QSize(70 , 32 ));
	pix.load("/opt/PDA/app/images/cancel.png", 0, Qt::AutoColor);
	pix = pix.scaled(70 , 32 , Qt::IgnoreAspectRatio);//图片大小
	pbCancel->setIcon(QIcon(pix));

	QStringList list;
	list.append("can0");
	list.append("can1");
/*	list.append("can2");
	list.append("can3");*/

	cbCan = new QComboBox();
	cbCan->addItems(list);
	cbCan->setCurrentIndex(0);

	list.clear();
	list.append(trUtf8("普通模式"));
	list.append(trUtf8("回环模式"));
	list.append(trUtf8("仅监听模式"));

	cbMode = new QComboBox();
	cbMode->addItems(list);
	cbMode->setCurrentIndex(0);

	cbTest = new QCheckBox(trUtf8("自发收"));
	cbTest->setChecked(true);

	QRegExp rx("-?\\d{0,9}");
	QRegExpValidator *exp = new QRegExpValidator(rx, this);

	leRate = new QLineEdit(trUtf8("50000"));
	leRate->setValidator(exp);

	cbCan->setMinimumWidth(108);
	cbCan->setMinimumHeight(32);
	cbMode->setMinimumWidth(108);
	cbMode->setMinimumHeight(32);
	leRate->setMinimumWidth(108);
	leRate->setMinimumHeight(32);

	lbCan = new QLabel(trUtf8("端口  ："));
	lbMode = new QLabel(trUtf8("模式  ："));
	lbRate = new QLabel(trUtf8("波特率："));;

	QHBoxLayout *comLayOut = new QHBoxLayout;
	comLayOut->addStretch(0);
	comLayOut->addWidget(lbCan);
	comLayOut->addStretch(0);
	comLayOut->addWidget(cbCan);
	comLayOut->addStretch(0);

	QHBoxLayout *modeLayOut = new QHBoxLayout;
	modeLayOut->addStretch(0);
	modeLayOut->addWidget(lbMode);
	modeLayOut->addStretch(0);
	modeLayOut->addWidget(cbMode);
	modeLayOut->addStretch(0);

	QHBoxLayout *rateLayOut = new QHBoxLayout;
	rateLayOut->addStretch(0);
	rateLayOut->addWidget(lbRate);
	rateLayOut->addStretch(0);
	rateLayOut->addWidget(leRate);
	rateLayOut->addStretch(0);


	QHBoxLayout *bottomLayOut = new QHBoxLayout;
	bottomLayOut->addStretch(0);
	bottomLayOut->addWidget(pbConfirm);
	bottomLayOut->addSpacing(60);
	bottomLayOut->addWidget(pbCancel);
	bottomLayOut->addStretch(0);

	QHBoxLayout *cbTestLayOut = new QHBoxLayout;
	cbTestLayOut->addStretch(0);
	cbTestLayOut->addWidget(cbTest);
	cbTestLayOut->addStretch(0);


	QVBoxLayout *centralLayOut = new QVBoxLayout;
	centralLayOut->addLayout(comLayOut);
	centralLayOut->addLayout(modeLayOut);
	centralLayOut->addLayout(rateLayOut);
	centralLayOut->addSpacing(20);
	centralLayOut->addLayout(cbTestLayOut);
//	centralLayOut->addLayout(dataLayOut);

	QHBoxLayout *hLayOut = new QHBoxLayout;
	hLayOut->addStretch(0);
	hLayOut->addLayout(centralLayOut);
	hLayOut->addStretch(0);

	QVBoxLayout *vLayOut = new QVBoxLayout;
	vLayOut->addStretch(0);
	vLayOut->addLayout(hLayOut);
	vLayOut->addSpacing(50);
	vLayOut->addLayout(bottomLayOut);
	vLayOut->addStretch(0);

	setLayout(vLayOut);

	this->resize(480,240);
	pbConfirmClicked();

	connect(pbCancel, SIGNAL(clicked()), this, SLOT(pbCancelClicked()));
	connect(pbConfirm, SIGNAL(clicked()), this, SLOT(pbConfirmClicked()));
}

 uiSetCanPara::~ uiSetCanPara()
{

}
void  uiSetCanPara::pbCancelClicked()
{
	QWidget::hide();
}
//确定按钮
void  uiSetCanPara::pbConfirmClicked()
{
	QStringList list;
	list << m_strCan << "stop" ;
	QProcess *process1 = new QProcess(this);;
	process1 -> execute("canconfig", list);

	m_strCan = cbCan->currentText();
	m_strMode = cbMode->currentText();
	m_strRate = leRate->text();

	switch (cbMode->currentIndex())
	{
	case 0:
		list.clear();
		list << m_strCan << "bitrate" \
				<< m_strRate << "ctrlmode" << "triple-sampling" \
				<< "on" << "listen-only" << "off" << "loopback" << "off";
		break;
	case 1:
		list.clear();
		list << m_strCan << "bitrate" \
				<< m_strRate << "ctrlmode" << "triple-sampling" \
				<< "on" << "listen-only" << "off" << "loopback" << "on";
		break;
	case 2:
		list.clear();
		list << m_strCan << "bitrate" \
				<< m_strRate << "ctrlmode" << "triple-sampling" \
				<< "on" << "listen-only" << "on" << "loopback" << "off";
		break;
	default:
		break;
	}

	QProcess *process2 = new QProcess(this);
	process2 -> execute("canconfig", list);

	list.clear();
	list << m_strCan << "start" ;
	QProcess *process3;
	process3 = new QProcess(this);
	process3->execute("canconfig", list);

	QString str;
	if(cbTest->isChecked()){
		m_bTest = true;
		if(m_strCan.contains("can0"))
			str = "can1";
		else
			str = "can0";
		list.clear();
		list << str << "stop" ;
		QProcess *process4 = new QProcess(this);;
		process1 -> execute("canconfig", list);

		list.clear();
		list << str << "bitrate" \
				<< m_strRate << "ctrlmode" << "triple-sampling" \
				<< "on" << "listen-only" << "off" << "loopback" << "off";
		QProcess *process5 = new QProcess(this);
		process5 -> execute("canconfig", list);

		list.clear();
		list << str << "start" ;
		QProcess *process6;
		process6 = new QProcess(this);
		process6->execute("canconfig", list);
	}
	else
	{
		m_bTest = false;
		if(m_strCan.contains("can0"))
			str = "can1";
		else
			str = "can0";
		list.clear();
		list << str << "stop" ;
		QProcess *process4 = new QProcess(this);;
		process1 -> execute("canconfig", list);
	}

	emit stateChanged();

	/*if (!f.exists())
	{
		QMessageBox::warning(this, trUtf8("提示"), trUtf8("串口不存在！"),
				QMessageBox::Ok);
		return;
	}*/
}
