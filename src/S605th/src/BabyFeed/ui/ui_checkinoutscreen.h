/********************************************************************************
** Form generated from reading UI file 'checkinoutscreen.ui'
**
** Created: Fri 31. Dec 04:54:58 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKINOUTSCREEN_H
#define UI_CHECKINOUTSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckInOutScreen
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *lButton;
    QPushButton *bButton;
    QPushButton *rButton;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *CheckInOutScreen)
    {
        if (CheckInOutScreen->objectName().isEmpty())
            CheckInOutScreen->setObjectName(QString::fromUtf8("CheckInOutScreen"));
        CheckInOutScreen->resize(360, 640);
        verticalLayout_2 = new QVBoxLayout(CheckInOutScreen);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lButton = new QPushButton(CheckInOutScreen);
        buttonGroup = new QButtonGroup(CheckInOutScreen);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(lButton);
        lButton->setObjectName(QString::fromUtf8("lButton"));
        QFont font;
        font.setPointSize(16);
        lButton->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/breastfeeding-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        lButton->setIcon(icon);
        lButton->setIconSize(QSize(38, 38));
        lButton->setCheckable(true);
        lButton->setChecked(true);
        lButton->setFlat(false);

        horizontalLayout_3->addWidget(lButton);

        bButton = new QPushButton(CheckInOutScreen);
        buttonGroup->addButton(bButton);
        bButton->setObjectName(QString::fromUtf8("bButton"));
        bButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/baby_bottle.png"), QSize(), QIcon::Normal, QIcon::Off);
        bButton->setIcon(icon1);
        bButton->setIconSize(QSize(38, 38));
        bButton->setCheckable(true);

        horizontalLayout_3->addWidget(bButton);

        rButton = new QPushButton(CheckInOutScreen);
        buttonGroup->addButton(rButton);
        rButton->setObjectName(QString::fromUtf8("rButton"));
        rButton->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/breastfeeding-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        rButton->setIcon(icon2);
        rButton->setIconSize(QSize(38, 38));
        rButton->setCheckable(true);

        horizontalLayout_3->addWidget(rButton);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lcdNumber = new QLCDNumber(CheckInOutScreen);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(300, 120));
        lcdNumber->setSizeIncrement(QSize(0, 0));
        lcdNumber->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(8);
        lcdNumber->setFont(font1);
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setLineWidth(1);
        lcdNumber->setNumDigits(5);
        lcdNumber->setDigitCount(5);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(0));

        horizontalLayout->addWidget(lcdNumber);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(CheckInOutScreen);

        QMetaObject::connectSlotsByName(CheckInOutScreen);
    } // setupUi

    void retranslateUi(QWidget *CheckInOutScreen)
    {
        CheckInOutScreen->setWindowTitle(QApplication::translate("CheckInOutScreen", "Form", 0, QApplication::UnicodeUTF8));
        lButton->setText(QString());
        bButton->setText(QString());
        rButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CheckInOutScreen: public Ui_CheckInOutScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKINOUTSCREEN_H
