#ifndef SCREEN_H
#define SCREEN_H
#include "view/view.h"
#include <QString>

class BabyFeedApp;

class Screen: public QObject
{
    Q_OBJECT

public:
    Screen(BabyFeedApp* dView);
    QString getViewUrl();
    View* getView();

signals:
	void screenInactive();

public slots:
    void show();
    virtual void viewReadyHandler() = 0;
    void notifyActive();
    void notifyInactive();

protected:
    BabyFeedApp* getWindow();
    void setView(View* view);
    void setTitle(QString title);

private:
    BabyFeedApp* window;
    View* view;
};

#endif // SCREEN_H
