/********************************************************************************
** Form generated from reading UI file 'optionsscreen.ui'
**
** Created: Fri 31. Dec 04:54:58 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSSCREEN_H
#define UI_OPTIONSSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsScreen
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QTimeEdit *timeEdit;
    QLabel *label_2;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *OptionsScreen)
    {
        if (OptionsScreen->objectName().isEmpty())
            OptionsScreen->setObjectName(QString::fromUtf8("OptionsScreen"));
        OptionsScreen->resize(360, 640);
        verticalLayout = new QVBoxLayout(OptionsScreen);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setVerticalSpacing(10);
        label = new QLabel(OptionsScreen);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        timeEdit = new QTimeEdit(OptionsScreen);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, timeEdit);

        label_2 = new QLabel(OptionsScreen);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        checkBox = new QCheckBox(OptionsScreen);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, checkBox);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 527, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(OptionsScreen);

        QMetaObject::connectSlotsByName(OptionsScreen);
    } // setupUi

    void retranslateUi(QWidget *OptionsScreen)
    {
        OptionsScreen->setWindowTitle(QApplication::translate("OptionsScreen", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OptionsScreen", "Time between feeds: ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("OptionsScreen", "Alarm Active:", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OptionsScreen: public Ui_OptionsScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSSCREEN_H
