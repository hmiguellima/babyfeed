#include <bb/cascades/Application>
#include "BabyFeedApp.hpp"
#include <QFile>
#include <QtSql/qsqlquery.h>
#include <QDateTime>
#include <QList>
#include <QSharedPointer>
#include <QtSql/qsqlerror.h>
#include "model/event.h"
#include "model/eventbus.h"
#include <QDir>
#include <QFile>
#include <QUrl>
#include <QLocale>
#include <QSharedPointer>
#include <QTextStream>
#include <QMetaObject>
#include "controller/mainscreen.h"
#include "controller/checkinoutscreen.h"
#include "controller/manualeventscreen.h"
#include "controller/babyscreen.h"
#include "controller/reportscreen.h"
#include "view/view.h"
#include "global.h"
#include "controller/screen.h"
#include <bb/cascades/controls/page.h>

#define DB_FILE_NAME "babyfeed.db"
#define BACKUP_SIGNATURE_V1 "BabyFeed (v1) backup"
#define BACKUP_SIGNATURE_V2 "BabyFeed (v2) backup"
#define HELP_URI "http://www.hlimasoft.com/babyfeed/help"
#define UPDATE_URI "http://www.hlimasoft.com/babyfeed/update"

BabyFeedApp* BabyFeedApp::instance;

using namespace bb::cascades;

BabyFeedApp::BabyFeedApp(bb::cascades::Application* app)
{
	QCoreApplication::setOrganizationName("HLimaSoft");
	QCoreApplication::setOrganizationDomain("www.hlimasoft.com");
	QCoreApplication::setApplicationName("BabyFeed");

	qmlRegisterType<Baby>("com.babyfeed.data", 1, 0, "Baby");

	qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("cs", this);

    root = qml->createRootObject<AbstractPane>();
    app->setScene(root);

    connect(rootObject(), SIGNAL(screenLoaded(QString)), this, SLOT(handleScreenActivation(QString)));
    connect(rootObject(), SIGNAL(aboutClicked()), this, SLOT(showAbout()));
    connect(rootObject(), SIGNAL(helpClicked()), this, SLOT(showHelp()));
    connect(rootObject(), SIGNAL(backupClicked()), this, SLOT(backup()));
    connect(rootObject(), SIGNAL(restoreClicked()), this, SLOT(restore()));
    connect(rootObject(), SIGNAL(langClicked(QString)), this, SLOT(initLang(QString)));
    connect(rootObject(), SIGNAL(exportClicked(QString)), this, SLOT(exportEventsToExcel(QString)));

    init();
}

void BabyFeedApp::init()
{
    qDebug("c++:app instanciated");

    appDataPath = QDir::homePath();
    //appDataPath = QDir::currentPath()+"/shared/documents";

    qDebug() << "Data path: " << appDataPath;

    initDatabase();
    instance=this;
    checkLang();
    start();
}

AbstractPane* BabyFeedApp::rootObject() {
	return root;
}

void BabyFeedApp::showMainScreen()
{
    // Vamos aproveitar para remover alarmes expirados

	//BabyEvent::deleteExpiredAlarms();

    mainScreen->show();
}

void BabyFeedApp::showScreen(Screen* screen)
{
    if (currentScreen!=screen) {
    	currentScreen=screen;
        QMetaObject::invokeMethod(rootObject(), "showScreen", Q_ARG(QVariant, screen->getViewUrl()));
    }
}

QmlDocument* BabyFeedApp::rootContext() {
	return qml;
}

