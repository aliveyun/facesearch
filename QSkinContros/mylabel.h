

#include <QtWidgets/QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{

	Q_OBJECT
public:
	explicit MyLabel(QWidget* parent = 0);	// 构造函数声明
protected:
	virtual void mouseReleaseEvent(QMouseEvent* ev);  // 声明鼠标左键点击事件
signals:
	void clicked(void); // 声明鼠标左击中信号

};
