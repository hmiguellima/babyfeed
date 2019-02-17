#ifndef EVENTTYPEPANEL_H
#define EVENTTYPEPANEL_H

#include "kineticscrollarea.h"
#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QButtonGroup>
#include <QString>
#include <QChar>

class EventTypePanel : public KineticScrollArea
{
    Q_OBJECT

public:
    EventTypePanel(QWidget *parent);

    void setType(char type);
    char getType();
    void setEnabled(bool enabled);

signals:
    void eventSelected(char type);

private:
    QPushButton *lButton;
    QPushButton *bButton;
    QPushButton *rButton;
    QPushButton *mButton;
    QSignalMapper *mapper;
    QButtonGroup *group;
    char type;

private slots:
    void updateEventType(QString type);
    void scrollToSelectedEventType(char type);
};

#endif // EVENTTYPEPANEL_H
