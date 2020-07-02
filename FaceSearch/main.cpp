#include "FaceSearch.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>
#include <QTextCodec>
#include <QTranslator>
#include <qapplication.h>
int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setAttribute(Qt::AA_MSWindowsUseDirect3DByDefault);
    QApplication a(argc, argv);

	QTextCodec* codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
    FaceSearch w;
    w.show();
    return a.exec();
}
