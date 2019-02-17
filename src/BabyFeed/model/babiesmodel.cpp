#include "babiesmodel.h"
#include <QHash>
#include <QByteArray>
#include "nobaby.h"

BabiesModel::BabiesModel(QObject* parent) : QAbstractListModel(parent),
    _babiesList(0)
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FotoUrlRole] = "photo";
    roles[AgeRole] = "age";
    roles[MeasuresRole] = "measures";
    roles[NewBabyRole] = "newBaby";
    setRoleNames(roles);
}

int BabiesModel::rowCount(const QModelIndex &parent) const
{
    if (_babiesList==0)
        return 1;
    else
        return _babiesList->count()+1;
}

QVariant BabiesModel::data(const QModelIndex &index, int role) const
{
    Baby baby;

    if (!index.isValid() || (_babiesList==0))
        return QVariant();

    if (index.row()==_babiesList->count())
        baby=NoBaby();
    else
        baby=_babiesList->at(index.row());

    switch (role)
    {
    case NameRole:
        return baby.getName();
    case AgeRole:
        return (baby.getGender()==NewBaby?"":baby.getAge());
    case MeasuresRole:
        return (baby.getGender()==NewBaby?"":baby.getLastMeasures());
    case FotoUrlRole:
        return (baby.getGender()==NewBaby?"qrc:/icons/icons/new_baby_icon.png":Baby::getPhotoUri(baby));
    case NewBabyRole:
        return (baby.getGender()==NewBaby?true:false);
    default:
        return QVariant();
    }
}

void BabiesModel::setBabies(QList<Baby>* babiesList)
{
    _babiesList=babiesList;
    reset();
}

void BabiesModel::refresh()
{
    reset();
}
