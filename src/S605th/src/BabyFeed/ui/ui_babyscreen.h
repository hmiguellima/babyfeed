/********************************************************************************
** Form generated from reading UI file 'babyscreen.ui'
**
** Created: Fri 31. Dec 04:54:58 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BABYSCREEN_H
#define UI_BABYSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BabyScreen
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *babyTab;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *photoLabel;
    QPushButton *changeFotoButton;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *label;
    QDateEdit *birthdayEdit;
    QLabel *label_2;
    QComboBox *genderBox;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QWidget *alarmsTab;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpinBox *feedIntervalBox;
    QCheckBox *alarmsCheckBox;
    QWidget *notificationsTab;
    QVBoxLayout *verticalLayout_3;
    QListView *contactsListView;

    void setupUi(QWidget *BabyScreen)
    {
        if (BabyScreen->objectName().isEmpty())
            BabyScreen->setObjectName(QString::fromUtf8("BabyScreen"));
        BabyScreen->resize(360, 640);
        QFont font;
        font.setPointSize(9);
        BabyScreen->setFont(font);
        verticalLayout = new QVBoxLayout(BabyScreen);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(BabyScreen);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 356, 636));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setPointSize(8);
        tabWidget->setFont(font1);
        babyTab = new QWidget();
        babyTab->setObjectName(QString::fromUtf8("babyTab"));
        gridLayout = new QGridLayout(babyTab);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        photoLabel = new QLabel(babyTab);
        photoLabel->setObjectName(QString::fromUtf8("photoLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(photoLabel->sizePolicy().hasHeightForWidth());
        photoLabel->setSizePolicy(sizePolicy);
        photoLabel->setMinimumSize(QSize(266, 200));
        photoLabel->setMaximumSize(QSize(266, 200));
        photoLabel->setFrameShape(QFrame::Box);
        photoLabel->setFrameShadow(QFrame::Raised);
        photoLabel->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/baby_icon.jpg")));
        photoLabel->setScaledContents(true);
        photoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(photoLabel);

        changeFotoButton = new QPushButton(babyTab);
        changeFotoButton->setObjectName(QString::fromUtf8("changeFotoButton"));
        changeFotoButton->setFlat(false);

        verticalLayout_2->addWidget(changeFotoButton);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 2);

        nameLabel = new QLabel(babyTab);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        gridLayout->addWidget(nameLabel, 2, 0, 1, 1);

        nameEdit = new QLineEdit(babyTab);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 2, 1, 1, 1);

        label = new QLabel(babyTab);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        birthdayEdit = new QDateEdit(babyTab);
        birthdayEdit->setObjectName(QString::fromUtf8("birthdayEdit"));

        gridLayout->addWidget(birthdayEdit, 3, 1, 1, 1);

        label_2 = new QLabel(babyTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        genderBox = new QComboBox(babyTab);
        genderBox->setObjectName(QString::fromUtf8("genderBox"));
        genderBox->setFrame(true);

        gridLayout->addWidget(genderBox, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        label_4 = new QLabel(babyTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        tabWidget->addTab(babyTab, QString());
        alarmsTab = new QWidget();
        alarmsTab->setObjectName(QString::fromUtf8("alarmsTab"));
        gridLayout_2 = new QGridLayout(alarmsTab);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(alarmsTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_5 = new QLabel(alarmsTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(112, 544, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 2);

        feedIntervalBox = new QSpinBox(alarmsTab);
        feedIntervalBox->setObjectName(QString::fromUtf8("feedIntervalBox"));
        feedIntervalBox->setMaximum(999);

        gridLayout_2->addWidget(feedIntervalBox, 1, 2, 1, 1);

        alarmsCheckBox = new QCheckBox(alarmsTab);
        alarmsCheckBox->setObjectName(QString::fromUtf8("alarmsCheckBox"));
        QFont font2;
        font2.setPointSize(16);
        alarmsCheckBox->setFont(font2);
        alarmsCheckBox->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(alarmsCheckBox, 0, 2, 1, 1);

        tabWidget->addTab(alarmsTab, QString());
        notificationsTab = new QWidget();
        notificationsTab->setObjectName(QString::fromUtf8("notificationsTab"));
        verticalLayout_3 = new QVBoxLayout(notificationsTab);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        contactsListView = new QListView(notificationsTab);
        contactsListView->setObjectName(QString::fromUtf8("contactsListView"));
        contactsListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_3->addWidget(contactsListView);

        tabWidget->addTab(notificationsTab, QString());

        verticalLayout_5->addWidget(tabWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(BabyScreen);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BabyScreen);
    } // setupUi

    void retranslateUi(QWidget *BabyScreen)
    {
        BabyScreen->setWindowTitle(QApplication::translate("BabyScreen", "Form", 0, QApplication::UnicodeUTF8));
        photoLabel->setText(QString());
        changeFotoButton->setText(QApplication::translate("BabyScreen", "Camera", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("BabyScreen", "Name:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BabyScreen", "Birthday:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BabyScreen", "Gender:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BabyScreen", "Photo:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(babyTab), QApplication::translate("BabyScreen", "Baby", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BabyScreen", "Timer alarms active:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BabyScreen", "Min. between feeds:", 0, QApplication::UnicodeUTF8));
        alarmsCheckBox->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(alarmsTab), QApplication::translate("BabyScreen", "Alarms", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(notificationsTab), QApplication::translate("BabyScreen", "Notifications", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BabyScreen: public Ui_BabyScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BABYSCREEN_H
