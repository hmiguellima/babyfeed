#include "babyscreen.h"
#include "ui_babyscreen.h"
#include "mainwindow.h"
#include "eventbus.h"
#include <QList>
#include <QBuffer>
#include <QDataStream>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include <QDate>
#include <QMessageBox>

BabyScreen::BabyScreen(MainWindow* window) :
    Screen(window),
    ui(new Ui::BabyScreen)
{
    ui->setupUi(this);
    contactsModel=0;
    kineticScroller1.setWidget(ui->contactsListView);
    kineticScroller2.setWidget(ui->scrollArea);

    notfMenu=new QComboBox(this);
    notfMenu->setVisible(false);
    notfMenu->addItem(tr("No notification"));
    notfMenu->addItem(tr("Notify feeding"));
    notfMenu->addItem(tr("Notify medicine"));
    notfMenu->addItem(tr("Notify all"));

    saveAction=new QAction(tr("Save"), this);
    saveAction->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(saveAction);
    addAction(getWindow()->getBackAction());

    connect(EventBus::getInstance(), SIGNAL(showBabyScreen(Baby&)), this, SLOT(onShowBabyScreen(Baby&)));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveBaby()));
    connect(ui->changeFotoButton, SIGNAL(clicked()), this, SLOT(takePhoto()));
    connect(EventBus::getInstance(), SIGNAL(babyPhotoAborted()), this, SLOT(onBabyPhotoAborted()));
    connect(EventBus::getInstance(), SIGNAL(babyPhotoCaptured(QByteArray)), this, SLOT(onBabyPhotoCaptured(QByteArray)));
    connect(ui->contactsListView, SIGNAL(clicked(QModelIndex)), this, SLOT(showNotfMenu(QModelIndex)));
    connect(notfMenu, SIGNAL(activated(int)), this, SLOT(changeNotification(int)));

    ui->genderBox->insertItem(0, tr("Boy"));
    ui->genderBox->insertItem(0, tr("Girl"));
    ui->genderBox->insertItem(0, "");
    ui->genderBox->setEditable(false);
    ui->genderBox->setFrame(false);
    ui->genderBox->setMaxVisibleItems(3);

    addAction(getWindow()->getBackAction());

    ui->contactsListView->setIconSize(QSize(32, 32));
}

void BabyScreen::showHandler()
{
}

BabyScreen::~BabyScreen()
{
    delete ui;
    if (contactsModel)
        delete contactsModel;
}

void BabyScreen::onShowBabyScreen(Baby &baby)
{
    this->baby=baby;

    if (baby.getGender()!=NewBaby)
        getWindow()->setWindowTitle(baby.getName()+tr("'s File"));
    else
        getWindow()->setWindowTitle(tr("New Baby's File"));

    if (baby.getGender()==NewBaby)
    {
        ui->nameEdit->setText("");
        ui->birthdayEdit->setDate(QDate::currentDate());
        ui->genderBox->setCurrentIndex(0);
        ui->photoLabel->setPixmap(QPixmap(":/icons/icons/baby_icon.jpg"));
        ui->alarmsCheckBox->setChecked(true);
        ui->feedIntervalBox->setValue(120);
    }
    else
    {
        ui->nameEdit->setText(baby.getName());
        ui->birthdayEdit->setDate(baby.getBirthDate().date());
        ui->photoLabel->setPixmap(QPixmap::fromImage(baby.getPhoto()));
        if (baby.getGender()==Girl)
            ui->genderBox->setCurrentIndex(1);
        else
            ui->genderBox->setCurrentIndex(2);
        ui->alarmsCheckBox->setChecked(baby.isFeedAlarmActive());
        ui->feedIntervalBox->setValue(baby.getTimeBetweenFeeds());
    }

    if (contactsModel)
        delete contactsModel;

    contactsModel=new ContactsModel(baby.getNotfContactKeys());

    ui->contactsListView->setModel(contactsModel);
    ui->tabWidget->setCurrentIndex(0);

    show();
}

void BabyScreen::saveBaby()
{
    bool newBaby=(baby.getGender()==NewBaby);

    if (ui->nameEdit->text().length()==0)
    {
        QMessageBox::information(this, tr("BabyFeed"), tr("Baby's name is invalid"));
        return;
    }
    baby.setName(ui->nameEdit->text());

    if (ui->genderBox->currentIndex()==0)
    {
        QMessageBox::information(this, tr("BabyFeed"), tr("Baby's gender is invalid"));
        return;
    }
    if (ui->genderBox->currentIndex()==1)
        baby.setGender(Girl);
    else
        baby.setGender(Boy);

    baby.setBirthDate(QDateTime(ui->birthdayEdit->date()));
    baby.setFeedAlarmActive(ui->alarmsCheckBox->isChecked());
    baby.setTimeBetweenFeeds(ui->feedIntervalBox->value());
    baby.setSelected(true);
    baby.persist();

    if (newBaby)
        EventBus::getInstance()->fireBabyAdded(baby);
    else
        EventBus::getInstance()->fireBabyUpdated(baby);
}

void BabyScreen::deleteBaby()
{

}

void BabyScreen::takePhoto()
{
    EventBus::getInstance()->fireShowCameraScreen();
}

void BabyScreen::onBabyPhotoCaptured(QByteArray data)
{
    QImage image=QImage::fromData(data).scaled(QSize(133, 100));
    QPixmap pixmap=QPixmap::fromImage(image);
    baby.setPhoto(image);
    ui->photoLabel->setPixmap(pixmap);
    show();
}

void BabyScreen::onBabyPhotoAborted()
{
    show();
}

void BabyScreen::showNotfMenu(QModelIndex index)
{
    QString key=contactsModel->getContactKeyFromRow(index.row());

    switch (baby.getNotificationType(key))
    {
        case 0:
            notfMenu->setCurrentIndex(0);
            break;
        case 'F':
            notfMenu->setCurrentIndex(1);
            break;
        case 'M':
            notfMenu->setCurrentIndex(2);
            break;
        case 'B':
            notfMenu->setCurrentIndex(3);
            break;
    }

    notfMenu->setProperty("contactRow", QVariant(index.row()));
    notfMenu->setProperty("contactKey", QVariant(key));
    notfMenu->showPopup();
}

void BabyScreen::changeNotification(int notfType)
{
    QString contactKey=notfMenu->property("contactKey").toString();
    int contactRow=notfMenu->property("contactRow").toInt();

    switch (notfType)
    {
        case 0:
            baby.removeNotification(contactKey);
            contactsModel->setNotification(contactRow, false);
            break;
        case 1:
            baby.updateNotfication(contactKey, 'F');
            contactsModel->setNotification(contactRow, true);
            ui->contactsListView->scrollToTop();
            break;
        case 2:
            baby.updateNotfication(contactKey, 'M');
            contactsModel->setNotification(contactRow, true);
            ui->contactsListView->scrollToTop();
            break;
        case 3:
            baby.updateNotfication(contactKey, 'B');
            contactsModel->setNotification(contactRow, true);
            ui->contactsListView->scrollToTop();
            break;
    }
}
