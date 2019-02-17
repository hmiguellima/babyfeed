#include "kineticpages.h"
#include "qtkineticscroller/qtscrollerproperties.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QLabel>
#include <QResizeEvent>

KineticPages::KineticPages(QWidget* parent) : QScrollArea(parent)
{
    QtScrollerProperties props;
    QWidget* container = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout();
    QSpacerItem* spacer;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->setSpacing(0);
    layout->setMargin(0);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWidgetResizable(true);
    setAutoFillBackground(true);

    scrollArea=new KineticScrollArea(0);
    scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    scrollArea->setFixedWidth(360);
    scroller=QtScroller::scroller(scrollArea->viewport());
    props.setScrollMetric(QtScrollerProperties::DecelerationFactor, 0);
    props.setScrollMetric(QtScrollerProperties::MaximumVelocity, 0);
    scroller->setScrollerProperties(props);


    container->setObjectName("kineticPagesContainer");
    container->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    container->setFixedWidth(440);
    container->setBackgroundRole(QPalette::Base);

    setWidget(container);

    container->setLayout(layout);

    spacer=new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    layout->addItem(spacer);

    layout->addWidget(scrollArea);
    layout->setAlignment(scrollArea, Qt::AlignTop);

    spacer=new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    layout->addItem(spacer);

    leftCueItem = new QLabel(container);
    leftCueItem->setFixedSize(40, 45);
    leftCueItem->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/leftarrowcue.png")));

    rightCueItem = new QLabel(container);
    rightCueItem->setFixedSize(40, 45);
    rightCueItem->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/rightarrowcue.png")));

    connect(scroller, SIGNAL(stateChanged(QtScroller::State)), SLOT(checkScrollerState(QtScroller::State)));
    previousScrollerState=QtScroller::Inactive;
    lastVisibleWidget = 0;
    dragging = false;
}

void KineticPages::addWidget(QWidget *widget)
{
    scrollArea->addWidget(widget);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    widget->setFixedWidth(354);
    horizontalScrollBar()->setValue(41);
    if (lastVisibleWidget==0)
        lastVisibleWidget=widget;
}

void KineticPages::checkScrollerState(QtScroller::State scrollerState)
{
    QRect visibleRect;
    QRect widgetRect;
    QObject *object;
    QObjectList children;
    QWidget *widget;

    if (scrollerState==QtScroller::Dragging)
        dragging=true;

    if (previousScrollerState==QtScroller::Dragging)
    {
        visibleRect=QRect(-scrollArea->scrollerContents->pos(), scrollArea->viewport()->size());
        children=scrollArea->scrollerContents->children();

        foreach(object,children)
        {
            widget=dynamic_cast<QWidget*>(object);
            if (widget)
            {
                widgetRect=QRect(widget->mapToParent(QPoint(0, 0)), widget->mapToParent(QPoint(widget->size().width(), widget->size().height())));
                if ((visibleRect.intersect(widgetRect)).width()>=visibleRect.width()/2)
                {
                    scrollArea->ensureWidgetVisible(widget);
                    if (lastVisibleWidget!=widget)
                        emit pageChanged(widget);
                    lastVisibleWidget = widget;
                    dragging=false;
                    break;
                }

            }
        }
    }
    previousScrollerState=scrollerState;
    horizontalScrollBar()->setValue(41);
}

void KineticPages::setVisibleWidget(QWidget* widget)
{
    QPropertyAnimation* leftCueAnim=new QPropertyAnimation(this, "leftCueHPos");
    QPropertyAnimation* rightCueAnim=new QPropertyAnimation(this, "rightCueHPos");
    qreal clientHeight=QApplication::desktop()->availableGeometry().height();

    scrollArea->ensureWidgetVisible(widget, 0, 0);

    leftCueItem->pos().setY((clientHeight/2)-22);
    rightCueItem->pos().setY((clientHeight/2)-22);

    leftCueAnim->setEasingCurve(QEasingCurve::InOutElastic);
    leftCueAnim->setDuration(4000);
    leftCueAnim->setStartValue(45);
    leftCueAnim->setEndValue(0);
    leftCueAnim->start(QAbstractAnimation::DeleteWhenStopped);

    rightCueAnim->setEasingCurve(QEasingCurve::InOutElastic);
    rightCueAnim->setDuration(4000);
    rightCueAnim->setStartValue(355);
    rightCueAnim->setEndValue(401);
    rightCueAnim->start(QAbstractAnimation::DeleteWhenStopped);

    horizontalScrollBar()->setValue(41);
    lastVisibleWidget = widget;
}

qreal KineticPages::getLeftCueHPos()
{
    return leftCueItem->pos().x();
}

qreal KineticPages::getRightCueHPos()
{
    return rightCueItem->pos().x();
}

void KineticPages::setLeftCueHPos(qreal pos)
{
    leftCueItem->setGeometry(QRect(QPoint(pos, leftCueItem->pos().y()), leftCueItem->size()));
}

void KineticPages::setRightCueHPos(qreal pos)
{
    rightCueItem->setGeometry(QRect(QPoint(pos, rightCueItem->pos().y()), rightCueItem->size()));
}

void KineticPages::clearWidgets()
{
    scrollArea->clearWidgets();
    lastVisibleWidget=0;
}

void KineticPages::ensureWidgetVisible(QWidget* widget)
{
    setVisibleWidget(widget);
    horizontalScrollBar()->setValue(41);
}

void KineticPages::resizeEvent(QResizeEvent * event)
{
    int yPos = (event->size().height() / 2) - 22;
    leftCueItem->setGeometry(QRect(QPoint(leftCueItem->pos().x(), yPos), leftCueItem->size()));
    rightCueItem->setGeometry(QRect(QPoint(rightCueItem->pos().x(), yPos), rightCueItem->size()));
    scrollArea->setFixedHeight(event->size().height());
    horizontalScrollBar()->setValue(41);
}

void KineticPages::paintEvent(QPaintEvent *)
{
    horizontalScrollBar()->setValue(41);
    if ( (lastVisibleWidget) && (!dragging) )
        scrollArea->ensureWidgetVisible(lastVisibleWidget);
}
