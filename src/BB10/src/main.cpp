#include <QtCore/QObject>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <bb/cascades/Application>
#include "BabyFeedApp.hpp"
#define QT_DECLARATIVE_DEBUG
#include <Qt/qdeclarativedebug.h>

using ::bb::cascades::Application;

void myMessageOutput(QtMsgType type, const char *msg)
 {
     //in this function, you can write the message to any stream!
     switch (type) {
     case QtDebugMsg:
         fprintf(stderr, "Debug: %s\n", msg);
         break;
     case QtWarningMsg:
         fprintf(stderr, "Warning: %s\n", msg);
         break;
     case QtCriticalMsg:
         fprintf(stderr, "Critical: %s\n", msg);
         break;
     case QtFatalMsg:
         fprintf(stderr, "Fatal: %s\n", msg);
         abort();
         break;
     }
 }

int main(int argc, char **argv)
{
	qInstallMsgHandler(myMessageOutput);
    Application app(argc, argv);

    QTranslator translator;
    QString locale_string = QLocale().name(); 
    QString filename = QString( "BabyFeed_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    BabyFeedApp bapp(&app);
    
    return Application::exec();
}
