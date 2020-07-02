#pragma once

#include <QtWidgets/QWidget>
#include <QList>
#include <QtWidgets/QPushButton>
#include "ui_pagewidget.h"

class PageWidget : public QWidget
{
	Q_OBJECT

public:
	PageWidget(QWidget *parent = Q_NULLPTR);
	~PageWidget();
	int getBlockSize() const;
	int getMaxPage() const;
	int getCurrentPage() const;

	// �������ֻ��Ҫ������������������
	void setMaxPage(int maxPage);   // ����ҳ���ı�ʱ����
	void setCurrentPage(int currentPage, bool signalEmitted = false); // �޸ĵ�ǰҳʱ����

protected:
	virtual bool eventFilter(QObject* watched, QEvent* e);
	void setCurrentPageColor(int page);

signals:
	void signal_currentPageChanged(int page);

private:
	void setBlockSize(int blockSize);
	void updatePageLabels();
	void initialize();
private:
	Ui::PageWidget ui;

	int blockSize;
	int maxPage;
	int currentPage;
	QList<QPushButton*>* pageLabels;

	
};
