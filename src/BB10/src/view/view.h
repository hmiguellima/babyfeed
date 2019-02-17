#ifndef VIEW_H
#define VIEW_H

#include <QString>
#include <QObject>

class BabyFeedApp;

class View : public QObject
{
    Q_OBJECT
public:
    View(BabyFeedApp* window, QObject* parent);
    virtual QString url()=0;
    virtual QString viewName()=0;
    void setTitle(QString title);

signals:

public slots:
    void notifyActive();
    virtual void handleActivation()=0;
    void grabViewJpeg(QString fileName);

protected:
    BabyFeedApp* view();
    QObject* mainItem();

private:
    BabyFeedApp* _dView;
    QObject* _mainItem;
};

#endif // VIEW_H
