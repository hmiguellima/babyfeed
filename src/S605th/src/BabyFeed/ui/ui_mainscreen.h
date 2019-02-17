/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created: Fri 31. Dec 04:54:58 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCREEN_H
#define UI_MAINSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "labelbar.h"

QT_BEGIN_NAMESPACE

class Ui_MainScreen
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QWidget *babyContainer;
    QVBoxLayout *babyLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *prevDayButton;
    LabelBar *currentDateLabel;
    QToolButton *nextDayButton;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QPushButton *checkInOutButton;
    QPushButton *manualButton;
    QPushButton *statsButton;

    void setupUi(QWidget *MainScreen)
    {
        if (MainScreen->objectName().isEmpty())
            MainScreen->setObjectName(QString::fromUtf8("MainScreen"));
        MainScreen->resize(360, 640);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainScreen->sizePolicy().hasHeightForWidth());
        MainScreen->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(MainScreen);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(MainScreen);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 356, 636));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        babyContainer = new QWidget(scrollAreaWidgetContents);
        babyContainer->setObjectName(QString::fromUtf8("babyContainer"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(babyContainer->sizePolicy().hasHeightForWidth());
        babyContainer->setSizePolicy(sizePolicy1);
        babyContainer->setMinimumSize(QSize(0, 175));
        babyContainer->setMaximumSize(QSize(16777215, 175));
        babyLayout = new QVBoxLayout(babyContainer);
        babyLayout->setSpacing(0);
        babyLayout->setContentsMargins(0, 0, 0, 0);
        babyLayout->setObjectName(QString::fromUtf8("babyLayout"));

        verticalLayout_2->addWidget(babyContainer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        prevDayButton = new QToolButton(scrollAreaWidgetContents);
        prevDayButton->setObjectName(QString::fromUtf8("prevDayButton"));

        horizontalLayout_2->addWidget(prevDayButton);

        currentDateLabel = new LabelBar(scrollAreaWidgetContents);
        currentDateLabel->setObjectName(QString::fromUtf8("currentDateLabel"));
        currentDateLabel->setAutoFillBackground(true);
        currentDateLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(currentDateLabel);

        nextDayButton = new QToolButton(scrollAreaWidgetContents);
        nextDayButton->setObjectName(QString::fromUtf8("nextDayButton"));

        horizontalLayout_2->addWidget(nextDayButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        listView = new QListView(scrollAreaWidgetContents);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setFocusPolicy(Qt::NoFocus);

        verticalLayout_2->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkInOutButton = new QPushButton(scrollAreaWidgetContents);
        checkInOutButton->setObjectName(QString::fromUtf8("checkInOutButton"));
        QFont font;
        font.setPointSize(14);
        checkInOutButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/appointment-new.svg"), QSize(), QIcon::Normal, QIcon::Off);
        checkInOutButton->setIcon(icon);
        checkInOutButton->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(checkInOutButton);

        manualButton = new QPushButton(scrollAreaWidgetContents);
        manualButton->setObjectName(QString::fromUtf8("manualButton"));
        manualButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/accessories-text-editor.svg"), QSize(), QIcon::Normal, QIcon::Off);
        manualButton->setIcon(icon1);
        manualButton->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(manualButton);

        statsButton = new QPushButton(scrollAreaWidgetContents);
        statsButton->setObjectName(QString::fromUtf8("statsButton"));
        statsButton->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/x-office-spreadsheet.svg"), QSize(), QIcon::Normal, QIcon::Off);
        statsButton->setIcon(icon2);
        statsButton->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(statsButton);


        verticalLayout_2->addLayout(horizontalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QWidget *MainScreen)
    {
        prevDayButton->setText(QApplication::translate("MainScreen", "<", 0, QApplication::UnicodeUTF8));
        currentDateLabel->setText(QApplication::translate("MainScreen", "Date", 0, QApplication::UnicodeUTF8));
        nextDayButton->setText(QApplication::translate("MainScreen", ">", 0, QApplication::UnicodeUTF8));
        checkInOutButton->setText(QString());
        manualButton->setText(QString());
        statsButton->setText(QString());
        Q_UNUSED(MainScreen);
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
