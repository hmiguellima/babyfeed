#include "labelbar.h"
#include <QStylePainter>
#include <QStyleOptionButton>

LabelBar::LabelBar(QWidget *parent):QLabel(parent)
{
}

void LabelBar::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    QStyleOptionButton option;

    option.initFrom(this);
    painter.drawPrimitive(QStyle::PE_PanelButtonTool, option);

    QLabel::paintEvent(event);
}
