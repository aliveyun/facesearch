

#include <QtWidgets/QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{

	Q_OBJECT
public:
	explicit MyLabel(QWidget* parent = 0);	// ���캯������
protected:
	virtual void mouseReleaseEvent(QMouseEvent* ev);  // ��������������¼�
signals:
	void clicked(void); // �������������ź�

};
