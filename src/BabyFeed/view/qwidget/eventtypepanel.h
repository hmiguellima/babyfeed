#ifndef EVENTTYPEPANEL_H
#define EVENTTYPEPANEL_H

#include "kineticscrollarea.h"
#include "model/event.h"
#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QButtonGroup>
#include <QString>
#include <QChar>
#include <QHash>

class EventTypePanel : public KineticScrollArea
{
    Q_OBJECT

public:
    EventTypePanel(QWidget *parent);
    ~EventTypePanel();

    void setType(char type);
    char getType();
    PEvent getEvent();
    void setEnabled(bool enabled);
    void resetEventsData();

signals:
    void eventSelected(char type);

private:
    QPushButton *lButton;
    QPushButton *bButton;
    QPushButton *rButton;
    QPushButton *mButton;
    QPushButton *pButton;
    QPushButton *wButton;
    QSignalMapper *mapper;
    QButtonGroup *group;
    QHash<char, PEvent> eventMap;

    char type;

    void initButton(QPushButton* button, QString icon, QString name, char type, QFont& font, PEvent event);
private slots:
    void updateEventType(QString type);
    void scrollToSelectedEventType(char type);
};

#endif // EVENTTYPEPANEL_H
