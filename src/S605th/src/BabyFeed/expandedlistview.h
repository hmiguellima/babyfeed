#ifndef EXPANDEDLISTVIEW_H
#define EXPANDEDLISTVIEW_H

#include <QListView>
#include <QWidget>

class ExpandedListView : public QListView
{
    Q_OBJECT

protected slots:
    void updateGeometries();

public:
    ExpandedListView(QWidget *parent);
    int getContentsHeight();
};

#endif // EXPANDEDLISTVIEW_H
