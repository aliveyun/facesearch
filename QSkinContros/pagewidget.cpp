#include "pagewidget.h"
#include <QtGlobal>
#include <QtWidgets/QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>
#include <QtGui/qvalidator.h>
PageWidget::PageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setBlockSize(blockSize);
	initialize();

	maxPage = 0;
	setMaxPage(1);
}

PageWidget::~PageWidget()
{
}
bool PageWidget::eventFilter(QObject* watched, QEvent* e) {
	if (e->type() == QEvent::MouseButtonRelease) {
		int page = -1;
		if (watched == ui.previousPageLabel) { page = getCurrentPage() - 1; }

		if (watched == ui.nextPageLabel) { page = getCurrentPage() + 1; }

		for (int i = 0; i < pageLabels->count(); ++i) {
			if (watched == pageLabels->at(i)) {
				page = pageLabels->at(i)->text().toInt();

				break;
			}
		}

		if (-1 != page) {
			setCurrentPage(page, true);
			return true;
		}
	}

	if (watched == ui.pageLineEdit && e->type() == QEvent::KeyRelease) {
		QKeyEvent* ke = static_cast<QKeyEvent*>(e);
		if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return) {
			setCurrentPage(ui.pageLineEdit->text().toInt(), true);
			//setMaxPage(ui->pageLineEdit->text().toInt()); // �������ɶ��ҳ��
			return true;
		}
	}

	return QWidget::eventFilter(watched, e);
}

int PageWidget::getBlockSize() const {
	return blockSize;
}

int PageWidget::getMaxPage() const {
	return maxPage;
}

int PageWidget::getCurrentPage() const {
	return currentPage;
}

void PageWidget::setMaxPage(int page) {
	page = qMax(page, 1);

	if (maxPage != page) {
		this->maxPage = page;
		this->currentPage = 1;
		updatePageLabels();

	}
	this->currentPage = 1;
	setCurrentPageColor(1);
}
void PageWidget::setCurrentPageColor(int page) {

	for (int i = 0; i < pageLabels->count(); i++) {
		QPushButton* label = pageLabels->at(i);
		int n = label->text().toInt();
		if (n == page)
		{
			label->setChecked(true);//
		}
		else
		{
			label->setChecked(false);//
		}


	}
}

void PageWidget::setCurrentPage(int page, bool signalEmitted) {

	page = qMax(page, 1);
	page = qMin(page, maxPage);

	for (int i = 0; i < pageLabels->count(); i++) {
		QPushButton* label = pageLabels->at(i);
		int n = label->text().toInt();
		if (n == page)
		{
			label->setChecked(true);//
		}
		else
		{
			label->setChecked(false);//
		}


	}

	if (page != this->currentPage) {
		this->currentPage = page;
		updatePageLabels();

		if (signalEmitted) {
			printf("signal_currentPageChanged  %d \n", page);
			emit signal_currentPageChanged(page);
		}
	}
}

void PageWidget::setBlockSize(int blockSize) {
	// Ϊ�˱��ڼ���, block size ����������, ����СΪ3
	blockSize = qMax(blockSize, 3);
	if (blockSize % 2 == 0) {
		++blockSize;
	}
	this->blockSize = blockSize;
}

// ��ʼ��ҳ���labels
// �ֳ���������, ��...��...��
void PageWidget::initialize() {
	ui.pageLineEdit->installEventFilter(this);
	ui.pageLineEdit->setValidator(new QIntValidator(1, 10000000, this));

	ui.nextPageLabel->setProperty("page", "true");
	ui.previousPageLabel->setProperty("page", "true");
	ui.nextPageLabel->installEventFilter(this);
	ui.previousPageLabel->installEventFilter(this);

	pageLabels = new QList<QPushButton*>();

	QHBoxLayout* leftLayout = new QHBoxLayout();
	QHBoxLayout* centerLayout = new QHBoxLayout();
	QHBoxLayout* rightLayout = new QHBoxLayout();
	leftLayout->setContentsMargins(0, 0, 0, 0);
	leftLayout->setSpacing(0);
	centerLayout->setContentsMargins(0, 0, 0, 0);
	centerLayout->setSpacing(0);
	rightLayout->setContentsMargins(0, 0, 0, 0);
	rightLayout->setSpacing(0);
	QButtonGroup* pButtonGroup = new QButtonGroup(this);
	for (int i = 0; i < blockSize * 3; ++i) {
		QPushButton* label = new QPushButton(QString::number(i + 1));

		label->setMinimumSize(35, 35);
		label->setMaximumSize(35, 35);
		//label->setScaledContents(true);   //�Զ����ı�һ���ĸ߶�

		/////////////////////
		label->setCheckable(true);
		label->setChecked(false);//ֻ������һ��
		if (i == 0)
			label->setChecked(true);//ֻ������һ��
		//label->setAutoExclusive(true);
			//////////////////
			//label->setStyleSheet("QPushButton:checked{color:rgb(34,255,255);border-image: url(:/navbar/bar_org_down);}");
		//label->setStyleSheet("QPushButton{color:rgb(37, 143, 173);background:transparent;color:white;font-weight:bold;font-size:16px;}QPushButton:hover{color:rgb(37,143,173);border-image: url(:/navbar/bar_org_down);}QPushButton:checked{color:rgb(34,255,255);border-image: url(:/navbar/bar_org_down);}");
		label->setStyleSheet("QPushButton{background:transparent;color:white;font-weight:bold;font-size:16px;}QPushButton:hover{color:rgb(37,143,173);border-image: url(:/navbar/bar_org_down);}QPushButton:checked{color:rgb(34,255,255);border-image: url(:/navbar/bar_org_down);}");
		//label->setStyleSheet("border: 0.5px solid #B5BCCC;");
		//label->setStyleSheet("QWidget {background:transparent;border:0px;color:white;font-weight:bold;font-size:16px;}");
		//label->setStyleSheet("QWidget{background:#ff0000;} QWidget:hover{background:#00ff00;}");




		pButtonGroup->addButton(label, i);



		label->setProperty("page", "true");
		label->installEventFilter(this);

		pageLabels->append(label);

		if (i < blockSize) {
			leftLayout->addWidget(label);
		}
		else if (i < blockSize * 2) {
			centerLayout->addWidget(label);
		}
		else {
			rightLayout->addWidget(label);
		}
	}

	ui.leftPagesWidget->setLayout(leftLayout);
	ui.centerPagesWidget->setLayout(centerLayout);
	ui.rightPagesWidget->setLayout(rightLayout);
}

