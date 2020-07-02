#include "delay_close_dialog.h"
#include <QtWidgets/qdesktopwidget.h>
#include <QtWidgets/qapplication.h>
delay_close_dialog::delay_close_dialog(QWidget* parent)
	: base_dialog(parent)
	, _type(QDialog::Rejected)
{
	setWindowOpacity(1);
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);
	this->set_hide_title();
	this->set_enable_dialog_move_with_mouse();
	//setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::SubWindow/*| Qt::WindowStaysOnTopHint*/);
	m_pTimer = new QTimer(this);
	connect(m_pTimer, &QTimer::timeout, this, [=]() {/*this->reject(); */m_pTimer->stop(); this->close(); delete this; });

	installEventFilter(this);

}

delay_close_dialog::~delay_close_dialog()
{
}
void delay_close_dialog::setCenter()
{
	move((QApplication::desktop()->width() - width()) / 2, (QApplication::desktop()->height() - height()) / 2);
}
void delay_close_dialog::accept()
{
	_type = QDialog::Accepted;
	//hide();
	setVisible(false);
	m_pTimer->start(28000);
}
int delay_close_dialog::exec()
{
	QDialog::exec();
	return _type;
}
void delay_close_dialog::reject()
{
	_type = QDialog::Rejected;
	//hide();
	setVisible(false);
	m_pTimer->start(18000);
}
int delay_close_dialog::getExec()
{
	return _type;
}
bool delay_close_dialog::eventFilter(QObject* o, QEvent* e)
{
	if (e->type() == QEvent::KeyPress)
	{
		return true;                //½Ø¶Ï°´Å¥µÄ¹¦ÄÜ
	}

	return QWidget::eventFilter(o, e);
}
