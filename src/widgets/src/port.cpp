#include "port.h"
#include "box_widget.cpp"

using namespace led::widget;

BoxPort::BoxPort(QString const& name)
    : m_name(name)
{
    setPen(QPen(DefaultPen));
    setBrush(DefaultPen);
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

void BoxPort::attach(BoxWidget *parent, int y_position)
{
    prepareGeometryChange();
    setParentItem(dynamic_cast<QGraphicsItem*>(parent));
    auto current_rectangle = rect();
    setRect(current_rectangle.x(), y_position, current_rectangle.width(), BoxPort::HEIGHT);
}

void BoxPort::updateSize(int x, int width)
{
    prepareGeometryChange();
    auto current_rectangle = rect();
    
    setRect(x, current_rectangle.y(), width, current_rectangle.height());
}

void BoxPort::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    setPen(QPen(HoverPen));
    setBrush(HoverPen);
}

void BoxPort::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    setPen(QPen(DefaultPen));
    setBrush(DefaultPen);
}

 QRectF BoxPort::boundingRect() const
{
    auto crect = rect();
    crect.adjust(-MARGIN, -MARGIN, MARGIN, MARGIN);
    
    return crect;
}