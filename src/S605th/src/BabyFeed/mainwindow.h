#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QAction>
#include <QString>
#include "checkinoutscreen.h"
#include "mainscreen.h"
#include "optionsscreen.h"
#include "manualeventscreen.h"
#include "babyscreen.h"
#include "baby.h"
#include "camerascreen.h"
#include "reportscreen.h"

namespace Ui {
    class MainWindow;
}

class Screen;
class ReportScreen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showScreen(Screen* screen);
    QAction* getBackAction();

    static MainWindow* getInstance();

private:
    static MainWindow* instance;

    Ui::MainWindow *ui;

    MainScreen* mainScreen;
    CheckInOutScreen* checkInOuScreen;
    OptionsScreen* optionsScreen;
    ManualEventScreen* manualEventScreen;
    BabyScreen* babyScreen;
    CameraScreen* cameraScreen;
    ReportScreen* reportsScreen;

    QSqlDatabase db;
    QAction *actionBack;
    QAction *actionExit;
    //QAction *actionOptions;
    QAction *actionExport;
    QAction *actionAbout;
    QAction *actionReset;

public slots:
    void init();

private slots:
    void showMainScreen();
    void showOptionsScreen();
    void resetDatabase();
    void initDatabase();
    void clearContextMenus();
};

#endif // MAINWINDOW_H
