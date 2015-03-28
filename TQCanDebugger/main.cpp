#include "tqcandebugger.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    TQCanDebugger *w;
    bool bShowKey=false;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "EmbedSky") == 0)
		{
			w = new TQCanDebugger(0, 1);
			bShowKey=true;
			break;
		}
	}
	if(!bShowKey)
		w = new TQCanDebugger(0, 0);
    w->showFullScreen();
    return a.exec();
}
