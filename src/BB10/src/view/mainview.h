#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "view/view.h"
#include "model/baby.h"
#include <QList>
#include <QDate>
#include "../BabyFeedApp.hpp"
#include <QObject>
#include "model/babiesmodel.h"

class MainView : public View
{
    Q_OBJECT
public:
    MainView(BabyFeedApp* dView, QObject* parent);

    QString viewName();
    QString url();

    void setBabyList(QList<Baby>* babies);
    void showDummyPhotos();

public slots:
    void handleActivation();

signals:
	void showBabyPage(int babyId);
	void deleteBaby(int babyId);

private:
    BabiesModel* _babiesModel;

private slots:
    void handleShowBabyPage(int babyId);
    void handleDeleteBaby(int babyId);
};

#endif // MAINVIEW_H
