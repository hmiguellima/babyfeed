#include "view.h"
#include <QTimer>
#include <QWidget>
#include <QVBoxLayout>
#include "mainwindow.h"
#include <QGraphicsObject>

View::View(MainWindow* dView, QObject* parent) : QObject(parent),
    _dView(dView), _mainItem(0)
{
}

MainWindow* View::view()
{
    return _dView;
}

void View::notifyActive()
{
    _mainItem=view()->rootObject()->findChild<QObject*>(viewName());
    handleActivation();
}

QObject * View::mainItem()
{
    return _mainItem;
}

void View::setTitle(QString title)
{
    _mainItem->setProperty("pageTitleText", QVariant(title));
}

