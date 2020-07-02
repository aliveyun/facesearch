#ifndef CAGORACONFIG_H
#define CAGORACONFIG_H

#include <QSettings>
#include <memory>
class Config
{
public:
    Config();


	QString getCommon();
	void setCommon();

	QString getUiView();

	QString getAlarmFilePath();
	QString getUser();
	void setUser(QString& user);
	QString getPassword();
	void setPassword(QString& password);




    QString getDeviceIP();
    QString getRtspUrl();

	QString getTime();
	void setTime(QString &time);
    void setTemperaturAbnormal(int num);//体温异常
    int  getTemperaturAbnormal();


	void setTemperaturNormal(int num);//体温正常
	int  getTemperaturNormal();


	void setNoMask(int num);//未戴口罩
	int  getNoMask();

	void setMask(int num);//口罩
	int  getMask();

	void setUnRegistered(int num);//未注册
	int  getUnRegistered();

	void setRegistered(int num);//注册
	int  getRegistered();

	void setTotal(int num);//总人数
	int  getTotal();

	QString getSaveFacePatch();
	QString getFengLi();                //获取风向风力
	QString getTianQiType();            //获取天气类型
	QString getCurrentWendu();          //获取当前温度


	QString getMySqlIP();
	int getMySqlPort();

	QString getLocalAddress();
private:
    std::shared_ptr<QSettings>  m_spConfig;
};

#endif // CAGORACONFIG_H
