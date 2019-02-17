#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include "checkinoutscreen.h"
#include "mainscreen.h"
#include "optionsscreen.h"

namespace Ui {
    class MainWindow;
}

class Screen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showScreen(Screen* screen);

public slots:
    void showCheckInOutScreen();
    void showOptionsScreen();
    void showMainScreen();

private:
    Ui::MainWindow *ui;

    MainScreen *mainScreen;
    CheckInOutScreen *checkInOuScreen;
    OptionsScreen * optionsScreen;
    QSqlDatabase db;

    void initDatabase();
    void clearContextMenus();
};

#endif // MAINWINDOW_H
