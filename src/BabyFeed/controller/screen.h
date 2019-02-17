#ifndef SCREEN_H
#define SCREEN_H
#include "view/view.h"
#include <QWidget>
#include <QString>
#include <QDeclarativeView>

class MainWindow;

class Screen: public QWidget
{
    Q_OBJECT

public:
    Screen(MainWindow* dView);
    QString getViewUrl();
    View* getView();

public slots:
    void show();
    virtual void viewReadyHandler() = 0;
    void notifyActive();

protected:
    MainWindow* getWindow();
    void setView(View* view);
    void setTitle(QString title);

private:
    MainWindow* window;
    View* view;
};

#endif // SCREEN_H
