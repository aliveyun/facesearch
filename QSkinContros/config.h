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
    void setTemperaturAbnormal(int num);//�����쳣
    int  getTemperaturAbnormal();


	void setTemperaturNormal(int num);//��������
	int  getTemperaturNormal();


	void setNoMask(int num);//δ������
	int  getNoMask();

	void setMask(int num);//����
	int  getMask();

	void setUnRegistered(int num);//δע��
	int  getUnRegistered();

	void setRegistered(int num);//ע��
	int  getRegistered();

	void setTotal(int num);//������
	int  getTotal();

	QString getSaveFacePatch();
	QString getFengLi();                //��ȡ�������
	QString getTianQiType();            //��ȡ��������
	QString getCurrentWendu();          //��ȡ��ǰ�¶�


	QString getMySqlIP();
	int getMySqlPort();

	QString getLocalAddress();
private:
    std::shared_ptr<QSettings>  m_spConfig;
};

#endif // CAGORACONFIG_H
