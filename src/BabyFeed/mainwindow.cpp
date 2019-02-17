#include "mainwindow.h"
#include <QFile>
#include <QSqlQuery>
#include <QDateTime>
#include <QList>
#include <QSharedPointer>
#include <QSqlError>
#include "model/event.h"
#include "model/eventbus.h"
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include <QApplication>
#include "global.h"
#include <QUrl>
#include <QLocale>
#include <QSharedPointer>
#include <QDesktopServices>
#include <QTextStream>
#include <QGraphicsObject>
#include <QMetaObject>
#include "controller/mainscreen.h"
#include "controller/checkinoutscreen.h"
#include "controller/manualeventscreen.h"
#include "controller/babyscreen.h"
#include "controller/reportscreen.h"
#include "view/view.h"
#include <QOrganizerManager>
#include <QOrganizerItemDetailDefinition>
#include <QOrganizerEvent>
#include <QMessageBox>

using namespace QtMobility;

#define DB_FILE_NAME "babyfeed.db"
#define BACKUP_SIGNATURE_V1 "BabyFeed (v1) backup"
#define BACKUP_SIGNATURE_V2 "BabyFeed (v2) backup"
#define HELP_URI "http://www.hlimasoft.com/babyfeed/help"
#define UPDATE_URI "http://www.hlimasoft.com/babyfeed/update"

MainWindow* MainWindow::instance;

