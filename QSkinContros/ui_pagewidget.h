/********************************************************************************
** Form generated from reading UI file 'pagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEWIDGET_H
#define UI_PAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *previousPageLabel;
    QWidget *leftPagesWidget;
    QLabel *leftSeparateLabel;
    QWidget *centerPagesWidget;
    QLabel *rightSeparateLabel;
    QWidget *rightPagesWidget;
    QLabel *nextPageLabel;
    QLabel *label;
    QLineEdit *pageLineEdit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PageWidget)
    {
        if (PageWidget->objectName().isEmpty())
            PageWidget->setObjectName(QString::fromUtf8("PageWidget"));
        PageWidget->resize(415, 41);
        horizontalLayout = new QHBoxLayout(PageWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(129, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        previousPageLabel = new QLabel(PageWidget);
        previousPageLabel->setObjectName(QString::fromUtf8("previousPageLabel"));

        horizontalLayout->addWidget(previousPageLabel);

        leftPagesWidget = new QWidget(PageWidget);
        leftPagesWidget->setObjectName(QString::fromUtf8("leftPagesWidget"));

        horizontalLayout->addWidget(leftPagesWidget);

        leftSeparateLabel = new QLabel(PageWidget);
        leftSeparateLabel->setObjectName(QString::fromUtf8("leftSeparateLabel"));

        horizontalLayout->addWidget(leftSeparateLabel);

        centerPagesWidget = new QWidget(PageWidget);
        centerPagesWidget->setObjectName(QString::fromUtf8("centerPagesWidget"));

        horizontalLayout->addWidget(centerPagesWidget);

        rightSeparateLabel = new QLabel(PageWidget);
        rightSeparateLabel->setObjectName(QString::fromUtf8("rightSeparateLabel"));

        horizontalLayout->addWidget(rightSeparateLabel);

        rightPagesWidget = new QWidget(PageWidget);
        rightPagesWidget->setObjectName(QString::fromUtf8("rightPagesWidget"));

        horizontalLayout->addWidget(rightPagesWidget);

        nextPageLabel = new QLabel(PageWidget);
        nextPageLabel->setObjectName(QString::fromUtf8("nextPageLabel"));

        horizontalLayout->addWidget(nextPageLabel);

        label = new QLabel(PageWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        pageLineEdit = new QLineEdit(PageWidget);
        pageLineEdit->setObjectName(QString::fromUtf8("pageLineEdit"));
        pageLineEdit->setMinimumSize(QSize(50, 0));
        pageLineEdit->setMaximumSize(QSize(50, 16777215));
        pageLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pageLineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(pageLineEdit);

        label_2 = new QLabel(PageWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(PageWidget);

        QMetaObject::connectSlotsByName(PageWidget);
    } // setupUi

    void retranslateUi(QWidget *PageWidget)
    {
        PageWidget->setWindowTitle(QCoreApplication::translate("PageWidget", "PageWidget", nullptr));
#if QT_CONFIG(tooltip)
        previousPageLabel->setToolTip(QCoreApplication::translate("PageWidget", "\344\270\212\344\270\200\351\241\265", nullptr));
#endif // QT_CONFIG(tooltip)
        previousPageLabel->setText(QCoreApplication::translate("PageWidget", "<<", nullptr));
#if QT_CONFIG(tooltip)
        leftSeparateLabel->setToolTip(QCoreApplication::translate("PageWidget", "\344\270\213\344\270\200\351\241\265", nullptr));
#endif // QT_CONFIG(tooltip)
        leftSeparateLabel->setText(QCoreApplication::translate("PageWidget", "..", nullptr));
#if QT_CONFIG(tooltip)
        rightSeparateLabel->setToolTip(QCoreApplication::translate("PageWidget", "\344\270\213\344\270\200\351\241\265", nullptr));
#endif // QT_CONFIG(tooltip)
        rightSeparateLabel->setText(QCoreApplication::translate("PageWidget", "..", nullptr));
#if QT_CONFIG(tooltip)
        nextPageLabel->setToolTip(QCoreApplication::translate("PageWidget", "\344\270\213\344\270\200\351\241\265", nullptr));
#endif // QT_CONFIG(tooltip)
        nextPageLabel->setText(QCoreApplication::translate("PageWidget", ">>", nullptr));
        label->setText(QCoreApplication::translate("PageWidget", "\347\254\254", nullptr));
        label_2->setText(QCoreApplication::translate("PageWidget", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageWidget: public Ui_PageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEWIDGET_H
