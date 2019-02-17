#ifndef VIEW_H
#define VIEW_H

#include <QString>
#include <QObject>

class MainWindow;

class View : public QObject
{
    Q_OBJECT
public:
    View(MainWindow* window, QObject* parent);
    virtual QString url()=0;
    virtual QString viewName()=0;
    void setTitle(QString title);

signals:

public slots:
    void notifyActive();
    virtual void handleActivation()=0;

protected:
    MainWindow* view();
    QObject* mainItem();

private:
    MainWindow* _dView;
    QObject* _mainItem;
};

#endif // VIEW_H
