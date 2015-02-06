#include "box_widget.h"
#include "port.h"
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
    : m_inlets()
    , m_outlets()
{
    m_name = initialName;
    
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);
}

BoxWidget::~BoxWidget()
{
    // TODO: Delete all ports
}

QRectF BoxWidget::boundingRect() const {
    const int MARGIN = 1;
    
    return outlineRect().adjusted(-MARGIN, -MARGIN, MARGIN, MARGIN);
}

QRectF BoxWidget::outlineRect() const {
    const int PADDING = 8;
    
    QFontMetricsF metrics = qApp->font();
    QRectF rect = metrics.boundingRect(m_name);
    rect.adjust(-PADDING, -PADDING*1.5, PADDING, PADDING*1.5);
    rect.translate(-rect.center());
    
    return rect;
}

void BoxWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const auto& palette = qApp->style()->standardPalette();
    QPen pen(palette.dark().color());
    const QPen& textPen(palette.text().color());
    QBrush background = palette.light().color();
    
    if (option->state & QStyle::State_Selected) {
        pen.setColor(palette.highlight().color());
    }
    
    if (option->state & QStyle::State_MouseOver) {
        background.setColor(palette.midlight().color());
    }
    
    QRectF rect = outlineRect();
    painter->setPen(pen);
    painter->setBrush(background);
    painter->drawRoundedRect(rect, 2.0, 2.0);
    
    painter->setPen(textPen);
    painter->drawText(rect, Qt::AlignCenter, m_name);
}

void BoxWidget::addPort(BoxPort *port, PortType type)
{
    int y_position = 0;
    switch(type) {
        case PortType::inlet:
            m_inlets.push_back(port);
            updatePortSizes(m_inlets);
            break;
            
        case PortType::outlet:
            y_position = this->outlineRect().height() - BoxPort::HEIGHT;
            m_outlets.push_back(port);
            updatePortSizes(m_outlets);
            break;
    }
    y_position += this->outlineRect().y();
    port->attach(this, y_position);
}

void BoxWidget::updatePortSizes(PORT_LIST &ports)
{
    
    int width = 8;
    int start_x = this->outlineRect().x();
    
    for (auto& port : ports)
    {
        port->updateSize(start_x, width);
        start_x += width + BoxPort::MARGIN;
    }
}