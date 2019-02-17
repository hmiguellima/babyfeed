#ifndef KINETICPAGES_H
#define KINETICPAGES_H

#include <QWidget>
#include <QObject>
#include <QScrollArea>
#include <QLabel>


class KineticPages : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY (qreal leftCueHPos READ getLeftCueHPos WRITE setLeftCueHPos)
    Q_PROPERTY (qreal rightCueHPos READ getRightCueHPos WRITE setRightCueHPos)
public:
    KineticPages(QWidget* parent = 0);

    void addWidget(QWidget* widget);
    void setVisibleWidget(QWidget* widget);
    void clearWidgets();
    void ensureWidgetVisible(QWidget* widget);

signals:
    void pageChanged(QWidget* widget);

protected:
    void resizeEvent(QResizeEvent * event);
    void paintEvent(QPaintEvent *);

private:
    QtScroller::State previousScrollerState;
    KineticScrollArea* scrollArea;
    QLabel* leftCueItem;
    QLabel* rightCueItem;
    QWidget* lastVisibleWidget;
    QtScroller *scroller;
    bool dragging;

    qreal getLeftCueHPos();
    void setLeftCueHPos(qreal pos);
    qreal getRightCueHPos();
    void setRightCueHPos(qreal pos);

private slots:
    void checkScrollerState(QtScroller::State scrollerState);
};

#endif // KINETICPAGES_H
