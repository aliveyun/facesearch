#include "mylabel.h"


MyLabel::MyLabel(QWidget* parent) :QLabel(parent)
{

}

// ��д����ͷ�ʱ�� mouseReleaseEvent()
void MyLabel::mouseReleaseEvent(QMouseEvent* ev)
{
	Q_UNUSED(ev)
	if (ev->button() == Qt::LeftButton)
	{
		emit clicked();	// �����ź�
	}
}
