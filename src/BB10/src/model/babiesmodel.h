#ifndef BABIESMODEL_H
#define BABIESMODEL_H

#include <bb/cascades/databinding/qlistdatamodel.h>
#include <QList>
#include <QVariantMap>
#include "baby.h"

class BabiesModel : public bb::cascades::QListDataModel<QVariantMap>
{
public:
    BabiesModel(QObject* parent);
    void setBabies(QList<Baby>* babiesList);
    void refresh(bool dummyPhoto);

private:
    QList<Baby>* _babiesList;
};

#endif // BABIESMODEL_H
