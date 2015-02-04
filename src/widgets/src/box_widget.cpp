#include "box_widget.h"
#include <QPainter>
#include <QLabel>
#include <QApplication>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

using namespace led::widget;

BoxWidget::BoxWidget()
    : BoxWidget("")
{
    
}

BoxWidget::BoxWidget(const QString& initialName)
{
    m_name = initialName;
    
    setFlags(ItemIsMovable | ItemIsSelectable);
}

BoxWidget::~BoxWidget()
{
    // Do Nothing
}

QRectF BoxWidget::boundingRect() const {
    const int MARGIN = 1;
    
    return outlineRect().adjusted(-MARGIN, -MARGIN, MARGIN, MARGIN);
}

QRectF BoxWidget::outlineRect() const {
    const int PADDING = 8;
    
    QFontMetricsF metrics = qApp->font();
    QRectF rect = metrics.boundingRect(m_name);
    rect.adjust(-PADDING, -PADDING, PADDING, PADDING);
    rect.translate(-rect.center());
    
    return rect;
}

void BoxWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const auto& palette = qApp->style()->standardPalette();
    QPen pen(palette.dark().color());
    const QPen& textPen(palette.text().color());
    const QBrush& background = palette.light().color();
    
    if (option->state & QStyle::State_Selected) {
        pen.setColor(palette.highlight().color());
    }
    
    QRectF rect = outlineRect();
    painter->setPen(pen);
    painter->setBrush(background);
    painter->drawRoundedRect(rect, 2.0, 2.0);
    
    painter->setPen(textPen);
    painter->drawText(rect, Qt::AlignCenter, m_name);
}