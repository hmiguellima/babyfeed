#include <QtGui/QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QWidget>
#include <QTimer>
#include <QObject>
#include "mainwindow.h"

#ifdef Q_OS_SYMBIAN
    #include <eikenv.h>
    #include <eikappui.h>
    #include <aknenv.h>
    #include <aknappui.h>
#endif

#define WAIT_MS 3000

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    QPixmap pixmap(QString::fromUtf8(":/icons/icons/breastfeeding-icon.jpg"));
    QSplashScreen splash(pixmap);

    #ifdef Q_OS_SYMBIAN
        CAknAppUi* appUi = dynamic_cast<CAknAppUi*> (CEikonEnv::Static()->AppUi());
        TRAPD(error,
            if (appUi) {
                // Lock application orientation into landscape
                appUi->SetOrientationL(CAknAppUi::EAppUiOrientationPortrait);
            }
        )
    #endif

    splash.showFullScreen();
    splash.raise();
    qApp->processEvents();

    QTimer::singleShot(WAIT_MS, &splash, SLOT(close()));
    QTimer::singleShot(WAIT_MS, &window, SLOT(init()));

    return a.exec();
}

