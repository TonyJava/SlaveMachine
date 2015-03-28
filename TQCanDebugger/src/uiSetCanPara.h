#ifndef  uiSetCanPara_H
#define  uiSetCanPara_H

#include <QtGui/QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include<QComboBox>
#include <QProcess>
#include <QLineEdit>
#include <QCheckBox>

class  uiSetCanPara : public QDialog
{
    Q_OBJECT

public:
     uiSetCanPara(QWidget *parent = 0);
    ~ uiSetCanPara();
public slots:
	void pbCancelClicked();
	void pbConfirmClicked();
	signals:
	void stateChanged();
public:
	QComboBox *cbCan;
	QComboBox *cbMode;
	QLineEdit *leRate;
	QCheckBox *cbTest;
//	QLineEdit *lePacketId;

	QString m_strCan;
	QString m_strMode;
	QString m_strRate;
	bool m_bTest;
//	QString m_strPacketID;
private:
	int m_iWidth;
	int m_iHeight;
	QPushButton *pbCancel;
	QPushButton *pbConfirm;
	QLabel *lbCan;
	QLabel *lbRate;
	QLabel *lbMode;
//	QLabel *lbPacketId;
};

#endif //  uiSetCanPara_H
