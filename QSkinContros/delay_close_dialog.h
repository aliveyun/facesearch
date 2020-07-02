#pragma once

#include <QObject>
#include <QTimer>
#include "base_dialog.h"
class delay_close_dialog : public base_dialog
{
	Q_OBJECT

public:
	delay_close_dialog(QWidget* parent = Q_NULLPTR);
	virtual~delay_close_dialog();
	void setCenter();

	virtual void accept();
	virtual void reject();
	int getExec();
	bool eventFilter(QObject* o, QEvent* e);

public Q_SLOTS:

	virtual int exec();
private:
	QTimer* m_pTimer;
	int _type;
};
