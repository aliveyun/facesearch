
#include "config.h"
#include <QTextCodec>
Config::Config()
{
   m_spConfig = std::make_shared<QSettings>("Config.ini",QSettings::IniFormat);
   m_spConfig->setIniCodec("UTF8");
}

//QString Config::getCommon(QString key)
//{
//
//}
//void Config::setCommon(QString value ,QString key)
//{
//
//}

QString Config::getUiView()
{
	QString file = m_spConfig->value("/Ui/Type").toString();
	if (file.isEmpty())
	{
		file = QStringLiteral("right");
	}
	return file;
}
QString Config::getDeviceIP()
{
	return m_spConfig->value("/Device/DeviceIP").toString();
}

QString Config::getRtspUrl()
{
	return m_spConfig->value("/Device/RTSP").toString();
}
QString Config::getTime()
{
	return m_spConfig->value("/Face/Time").toString();
}
void Config::setTime(QString& time)
{
	m_spConfig->setValue("/Face/Time", time);
}
void Config::setTemperaturAbnormal(int num)
{
	 m_spConfig->setValue("/Face/Abnormal", num);
}
int  Config::getTemperaturAbnormal()
{
	return m_spConfig->value("/Face/Abnormal").toInt();
}


void Config::setTemperaturNormal(int num)
{
	m_spConfig->setValue("/Face/Normal", num);
}
int  Config::getTemperaturNormal()
{
	return m_spConfig->value("/Face/Normal").toInt();
}


void Config::setNoMask(int num)
{
	m_spConfig->setValue("/Face/NoMask", num);
}
int  Config::getNoMask()
{
	return m_spConfig->value("/Face/NoMask").toInt();
}

void Config::setMask(int num)
{
	m_spConfig->setValue("/Face/Mask", num);
}
int  Config::getMask()
{
	return m_spConfig->value("/Face/Mask").toInt();
}

void Config::setUnRegistered(int num)
{
	m_spConfig->setValue("/Face/UnRegistered", num);
}
int  Config::getUnRegistered()
{
	return m_spConfig->value("/Face/UnRegistered").toInt();
}

void Config::setRegistered(int num)
{
	m_spConfig->setValue("/Face/Registered", num);
}
int  Config::getRegistered()
{
	return m_spConfig->value("/Face/Registered").toInt();
}
void  Config::setTotal(int num)
{
	m_spConfig->setValue("/Face/Total", num);
}
int   Config::getTotal()
{
	return m_spConfig->value("/Face/Total").toInt();
}
QString Config::getSaveFacePatch()
{
	QString file= m_spConfig->value("/Face/Patch").toString();
	if (file.isEmpty())
	{
		file = "d:/face/";
	}
	return file;
}

QString GBK2UTF8(const QString& str)
{
	QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
	return utf8->toUnicode(str.toUtf8());
}
QString UTF82GBK(const QString& str)
{
	QTextCodec* gbk = QTextCodec::codecForName("GB18030");
	return gbk->toUnicode(str.toLocal8Bit());
}

QString Config::getFengLi()
{
	QString file = GBK2UTF8( m_spConfig->value("/Weather/FengLi").toString());
	if (file.isEmpty())
	{
		file = QStringLiteral("南风3级");
	}
	return file;
}
QString Config::getTianQiType()
{
	QString file = m_spConfig->value("/Weather/TianQiType").toString();
	if (file.isEmpty())
	{
		file = QStringLiteral("小雨");
	}

	return file;
}
QString Config::getCurrentWendu()
{
	QString file = m_spConfig->value("/Weather/Wendu").toString();
	if (file.isEmpty())
	{
		file = "29";
	}
	return file;
}
QString Config::getMySqlIP()
{
	QString file = m_spConfig->value("/MySql/IP").toString();
	if (file.isEmpty())
	{
		file = "127.0.0.1";
	}
	return file;
}
int Config::getMySqlPort()
{
	QString file = m_spConfig->value("/MySql/Port").toString();
	if (file.isEmpty())
	{
		file = "3306";
	}
	return file.toInt();
}
QString Config::getLocalAddress()
{
	QString file = m_spConfig->value("/Local/Address").toString();
	if (file.isEmpty())
	{
		file = QStringLiteral("盈峰中心一楼正门");
	}
	return file;
}
QString Config::getUser()
{
	return  m_spConfig->value("/User/User").toString();
}
void Config::setUser(QString& user)
{
	m_spConfig->setValue("/User/User", user);
}
QString Config::getPassword() {
	return  m_spConfig->value("/User/Password").toString();
}
void Config::setPassword(QString& password)
{
	m_spConfig->setValue("/User/Password", password);
}
QString Config::getAlarmFilePath()
{
	QString file = m_spConfig->value("/Alarm/Sound").toString();
	if (file.isEmpty())
	{
		//file = QStringLiteral("c://camera");
		file = QStringLiteral("alarmSound");
	}
	return file;


}