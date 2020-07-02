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

	// 其他组件只需要调用这两个函数即可
	void setMaxPage(int maxPage);   // 当总页数改变时调用
	void setCurrentPage(int currentPage, bool signalEmitted = false); // 修改当前页时调用

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
