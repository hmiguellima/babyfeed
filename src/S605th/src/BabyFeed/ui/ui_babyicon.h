/********************************************************************************
** Form generated from reading UI file 'babyicon.ui'
**
** Created: Fri 31. Dec 04:54:58 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BABYICON_H
#define UI_BABYICON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BabyIcon
{
public:
    QLabel *nameLabel;
    QPushButton *fotoButton;

    void setupUi(QWidget *BabyIcon)
    {
        if (BabyIcon->objectName().isEmpty())
            BabyIcon->setObjectName(QString::fromUtf8("BabyIcon"));
        BabyIcon->resize(176, 150);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BabyIcon->sizePolicy().hasHeightForWidth());
        BabyIcon->setSizePolicy(sizePolicy);
        BabyIcon->setMinimumSize(QSize(176, 150));
        BabyIcon->setMaximumSize(QSize(176, 150));
        BabyIcon->setAutoFillBackground(true);
        nameLabel = new QLabel(BabyIcon);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(5, 113, 171, 24));
        QFont font;
        font.setPointSize(7);
        nameLabel->setFont(font);
        nameLabel->setAlignment(Qt::AlignCenter);
        fotoButton = new QPushButton(BabyIcon);
        fotoButton->setObjectName(QString::fromUtf8("fotoButton"));
        fotoButton->setGeometry(QRect(22, 10, 133, 100));
        fotoButton->setIconSize(QSize(133, 100));

        retranslateUi(BabyIcon);

        QMetaObject::connectSlotsByName(BabyIcon);
    } // setupUi

    void retranslateUi(QWidget *BabyIcon)
    {
        BabyIcon->setWindowTitle(QApplication::translate("BabyIcon", "Form", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("BabyIcon", "<Click to change>", 0, QApplication::UnicodeUTF8));
        fotoButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BabyIcon: public Ui_BabyIcon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BABYICON_H
