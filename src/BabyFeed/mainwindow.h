#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql/QSqlDatabase>
#include <QString>
#include "model/baby.h"
#include <QTranslator>
#include <QModelIndex>
#include <QDeclarativeView>

class Screen;
class MainScreen;
class CheckInOutScreen;
class ManualEventScreen;
class BabyScreen;
class CameraScreen;
class ReportScreen;

class MainWindow : public QDeclarativeView
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

    void showScreen(Screen* screen);
    void showMessageBox(QString title, QString message);
    void showBusyBox();
    void hideBusyBox();
    static MainWindow* getInstance();

private:
    static MainWindow* instance;

    MainScreen* mainScreen;
    CheckInOutScreen* checkInOuScreen;
    ManualEventScreen* manualEventScreen;
    BabyScreen* babyScreen;
    CameraScreen* cameraScreen;
    ReportScreen* reportScreen;
    Screen* currentScreen;

    QSqlDatabase db;
    QTranslator translator;

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
    void handleScreenActivation();
    void exportEventsToExcel(QString email);
};

#endif // MAINWINDOW_H
