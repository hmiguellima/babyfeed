#ifndef LABELBAR_H
#define LABELBAR_H

#include <QLabel>

class LabelBar : public QLabel
{
    Q_OBJECT

protected:
    virtual void paintEvent(QPaintEvent *);

public:
    LabelBar(QWidget *parent = 0);
};

#endif // LABELBAR_H
