/********************************************************************************
** Form generated from reading UI file 'camerascreen.ui'
**
** Created: Fri 31. Dec 04:54:59 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASCREEN_H
#define UI_CAMERASCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraScreen
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QFrame *viewfinderHolder;
    QVBoxLayout *viewfinderHolderLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *CameraScreen)
    {
        if (CameraScreen->objectName().isEmpty())
            CameraScreen->setObjectName(QString::fromUtf8("CameraScreen"));
        CameraScreen->resize(360, 640);
        verticalLayout_2 = new QVBoxLayout(CameraScreen);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(CameraScreen);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        frame = new QFrame(CameraScreen);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        viewfinderHolder = new QFrame(frame);
        viewfinderHolder->setObjectName(QString::fromUtf8("viewfinderHolder"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(viewfinderHolder->sizePolicy().hasHeightForWidth());
        viewfinderHolder->setSizePolicy(sizePolicy);
        viewfinderHolder->setMinimumSize(QSize(266, 200));
        viewfinderHolder->setMaximumSize(QSize(266, 200));
        viewfinderHolder->setFrameShape(QFrame::StyledPanel);
        viewfinderHolder->setFrameShadow(QFrame::Raised);
        viewfinderHolder->setLineWidth(4);
        viewfinderHolderLayout = new QVBoxLayout(viewfinderHolder);
        viewfinderHolderLayout->setSpacing(0);
        viewfinderHolderLayout->setContentsMargins(0, 0, 0, 0);
        viewfinderHolderLayout->setObjectName(QString::fromUtf8("viewfinderHolderLayout"));

        horizontalLayout->addWidget(viewfinderHolder);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(CameraScreen);

        QMetaObject::connectSlotsByName(CameraScreen);
    } // setupUi

    void retranslateUi(QWidget *CameraScreen)
    {
        CameraScreen->setWindowTitle(QApplication::translate("CameraScreen", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CameraScreen", "Take baby's photo:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraScreen: public Ui_CameraScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASCREEN_H
