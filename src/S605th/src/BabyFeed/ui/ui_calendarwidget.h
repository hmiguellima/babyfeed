/********************************************************************************
** Form generated from reading UI file 'calendarwidget.ui'
**
** Created: Fri 31. Dec 04:54:59 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARWIDGET_H
#define UI_CALENDARWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "labelbar.h"

QT_BEGIN_NAMESPACE

class Ui_CalendarWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *prevMonthBtn;
    LabelBar *mesAnoLabel;
    QToolButton *nextMonthBtn;
    QCalendarWidget *calendarWidget;

    void setupUi(QWidget *CalendarWidget)
    {
        if (CalendarWidget->objectName().isEmpty())
            CalendarWidget->setObjectName(QString::fromUtf8("CalendarWidget"));
        CalendarWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(CalendarWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        prevMonthBtn = new QToolButton(CalendarWidget);
        prevMonthBtn->setObjectName(QString::fromUtf8("prevMonthBtn"));
        QFont font;
        font.setPointSize(8);
        prevMonthBtn->setFont(font);

        horizontalLayout_2->addWidget(prevMonthBtn);

        mesAnoLabel = new LabelBar(CalendarWidget);
        mesAnoLabel->setObjectName(QString::fromUtf8("mesAnoLabel"));
        mesAnoLabel->setFont(font);
        mesAnoLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(mesAnoLabel);

        nextMonthBtn = new QToolButton(CalendarWidget);
        nextMonthBtn->setObjectName(QString::fromUtf8("nextMonthBtn"));
        nextMonthBtn->setFont(font);

        horizontalLayout_2->addWidget(nextMonthBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        calendarWidget = new QCalendarWidget(CalendarWidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        QFont font1;
        font1.setPointSize(6);
        calendarWidget->setFont(font1);
        calendarWidget->setAutoFillBackground(true);
        calendarWidget->setGridVisible(true);
        calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarWidget->setNavigationBarVisible(false);

        verticalLayout->addWidget(calendarWidget);


        retranslateUi(CalendarWidget);

        QMetaObject::connectSlotsByName(CalendarWidget);
    } // setupUi

    void retranslateUi(QWidget *CalendarWidget)
    {
        CalendarWidget->setWindowTitle(QApplication::translate("CalendarWidget", "Form", 0, QApplication::UnicodeUTF8));
        prevMonthBtn->setText(QApplication::translate("CalendarWidget", "<", 0, QApplication::UnicodeUTF8));
        mesAnoLabel->setText(QApplication::translate("CalendarWidget", "M\303\252s, Ano", 0, QApplication::UnicodeUTF8));
        nextMonthBtn->setText(QApplication::translate("CalendarWidget", ">", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalendarWidget: public Ui_CalendarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARWIDGET_H
