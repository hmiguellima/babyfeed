#include "babiesmodel.h"
#include "nobaby.h"
#include "../global.h"

using namespace bb::cascades;

BabiesModel::BabiesModel(QObject* parent) : QListDataModel()
{
	setParent(parent);
}

void BabiesModel::setBabies(QList<Baby>* babiesList)
{
    _babiesList=babiesList;
    refresh(false);
}

void BabiesModel::refresh(bool dummyPhoto)
{
    clear();

    for (int i = 0; i < _babiesList->size(); i++){
        QVariantMap map;
        Baby baby;

        baby=_babiesList->at(i);

        map.insert("name", baby.getName());
        map.insert("id", baby.getId());
        if (!dummyPhoto)
        	map.insert("photoUrl", Baby::getPhotoUri(baby));
        else
        	map.insert("photoUrl", "file://" + appDataPath + "/dummy.jpg");
        map.insert("age", baby.getAge());
        map.insert("measures", baby.getLastMeasures());

        append(map);
    }

}
