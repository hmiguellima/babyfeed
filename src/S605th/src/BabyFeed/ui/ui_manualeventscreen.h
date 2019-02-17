/********************************************************************************
** Form generated from reading UI file 'manualeventscreen.ui'
**
** Created: Fri 31. Dec 04:54:58 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALEVENTSCREEN_H
#define UI_MANUALEVENTSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "calendarwidget.h"
#include "eventtypepanel.h"

QT_BEGIN_NAMESPACE

class Ui_ManualEventScreen
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    EventTypePanel *eventPanel;
    QTabWidget *tabWidget;
    QWidget *whenTab;
    QVBoxLayout *verticalLayout_3;
    CalendarWidget *startCalendar;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QTimeEdit *timeEdit;
    QLabel *label_2;
    QSpinBox *durationBox;
    QSpacerItem *verticalSpacer;
    QWidget *notesTab;
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *notesStack;
    QWidget *feedingPage;
    QVBoxLayout *verticalLayout_5;
    QPlainTextEdit *notesEdit;
    QWidget *medicinePage;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QLineEdit *drugEdit;
    QLabel *label_6;
    QPlainTextEdit *drugNotesEdit;
    QWidget *scheduleTab;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    CalendarWidget *endCalendar;
    QLabel *label_4;
    QSpinBox *repeatMinBox;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ManualEventScreen)
    {
        if (ManualEventScreen->objectName().isEmpty())
            ManualEventScreen->setObjectName(QString::fromUtf8("ManualEventScreen"));
        ManualEventScreen->resize(360, 640);
        QFont font;
        font.setPointSize(10);
        ManualEventScreen->setFont(font);
        verticalLayout = new QVBoxLayout(ManualEventScreen);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea_2 = new QScrollArea(ManualEventScreen);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 356, 636));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        eventPanel = new EventTypePanel(scrollAreaWidgetContents_2);
        eventPanel->setObjectName(QString::fromUtf8("eventPanel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(eventPanel->sizePolicy().hasHeightForWidth());
        eventPanel->setSizePolicy(sizePolicy);
        eventPanel->setMinimumSize(QSize(0, 80));
        eventPanel->setMaximumSize(QSize(16777215, 80));

        verticalLayout_2->addWidget(eventPanel);

        tabWidget = new QTabWidget(scrollAreaWidgetContents_2);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setPointSize(8);
        tabWidget->setFont(font1);
        whenTab = new QWidget();
        whenTab->setObjectName(QString::fromUtf8("whenTab"));
        verticalLayout_3 = new QVBoxLayout(whenTab);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        startCalendar = new CalendarWidget(whenTab);
        startCalendar->setObjectName(QString::fromUtf8("startCalendar"));
        sizePolicy.setHeightForWidth(startCalendar->sizePolicy().hasHeightForWidth());
        startCalendar->setSizePolicy(sizePolicy);
        startCalendar->setMinimumSize(QSize(0, 270));
        startCalendar->setMaximumSize(QSize(16777215, 270));

        verticalLayout_3->addWidget(startCalendar);

        widget = new QWidget(whenTab);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(16777215, 100));
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        timeEdit = new QTimeEdit(widget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));

        gridLayout->addWidget(timeEdit, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 100));
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        durationBox = new QSpinBox(widget);
        durationBox->setObjectName(QString::fromUtf8("durationBox"));

        gridLayout->addWidget(durationBox, 1, 1, 1, 1);


        verticalLayout_3->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 234, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(whenTab, QString());
        notesTab = new QWidget();
        notesTab->setObjectName(QString::fromUtf8("notesTab"));
        verticalLayout_4 = new QVBoxLayout(notesTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        notesStack = new QStackedWidget(notesTab);
        notesStack->setObjectName(QString::fromUtf8("notesStack"));
        feedingPage = new QWidget();
        feedingPage->setObjectName(QString::fromUtf8("feedingPage"));
        verticalLayout_5 = new QVBoxLayout(feedingPage);
#ifndef Q_OS_MAC
        verticalLayout_5->setSpacing(6);
#endif
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        notesEdit = new QPlainTextEdit(feedingPage);
        notesEdit->setObjectName(QString::fromUtf8("notesEdit"));

        verticalLayout_5->addWidget(notesEdit);

        notesStack->addWidget(feedingPage);
        medicinePage = new QWidget();
        medicinePage->setObjectName(QString::fromUtf8("medicinePage"));
        verticalLayout_6 = new QVBoxLayout(medicinePage);
#ifndef Q_OS_MAC
        verticalLayout_6->setSpacing(6);
#endif
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_5 = new QLabel(medicinePage);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_6->addWidget(label_5);

        drugEdit = new QLineEdit(medicinePage);
        drugEdit->setObjectName(QString::fromUtf8("drugEdit"));

        verticalLayout_6->addWidget(drugEdit);

        label_6 = new QLabel(medicinePage);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_6->addWidget(label_6);

        drugNotesEdit = new QPlainTextEdit(medicinePage);
        drugNotesEdit->setObjectName(QString::fromUtf8("drugNotesEdit"));

        verticalLayout_6->addWidget(drugNotesEdit);

        notesStack->addWidget(medicinePage);

        verticalLayout_4->addWidget(notesStack);

        tabWidget->addTab(notesTab, QString());
        scheduleTab = new QWidget();
        scheduleTab->setObjectName(QString::fromUtf8("scheduleTab"));
        gridLayout_2 = new QGridLayout(scheduleTab);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(6);
        label_3 = new QLabel(scheduleTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        endCalendar = new CalendarWidget(scheduleTab);
        endCalendar->setObjectName(QString::fromUtf8("endCalendar"));
        endCalendar->setMinimumSize(QSize(0, 270));
        endCalendar->setMaximumSize(QSize(16777215, 270));

        gridLayout_2->addWidget(endCalendar, 1, 0, 1, 3);

        label_4 = new QLabel(scheduleTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        repeatMinBox = new QSpinBox(scheduleTab);
        repeatMinBox->setObjectName(QString::fromUtf8("repeatMinBox"));
        repeatMinBox->setMaximum(999);

        gridLayout_2->addWidget(repeatMinBox, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(202, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 1);

        tabWidget->addTab(scheduleTab, QString());

        verticalLayout_2->addWidget(tabWidget);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(scrollArea_2);


        retranslateUi(ManualEventScreen);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ManualEventScreen);
    } // setupUi

    void retranslateUi(QWidget *ManualEventScreen)
    {
        ManualEventScreen->setWindowTitle(QApplication::translate("ManualEventScreen", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ManualEventScreen", "Time:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ManualEventScreen", "Duration (Min):", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(whenTab), QApplication::translate("ManualEventScreen", "When?", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ManualEventScreen", "Drug Name:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ManualEventScreen", "Notes:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(notesTab), QApplication::translate("ManualEventScreen", "About", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ManualEventScreen", "End date:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ManualEventScreen", "Repeat in (Min.):", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(scheduleTab), QApplication::translate("ManualEventScreen", "Schedule", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ManualEventScreen: public Ui_ManualEventScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALEVENTSCREEN_H