void BabyFeedApp::initDatabase()
{
    bool createTables=true;
    QString versao;

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(appDataPath+"/"+DB_FILE_NAME);
    db.open();

    QSqlQuery query;

    query.exec("SELECT name FROM sqlite_master WHERE type='table' and name='FeedConfig';");
    createTables=!query.next();

    if (createTables) {
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
            "  `feed_alarmNativeKey` VARCHAR(2000) NULL, "
            "  `feed_checked` BOOL NOT NULL, "
            "  `feed_weight` INT NOT NULL, "
            "  `feed_height` INT NOT NULL, "
            "  `feed_cephalic` INT NOT NULL, "
            "  PRIMARY KEY (`feed_id`) ); ");

        query.exec(
            "CREATE TABLE `Notification` ( "
            "  `notf_id` INT NOT NULL, "
            "  `notf_type` VARCHAR(1) NOT NULL, "
            "  `notf_contact` VARCHAR(255) NOT NULL, "
            "  `notf_baby_id` INT NOT NULL, "
            "  PRIMARY KEY (`notf_id`) ); ");

        query.exec(
            "CREATE  TABLE `FeedConfig` ( "
            "  `fcfg_lang` VARCHAR(2) NOT NULL, "
            "  `fcfg_version` VARCHAR(10) NOT NULL); ");

        query.exec(
            "INSERT INTO FeedConfig VALUES(\"xx\", \"v"+QString(VERSION)+"\");");
    } else {
        // Verificar se é necessário upgrade
        query.exec("SELECT fcfg_version FROM FeedConfig");
        if (query.next())
        {
            versao = query.value(0).toString();
            if (versao!="v"+QString(VERSION))
            {
                if (versao=="v1.0")
                {
                    query.exec("ALTER TABLE FeedHistory ADD feed_weight INT");
                    query.exec("ALTER TABLE FeedHistory ADD feed_height INT");
                    query.exec("ALTER TABLE FeedHistory ADD feed_cephalic INT");
                }
                if ( (versao=="v1.0") || (versao=="v1.1") || (versao=="v1.2") )
                {
                    query.exec("ALTER TABLE FeedHistory ADD feed_alarmNativeKey VARCHAR(2000) NULL");
                }
                query.exec("UPDATE FeedConfig SET fcfg_version=\"v"+QString(VERSION)+"\"");
            }
        }
    }
}

BabyFeedApp* BabyFeedApp::getInstance()
{
    return instance;
}

void BabyFeedApp::showAbout()
{
    showMessageBox(tr("BabyFeed"), getAboutText());
}

void BabyFeedApp::backup()
{
}

void BabyFeedApp::restore()
{
}

void BabyFeedApp::showHelp()
{
}

void BabyFeedApp::start()
{
    connect(EventBus::getInstance(), SIGNAL(showMainScreen()), this, SLOT(showMainScreen()));
    //connect(EventBus::getInstance(), SIGNAL(showCaptureDialog()), this, SLOT(showCaptureDialog()));

    mainScreen=new MainScreen(this);
    manualEventScreen=new ManualEventScreen(this);
    babyScreen=new BabyScreen(this);
    checkInOutScreen=new CheckInOutScreen(this);
    reportScreen=new ReportScreen(this);

    showMainScreen();
}

void BabyFeedApp::checkLang()
{
}

void BabyFeedApp::initLang(QString lang)
{
}

void BabyFeedApp::translate(QString lang)
{
}

QString BabyFeedApp::getAboutText()
{
    QFile file("txt/about.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

void BabyFeedApp::updateVersion()
{
}

void BabyFeedApp::test()
{
    qDebug("test");
}

void BabyFeedApp::handleScreenActivation(QString name)
{
	QStringList screens;

	if (currentScreen!=0)
		currentScreen->notifyInactive();

	screens << "mainScreen" << "checkInOutScreen" << "manualEventScreen" << "babyScreen" << "reportScreen";
	currentScreen=0;

	switch (screens.indexOf(name)) {
		case 0:
			currentScreen=mainScreen;
			break;

		case 1:
			currentScreen=checkInOutScreen;
			break;

		case 2:
			currentScreen=manualEventScreen;
			break;

		case 3:
			currentScreen=babyScreen;
			break;

		case 4:
			currentScreen=reportScreen;
			break;
	}

	if (currentScreen!=0)
        currentScreen->notifyActive();
}

void BabyFeedApp::showMessageBox(QString title, QString message)
{
    QMetaObject::invokeMethod(rootObject(), "showMessageBox", Q_ARG(QVariant, message));
}

void BabyFeedApp::showBusyBox()
{
    QMetaObject::invokeMethod(rootObject(), "showBusyBox");
}

void BabyFeedApp::hideBusyBox()
{
    QMetaObject::invokeMethod(rootObject(), "hideBusyBox");
}


void BabyFeedApp::exportEventsToExcel(QString email)
{
}
