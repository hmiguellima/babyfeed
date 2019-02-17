#ifndef BABYFEEDAPP_H
#define BABYFEEDAPP_H

#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QTranslator>
#include <QModelIndex>
#include "model/baby.h"

namespace bb { namespace cascades { class Application; }}
class Screen;
class MainScreen;
class CheckInOutScreen;
class ManualEventScreen;
class BabyScreen;
class ReportScreen;

class BabyFeedApp : public QObject
{
    Q_OBJECT

public:
    explicit BabyFeedApp(bb::cascades::Application* app);

    void showScreen(Screen* screen);
    void showMessageBox(QString title, QString message);
    void showBusyBox();
    void hideBusyBox();
    bb::cascades::QmlDocument* rootContext();
    bb::cascades::AbstractPane* rootObject();

    static BabyFeedApp* getInstance();

private:
    static BabyFeedApp* instance;

    bb::cascades::AbstractPane *root;
    MainScreen* mainScreen;
    CheckInOutScreen* checkInOutScreen;
    ManualEventScreen* manualEventScreen;
    BabyScreen* babyScreen;
    ReportScreen* reportScreen;
    Screen* currentScreen;

    QSqlDatabase db;
    QTranslator translator;
    bb::cascades::QmlDocument *qml;

    void checkLang();
    void translate(QString lang);
    QString getAboutText();

public slots:
    void init();
    void start();
    void test();

private slots:
    void showMainScreen();
    void showAbout();
    void initDatabase();
    void backup();
    void restore();
    void showHelp();
    void updateVersion();
    void initLang(QString lang);
    void handleScreenActivation(QString name);
    void exportEventsToExcel(QString email);
};

#endif // ifndef BABYFEEDAPP_H
