#include "expandedlistview.h"

ExpandedListView::ExpandedListView(QWidget *parent) : QListView(parent)
{
}

int ExpandedListView::getContentsHeight()
{
    return contentsSize().height();
}

void ExpandedListView::updateGeometries()
{
    int height;

    QListView::updateGeometries();

    height=getContentsHeight();
    setMinimumHeight(height+10);
}