void PageWidget::updatePageLabels() {
	ui.leftSeparateLabel->hide();
	ui.rightSeparateLabel->hide();

	//for (int i = 0; i < pageLabels->count(); i ++) {
	//	QPushButton *label = pageLabels->at(i);
	//	label->setChecked(false);//ֻ������һ��
	//	
	//}
	if (maxPage <= blockSize * 3) {
		for (int i = 0; i < pageLabels->count(); i += 1) {
			QPushButton* label = pageLabels->at(i);

			if (i < maxPage) {
				label->setText(QString::number(i + 1));
				label->show();
				label->setChecked(false);//ֻ������һ��
			}
			else {
				label->hide();
				label->setChecked(false);//ֻ������һ��

			}

			if (currentPage - 1 == i) {
				label->setProperty("currentPage", "true");
				label->setChecked(false);//ֻ������һ��
			}
			else {
				label->setProperty("currentPage", "false");
				label->setChecked(false);//ֻ������һ��
			}

			//label->setStyleSheet("/**/");
		}
		return;
	}

	// �������ΪmaxPageNumber����blockSize * 3, ���е�ҳ��label��Ҫ��ʾ
	// c Ϊ currentPage
	// n Ϊ block size
	// m Ϊ maxPage

	// 1. c �� [1, n + n/2 + 1]: ��ʾǰ n * 2 ��, �� n ��: ֻ��ʾ�ұߵķָ���
	// 2. c �� [m - n - n/2, m]: ��ʾǰ n ��, �� n * 2 ��: ֻ��ʾ��ߵķָ���
	// 3. ��ʾ[1, n], [c - n/2, c + n/2], [m - 2*n + 1, m]: �����ָ�������ʾ
	//for (int i = 0; i < pageLabels->count(); i++) {
	//	QPushButton *label = pageLabels->at(i);
	//	label->setChecked(false);//ֻ������һ��

	//}
	int c = currentPage;
	int n = blockSize;
	int m = maxPage;
	int centerStartPage = 0;

	if (c >= 1 && c <= n + n / 2 + 1) {
		// 1. c �� [1, n + n/2 + 1]: ��ʾǰ n * 2 ��, �� n ��: ֻ��ʾ�ұߵķָ���
		centerStartPage = n + 1;
		ui.rightSeparateLabel->show();
	}
	else if (c >= m - n - n / 2 && c <= m) {
		// 2. c �� [m - n - n/2, m]: ��ʾǰ n ��, �� n * 2 ��: ֻ��ʾ��ߵķָ���
		centerStartPage = m - n - n + 1;
		ui.leftSeparateLabel->show();
	}
	else {
		// 3. ��ʾ[1, n], [c - n/2, c + n/2], [m - n + 1, m]: �����ָ�������ʾ
		centerStartPage = c - n / 2;
		ui.rightSeparateLabel->show();
		ui.leftSeparateLabel->show();
	}

	for (int i = 0; i < n; ++i) {
		pageLabels->at(i)->setText(QString::number(i + 1));                     // ǰ�� n ��
		pageLabels->at(n + i)->setText(QString::number(centerStartPage + i));   // �м� n ��
		pageLabels->at(3 * n - i - 1)->setText(QString::number(m - i));         // ���� n ��
	}

	for (int i = 0; i < pageLabels->count(); ++i) {
		QPushButton* label = pageLabels->at(i);
		int page = label->text().toInt();
		if (page == currentPage) {
			label->setProperty("currentPage", "true");
			label->setChecked(true);//ֻ������һ��
		}
		else {
			label->setProperty("currentPage", "false");
			label->setChecked(false);//ֻ������һ��
		}

		// label->setStyleSheet("/**/");
		label->show();
	}
}
