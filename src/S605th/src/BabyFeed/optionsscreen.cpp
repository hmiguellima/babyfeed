#include "optionsscreen.h"
#include "ui_optionsscreen.h"
#include "mainwindow.h"
#include "eventbus.h"

OptionsScreen::OptionsScreen(MainWindow* window) :
    Screen(window),
    ui(new Ui::OptionsScreen)
{
    ui->setupUi(this);
    actionSave = new QAction(tr("Save"), this);
    actionSave->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(actionSave);
    addAction(getWindow()->getBackAction());
    connect(EventBus::getInstance(), SIGNAL(showOptionsScreen()), this, SLOT(onShowOptionsScreen()));
}

OptionsScreen::~OptionsScreen()
{
    delete ui;
}

void OptionsScreen::showHandler()
{
    getWindow()->setWindowTitle(tr("BabyFeed - Configure"));
}

void OptionsScreen::onShowOptionsScreen()
{
    show();
}
