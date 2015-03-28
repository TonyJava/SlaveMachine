#ifndef TQCANDEBUGGER_H
#define TQCANDEBUGGER_H

#include <QtGui/QWidget>
#include <QDesktopWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QStatusBar>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <qprocess.h>
#include <QPushButton>
#include <QTextEdit>
#include <QWSInputMethod>
#include <QTextBrowser>
#include "src/ThreadRec.h"
#include "src/uiSetCanPara.h"
#include "TQInputMethod.h"


class TQCanDebugger : public QWidget
{
    Q_OBJECT

public:
    TQCanDebugger(QWidget *parent = 0, bool bKeyShow = 0);
    ~TQCanDebugger();

private:
	QTextBrowser *m_pteDisplay;
//	QTextEdit *m_pteDisplay;
	QTextEdit *m_leSend;
	QString m_strDisplayInput;
	QStatusBar *m_pBar;//状态栏
	QCheckBox *m_pcbHexRecv;//Hex收
	QCheckBox *m_pcbHexSend;//Hex发
	QCheckBox *m_pcbExtendSend;//扩展帧发送
	QCheckBox *m_pcbLoopSend;//自动发送
	QTimer *m_pAutoSend;
	QPushButton *m_pbHelp;

	QCheckBox *m_cbFilte;//过滤
	QLineEdit *m_leFilte;

	QLineEdit *m_leFrame;//自动发送帧数
	QLabel *m_plbUrl;//网站
	QLabel *m_plbRecv;//接收
	QLabel *m_plbSend;//发送
	QLabel *m_plbComStatus;//串口状态
	QPushButton *m_pbClearRecv;//清空接收
	QPushButton *m_pbClearSend;//清空发送
	QPushButton *m_pbClearCount;//清空计数器
//	QPushButton *m_pbSelect;//选择文件
	QPushButton *m_pbSet;//设置
	QPushButton *m_pbSend;//发送

	QPushButton *m_pbKey;
	ThreadRec* m_threadRecv;
	uiSetCanPara* setPara;
	char *m_cptr[10];

	int m_iWidth;
	int m_iHeight;
	int m_iRecvCount;
	int m_iSendCount;
	bool m_bRecv;

	QString m_strDisplay;

	QWSInputMethod* im;

	bool iShowKey;

public slots:
	void ShowCanMsg(QString);
	void pbClearRecvClicked();
	void pbClearSendClicked();
	void pbClearCountClicked();
	void pbSendClicked();
	void Close();
	void pbSetClicked();
	void cbStateChanged();
	void pbHelpClicked();
	void pbKeyShowHide();
	void cbAutoSendClicked();
	void cbDisplay();
	QString hex2Decimal(QString);
	void cbHexSendClicked();
};

#endif // TQCANDEBUGGER_H
