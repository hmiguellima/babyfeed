#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QFile>
#include <QSqlQuery>
#include <QDateTime>
#include <QList>
#include <QSharedPointer>
#include <QMessageBox>
#include <QSqlError>
#include "event.h"
#include "eventbus.h"

#ifdef Q_OS_SYMBIAN
    #include <eikenv.h>
    #include <eikappui.h>
    #include <aknenv.h>
    #include <aknappui.h>
#endif


#ifdef Q_OS_SYMBIAN
    #define DB_FILE_NAME "babyfeed.db.sqlite"
#else
    #define DB_FILE_NAME "D:\\temp\\babyfeed.db"
#endif

MainWindow* MainWindow::instance;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    initDatabase();

    ui->setupUi(this);
    instance=this;

    actionBack=new QAction(tr("Back"), this);
    actionExit=new QAction(tr("Quit"), this);
    //actionOptions=new QAction(tr("Configure"), this);
    actionExport=new QAction(tr("Export"), this);
    actionAbout=new QAction(tr("About"), this);
    actionReset=new QAction(tr("Reset data"), this);

    actionAbout->setSoftKeyRole(QAction::PositiveSoftKey);
    actionExport->setSoftKeyRole(QAction::PositiveSoftKey);
    //actionOptions->setSoftKeyRole(QAction::PositiveSoftKey);
    actionExit->setSoftKeyRole(QAction::NegativeSoftKey);
    actionBack->setSoftKeyRole(QAction::NegativeSoftKey);
    actionReset->setSoftKeyRole(QAction::NegativeSoftKey);

    ui->stackedWidget->addWidget(mainScreen=new MainScreen(this));
    ui->stackedWidget->addWidget(checkInOuScreen=new CheckInOutScreen(this));
    //ui->stackedWidget->addWidget(optionsScreen=new OptionsScreen(this));
    ui->stackedWidget->addWidget(manualEventScreen=new ManualEventScreen(this));
    ui->stackedWidget->addWidget(babyScreen=new BabyScreen(this));
    ui->stackedWidget->addWidget(cameraScreen=new CameraScreen(this));
    ui->stackedWidget->addWidget(reportsScreen=new ReportScreen(this));

    connect(actionBack, SIGNAL(triggered()), this, SLOT(showMainScreen()));
    //connect(actionOptions, SIGNAL(triggered()), this, SLOT(showOptionsScreen()));
    connect(actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionReset, SIGNAL(triggered()), this, SLOT(resetDatabase()));

    connect(EventBus::getInstance(), SIGNAL(showMainScreen()), this, SLOT(showMainScreen()));

    clearContextMenus();
    showMainScreen();
#ifdef Q_OS_SYMBIAN
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*> (CEikonEnv::Static()->AppUi());
    TRAPD(error,
        if (appUi)
            appUi->SetOrientationL(CAknAppUi::EAppUiOrientationAutomatic);
    )
    showMaximized();
#else
    show();
#endif
}

void MainWindow::clearContextMenus()
{
    QWidgetList widgets = QApplication::allWidgets();
    QWidget* w=0;
    foreach(w,widgets) {
        w->setContextMenuPolicy(Qt::NoContextMenu);
    }
}


void MainWindow::showMainScreen()
{
    QAction *action;

    foreach (action, menuBar()->actions())
        menuBar()->removeAction(action);

    menuBar()->addAction(actionAbout);
    menuBar()->addAction(actionExport);
    //menuBar()->addAction(actionOptions);
    menuBar()->addAction(actionReset);

    removeAction(actionBack);
    addAction(actionExit);

    mainScreen->show();
}

void MainWindow::showScreen(Screen* screen)
{
    ui->stackedWidget->setCurrentWidget(screen);
}

void MainWindow::resetDatabase()
{
    // Close database
    db.close();

    // Remove created database binary file
    QFile::remove(DB_FILE_NAME);
    initDatabase();

    EventBus::getInstance()->fireDataReset();
}

void MainWindow::initDatabase()
{
    bool createTables=true;

    db=QSqlDatabase::addDatabase("QSQLITE");

    createTables=!QFile::exists(DB_FILE_NAME);
    db.setDatabaseName(DB_FILE_NAME);

    db.open();
    if (createTables) {
        QSqlQuery query;

        query.exec(
            "CREATE  TABLE Baby ("
            "  `baby_id` INT NOT NULL, "
            "  `baby_name` VARCHAR(50) NOT NULL, "
            "  `baby_birthDate` VARCHAR(50) NOT NULL, "
            "  `baby_gender` VARCHAR(1) NOT NULL, "
            "  `baby_selected` BOOL NOT NULL, "
            "  `baby_timeBetweenFeeds` INT NOT NULL, "
            "  `baby_feedAlarmActive` BOOL NOT NULL, "
            "  PRIMARY KEY (`baby_id`) ); ");

        query.exec(
            "CREATE  TABLE `FeedHistory` ( "
            "  `feed_id` INT NOT NULL , "
            "  `feed_baby_id` INT NOT NULL, "
            "  `feed_dateTime` DATETIME NULL , "
            "  `feed_durationMin` INT NULL , "
            "  `feed_type` VARCHAR(1) NULL , "
            "  `feed_notes` VARCHAR(2000), "
            "  `feed_recurrenceId` INT NULL, "
            "  `feed_alarmNativeId` INT NULL, "
            "  `feed_checked` BOOL NOT NULL, "
            "  PRIMARY KEY (`feed_id`) ); ");

        query.exec(
            "CREATE TABLE `Notification` ( "
            "  `notf_id` INT NOT NULL, "
            "  `notf_type` VARCHAR(1) NOT NULL, "
            "  `notf_contact` VARCHAR(255) NOT NULL, "
            "  `notf_baby_id` INT NOT NULL, "
            "  PRIMARY KEY (`notf_id`) ); ");

        //QMessageBox::information(0, "teste", query.lastError().text());


        query.exec(
            "CREATE  TABLE `FeedConfig` ( "
            "  `fcfg_timeBetween` INT NOT NULL , "
            "  `fcfg_alertActive` BOOL NULL , "
            "  `fcfg_notfActive` BOOL NULL , "
            "  `fcfg_version` VARCHAR(10) NULL , "
            "  PRIMARY KEY (`fcfg_timeBetween`) ); "
            "INSERT INTO FeedConfig VALUES(120, true, true, \"v1.0\");"
        );
    }
}

QAction* MainWindow::getBackAction()
{
    return actionBack;
}


MainWindow* MainWindow::getInstance()
{
    return instance;
}

void MainWindow::showOptionsScreen()
{
    optionsScreen->show();
}
