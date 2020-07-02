#include "yh_global.h"

#include <QtWidgets/QApplication>
#include <QtCore/qdir.h>
#include <QtCore/QProcess>
#include <qdebug.h>
#include "qobject.h"
#include "qobjectdefs.h"

#include <QCryptographicHash>

#include <QList>  

#include <QtCore/QDirIterator>

#if defined(_MSC_VER)
#define strcasecmp _stricmp
#endif

QString get_appdataPath()
{
	return QProcessEnvironment::systemEnvironment().value("APPDATA");
}

QString get_appdata_fullPath()
{
	QString dataPath = get_appdataPath();
	//QString dataPath = PATH_CONFIG;// get_appdataPath();
	//dataPath.replace("\\", "/");
	return  QString("%1/%2").arg(dataPath).arg(get_appName());
}
QString get_appName()
{

	QString application_path = QCoreApplication::applicationFilePath();
	application_path.replace("/", "\\");
	QDir sourceDir(application_path);
	application_path = sourceDir.dirName();
	application_path.replace(".exe", "");
	//return application_path.mid(application_path.fin)
	return application_path;
}
bool isDirExist_Q(QString fullPath)
{
	QDir dir(fullPath);
	if (dir.exists())
	{
		return true;
	}
	else
	{
		bool ok = dir.mkpath(fullPath);//创建多级目录
		return ok;
	}
}
QPixmap Base64_To_Image(QByteArray bytearray, QString SavePath)
{
	QByteArray Ret_bytearray;
	Ret_bytearray = QByteArray::fromBase64(bytearray);
	QBuffer buffer(&Ret_bytearray);
	buffer.open(QIODevice::WriteOnly);
	QPixmap imageresult;
	imageresult.loadFromData(Ret_bytearray);
	if (SavePath != "")
	{
		SavePath.replace("\\", "/");
		qDebug() << "save";
		bool b = imageresult.save(SavePath);
		if (b)
		{
			qDebug() << "save s";
		}
		else
		{
			qDebug() << "save f";
		}
	}
	return imageresult;
}
 QByteArray Image_To_Base64(QImage* image)
{

	QByteArray ba;
	QBuffer buf(&ba);
	image->save(&buf, "jpg");

	QByteArray hexed = ba.toBase64();
	buf.close();
	return hexed;
}
 QStringList addSubFolderImages(QString path)
 {
	 //判断路径是否存在
	 QDir dir(path);
	 if (!dir.exists())
	 {
		 return QStringList();
	 }
	 //获取所选文件类型过滤器
	 QStringList filters;
	 //文件过滤
	  filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png")<<QString("*.tiff")<<QString("*.gif")<<QString("*.bmp");
		 //定义迭代器并设置过滤器
	 QDirIterator dir_iterator(path,
		 filters,
		 QDir::Files | QDir::NoSymLinks,
		 QDirIterator::Subdirectories);
	 QStringList string_list;
	 while (dir_iterator.hasNext())
	 {
		 dir_iterator.next();
		 QFileInfo file_info = dir_iterator.fileInfo();
		 QString absolute_file_path = file_info.absoluteFilePath();
		 QString file_name = file_info.baseName();
		 absolute_file_path.append("@@");
		 absolute_file_path.append(file_name);
		 
		 string_list.append(absolute_file_path);
	 }
	 return string_list;
 }

 QString GToUQString(const std::string& cstr)
 {
	 QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
	 if (!pCodec) return "";

	 QString qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
	 return qstr;
 }
 std::string UToGString(const QString& qstr)
 {
	 QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
	 if (!pCodec) return "";

	 QByteArray arr = pCodec->fromUnicode(qstr);
	 std::string cstr = arr.data();
	 return cstr;
 }