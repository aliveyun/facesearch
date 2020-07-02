#pragma once
#include <string>
#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>
#include <QtCore/qstring.h>
#include <QtCore/QBuffer>
#include <QtCore/QVariant>
#include <QTextCodec>
#if defined(__MINGW32__) || defined(_UWIN)
#include <unistd.h>
#else
typedef int pid_t;
#endif
//#include <unistd.h>
QString get_appdataPath();
QString get_appdata_fullPath();
QPixmap Base64_To_Image(QByteArray bytearray, QString SavePath);
QString get_appName();
QByteArray Image_To_Base64(QImage* image);
bool isDirExist_Q(QString fullPath);
QStringList addSubFolderImages(QString path);
QString GToUQString(const std::string& cstr);
std::string UToGString(const QString& qstr);