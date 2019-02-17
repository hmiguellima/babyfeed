#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //centralWidget()->showMaximized();
    ui->setupUi(this);

    ui->actionAbout->setSoftKeyRole(QAction::PositiveSoftKey);
    ui->actionExport->setSoftKeyRole(QAction::PositiveSoftKey);
    ui->actionExit->setSoftKeyRole(QAction::NegativeSoftKey);
    ui->actionOptions->setSoftKeyRole(QAction::PositiveSoftKey);
    ui->actionBack->setSoftKeyRole(QAction::NegativeSoftKey);

    ui->stackedWidget->addWidget(mainScreen=new MainScreen(this));
    ui->stackedWidget->addWidget(checkInOuScreen=new CheckInOutScreen(this));
    ui->stackedWidget->addWidget(optionsScreen=new OptionsScreen(this));

    connect(ui->actionBack, SIGNAL(triggered()), this, SLOT(showMainScreen()));

    clearContextMenus();
    showMainScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearContextMenus()
{
    QWidgetList widgets = QApplication::allWidgets();
    QWidget* w=0;
    foreach(w,widgets) {
        w->setContextMenuPolicy(Qt::NoContextMenu);
    }
}

void MainWindow::showCheckInOutScreen()
{
    menuBar()->removeAction(ui->actionExit);
    menuBar()->addAction(ui->actionBack);
    checkInOuScreen->show();
}

void MainWindow::showOptionsScreen()
{
    optionsScreen->show();
}

void MainWindow::showMainScreen()
{
    QAction *action;

    foreach (action, menuBar()->actions())
        menuBar()->removeAction(action);

    menuBar()->addAction(ui->actionAbout);
    menuBar()->addAction(ui->actionExport);
    menuBar()->addAction(ui->actionOptions);
    menuBar()->addAction(ui->actionExit);
    mainScreen->show();
}

void MainWindow::showScreen(Screen* screen)
{
    ui->stackedWidget->setCurrentWidget(screen);
}

void MainWindow::initDatabase()
{
    db=QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("my.db.sqlite");
    db.open();
}