MainWindow::MainWindow() : QDeclarativeView(), currentScreen(0)
{
#if defined(MEEGO_VERSION)
    setSource(QUrl("qrc:/qml/qml/BabyFeedMeego/Main.qml"));
#else
    setSource(QUrl("qrc:/qml/qml/BabyFeedSymbian/Main.qml"));
#endif
    showFullScreen();

    connect(rootObject(), SIGNAL(splashFinished()), this, SLOT(init()));
    connect(rootObject(), SIGNAL(screenLoaded()), this, SLOT(handleScreenActivation()));
    connect(rootObject(), SIGNAL(aboutClicked()), this, SLOT(showAbout()));
    connect(rootObject(), SIGNAL(helpClicked()), this, SLOT(showHelp()));
    connect(rootObject(), SIGNAL(backupClicked()), this, SLOT(backup()));
    connect(rootObject(), SIGNAL(restoreClicked()), this, SLOT(restore()));
    connect(rootObject(), SIGNAL(langClicked(QString)), this, SLOT(initLang(QString)));
    connect(rootObject(), SIGNAL(exportClicked(QString)), this, SLOT(exportEventsToExcel(QString)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    qDebug("c++:splashFinished");

#if defined(MEEGO_VERSION)
    appDataPath = "/home/user/MyDocs";
#else
    appDataPath = QApplication::applicationDirPath();
#endif
    qDebug() << "Data path: " << appDataPath;

    initDatabase();
    instance=this;
    checkLang();
    start();
}

void MainWindow::showMainScreen()
{
    // Vamos aproveitar para remover alarmes expirados
    Event::deleteExpiredAlarms();

    mainScreen->show();
}

void MainWindow::showScreen(Screen* screen)
{
    currentScreen=screen;
    QMetaObject::invokeMethod(rootObject(), "showScreen", Q_ARG(QVariant, screen->getViewUrl()));
}

void MainWindow::initDatabase()
{
    bool createTables=true;
    QString versao;

    db=QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "Current path: " << QDir::currentPath();
    db.setDatabaseName(QDir::toNativeSeparators(QString(appDataPath)+"/"+DB_FILE_NAME));
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

        //QMessageBox::information(0, "teste", query.lastError().text());


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

MainWindow* MainWindow::getInstance()
{
    return instance;
}

void MainWindow::showAbout()
{
    showMessageBox(tr("BabyFeed"), getAboutText());
}

void MainWindow::backup()
{
    QString path;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select backup directory"), "C:", QFileDialog::ShowDirsOnly);

    if (!dir.isEmpty())
    {
        showBusyBox();
        path=QDir::toNativeSeparators(dir);

        QuaZip zip(path+"babyfeed.zip");
        if(!zip.open(QuaZip::mdCreate)) {
            showMessageBox(tr("BabyFeed"), QString("backup(): zip.open(): %0").arg(zip.getZipError()));
          return;
        }
        zip.setComment(BACKUP_SIGNATURE_V2);
        QFileInfoList files=QDir(QDir::toNativeSeparators(appDataPath)).entryInfoList();
        QFile inFile;
        QuaZipFile outFile(&zip);
        char c;
        //QDir::setCurrent(QDir::toNativeSeparators(appDataPath));
        foreach(QFileInfo file, files) {
          if(!file.isFile()) continue;
          inFile.setFileName(file.fileName());
          if(!inFile.open(QIODevice::ReadOnly)) {
            showMessageBox(tr("BabyFeed"), QString("backup(): inFile.open(): %0").arg(inFile.errorString().toLocal8Bit().constData()));
            return;
          }
          if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(inFile.fileName(), inFile.fileName()))) {
            showMessageBox(tr("BabyFeed"), QString("backup(): outFile.open(): %0").arg(outFile.getZipError()));
            return;
          }
          while(inFile.getChar(&c)&&outFile.putChar(c));
          if(outFile.getZipError()!=UNZ_OK) {
            showMessageBox(tr("BabyFeed"), QString("backup(): outFile.putChar(): %0").arg(outFile.getZipError()));
            return;
          }
          outFile.close();
          if(outFile.getZipError()!=UNZ_OK) {
            showMessageBox(tr("BabyFeed"), QString("backup(): outFile.close(): %0").arg(outFile.getZipError()));
            return;
          }
          inFile.close();
        }
        zip.close();
        if(zip.getZipError()!=0) {
          showMessageBox(tr("BabyFeed"), QString("backup(): zip.close(): %0").arg(zip.getZipError()));
          return;
        }

        hideBusyBox();
        showMessageBox(tr("BabyFeed"), tr("Backup saved to ")+path+"babyfeed.zip");
        return;
    }
}

void MainWindow::restore()
{
    int ret;
    QString sig;
    QString backupFile;

    backupFile = QFileDialog::getOpenFileName(this, tr("Select backup file"), "C:");
    if (backupFile.isEmpty())
        return;

    // Test if file is a valid backup
    QuaZip zip(QDir::toNativeSeparators(backupFile));
    if(!zip.open(QuaZip::mdUnzip)) {
        showMessageBox(tr("BabyFeed"), tr("Invalid backup file"));
        return;
    }
    sig=zip.getComment();

    if ( (sig != BACKUP_SIGNATURE_V1) && (sig != BACKUP_SIGNATURE_V2) )
    {
        showMessageBox(tr("BabyFeed"), tr("Invalid backup file (sig)"));
        return;
    }

    ret=QMessageBox::warning(this, tr("BabyFeed"), tr("This action will replace all baby files, are you sure?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret==QMessageBox::Yes)
    {
        showBusyBox();

        // Close database
        db.close();
        db.removeDatabase(db.connectionName());


        // Remover ficheiros
        QFileInfoList files=QDir(QDir::toNativeSeparators(appDataPath)).entryInfoList();

        foreach(QFileInfo file, files)
        {
            if(!file.isFile()) continue;

            QFile::remove(QDir::toNativeSeparators(file.absoluteFilePath()));
        }


        QuaZipFileInfo info;
        QuaZipFile file(&zip);
        QFile out;
        QString name;
        char c;
        for(bool more=zip.goToFirstFile(); more; more=zip.goToNextFile()) {
          if(!zip.getCurrentFileInfo(&info)) {
            showMessageBox(tr("BabyFeed"), tr("Invalid backup file (err)"));
            return;
          }
          if(!file.open(QIODevice::ReadOnly)) {
            showMessageBox(tr("BabyFeed"), tr("Invalid backup file (err)"));
            return;
          }
          name=file.getActualFileName();
          if(file.getZipError()!=UNZ_OK) {
            showMessageBox(tr("BabyFeed"), tr("Invalid backup file (err)"));
            return;
          }

          out.setFileName(QDir::toNativeSeparators(QString(appDataPath)+"/"+name));
          out.open(QIODevice::WriteOnly);
          char buf[4096];
          int len = 0;
          while (file.getChar(&c)) {
            // we could just do this, but it's about 40% slower:
            // out.putChar(c);
            buf[len++] = c;
            if (len >= 4096) {
              out.write(buf, len);
              len = 0;
            }
          }
          if (len > 0) {
            out.write(buf, len);
          }
          out.close();
          if(file.getZipError()!=UNZ_OK) {
              showMessageBox(tr("BabyFeed"), tr("Error restoring backup:")+QString::number(file.getZipError()));
              return;
          }
          if(!file.atEnd()) {
              showMessageBox(tr("BabyFeed"), tr("Error restoring backup"));
              return;
          }
          file.close();
          if(file.getZipError()!=UNZ_OK) {
              showMessageBox(tr("BabyFeed"), tr("Error restoring backup:")+QString::number(file.getZipError()));
              return;
          }
        }
        zip.close();
        if(zip.getZipError()!=UNZ_OK) {
            showMessageBox(tr("BabyFeed"), tr("Error restoring backup:")+QString::number(file.getZipError()));
            return;
        }

        hideBusyBox();
        showMessageBox(tr("BabyFeed"), tr("Restore complete"));
        initDatabase();
        EventBus::getInstance()->fireDataReset();
    }
}

void MainWindow::showHelp()
{
    QDesktopServices::openUrl(QUrl(QString(HELP_URI)+"/"+appLang));
}

void MainWindow::start()
{
    connect(EventBus::getInstance(), SIGNAL(showMainScreen()), this, SLOT(showMainScreen()));

    mainScreen=new MainScreen(this);
    manualEventScreen=new ManualEventScreen(this);
    babyScreen=new BabyScreen(this);
    checkInOuScreen=new CheckInOutScreen(this);
    reportScreen=new ReportScreen(this);

#if defined(TIME_TRIAL_VERSION)
    QMessageBox::information(0, tr("BabyFeed"), "Trial version\r\n(ends on October 1, 2012)");
    if (QDate::currentDate()>QDate(2012, 10, 1))
        QApplication::instance()->quit();
#endif

    showMainScreen();
}

void MainWindow::checkLang()
{
    QSqlQuery query;
    QString lang;

    query.exec("select fcfg_lang from FeedConfig");
    query.next();
    lang=query.value(0).toString();
    if (lang=="xx")
    {
        lang="en";
        query.exec("update FeedConfig set fcfg_lang=\""+lang+"\"");
    }
    else
        translate(lang);
}

void MainWindow::initLang(QString lang)
{
    QSqlQuery query;

    query.exec("update FeedConfig set fcfg_lang=\""+lang+"\"");
    showMessageBox("BabyFeed", "Restart BabyFeed to change the language");
}

void MainWindow::translate(QString lang)
{
    translator.load("babyfeed_"+lang, ":/tr");
    qApp->installTranslator(&translator);
    QLocale::setDefault(QLocale(lang));
    appLang=lang;
}

QString MainWindow::getAboutText()
{
    QFile file(":/txt/about.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

void MainWindow::updateVersion()
{
    QDesktopServices::openUrl(QUrl(QString(UPDATE_URI)+"?version="+VERSION));
}

void MainWindow::test()
{
    qDebug("test");
}

void MainWindow::handleScreenActivation()
{
    if (currentScreen!=0)
        currentScreen->notifyActive();
}

void MainWindow::showMessageBox(QString title, QString message)
{
    QMetaObject::invokeMethod(rootObject(), "showMessageBox", Q_ARG(QVariant, message));
}

void MainWindow::showBusyBox()
{
    QMetaObject::invokeMethod(rootObject(), "showBusyBox");
}

void MainWindow::hideBusyBox()
{
    QMetaObject::invokeMethod(rootObject(), "hideBusyBox");
}

void MainWindow::exportEventsToExcel(QString email)
{
    Baby currentBaby=mainScreen->getCurrentBaby();
    bool res;

    if (currentBaby.getGender()==NewBaby)
        showMessageBox("BabyFeed", tr("You must select a baby to export"));
    else
    {
        showBusyBox();
        QApplication::processEvents();
        res=currentBaby.exportEvents(email);
        hideBusyBox();
        if (!res)
            showMessageBox("BabyFeed", tr("Mail was not sent. Please check if you have a valid destination address and you have your phone's email account setup."));
    }
}

