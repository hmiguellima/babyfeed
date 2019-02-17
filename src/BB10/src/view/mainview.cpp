#include "mainview.h"
#include <QUrl>
#include <QList>
#include <QVariant>
#include <QDate>


MainView::MainView(BabyFeedApp* dView, QObject* parent) : View(dView, parent)
{
    _babiesModel=new BabiesModel(this);

    dView->rootContext()->setContextProperty("babiesModel", _babiesModel);
}

void MainView::setBabyList(QList<Baby> *babies)
{
    _babiesModel->setBabies(babies);
}

QString MainView::url()
{
    return "main";
}

QString MainView::viewName()
{
    return "mainScreen";
}

void MainView::showDummyPhotos() {
	_babiesModel->refresh(true);
}

void MainView::handleShowBabyPage(int babyId)
{
    emit showBabyPage(babyId);
}

void MainView::handleActivation()
{
    connect(mainItem(), SIGNAL(showBabyPage(int)), this, SLOT(handleShowBabyPage(int)));
    connect(mainItem(), SIGNAL(deleteBabyClicked(int)), this, SLOT(handleDeleteBaby(int)));
}

void MainView::handleDeleteBaby(int babyId) {
	emit deleteBaby(babyId);
}

