#include "mylabel.h"


MyLabel::MyLabel(QWidget* parent) :QLabel(parent)
{

}

// 重写鼠标释放时间 mouseReleaseEvent()
void MyLabel::mouseReleaseEvent(QMouseEvent* ev)
{
	Q_UNUSED(ev)
	if (ev->button() == Qt::LeftButton)
	{
		emit clicked();	// 发射信号
	}
}
