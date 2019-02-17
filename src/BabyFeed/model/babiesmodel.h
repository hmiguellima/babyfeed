#ifndef BABIESMODEL_H
#define BABIESMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "baby.h"

class BabiesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RecordRoles {
        NameRole = Qt::UserRole + 1,
        FotoUrlRole,
        AgeRole,
        MeasuresRole,
        NewBabyRole
    };

    BabiesModel(QObject* parent);
    void setBabies(QList<Baby>* babiesList);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    void refresh();

private:
    QList<Baby>* _babiesList;
};

#endif // BABIESMODEL_H
