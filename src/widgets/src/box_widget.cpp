#include "box_widget.h"
#include <QPainter>

using namespace led::widget;

BoxWidget::BoxWidget(QWidget *parent)
: BoxWidget(parent, {}, {})
{
    
}

BoxWidget::BoxWidget(QWidget *parent, PORT_LIST_PTR inlets, PORT_LIST_PTR outlets)
    : QFrame(parent)
    , m_inlets(std::move(inlets))
    , m_outlets(std::move(outlets))
{
    
}

BoxWidget::~BoxWidget()
{
}

void BoxWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    
    painter.drawLine(0, 0, width(), height());
}

void BoxWidget::addConnectionPoint(std::string name, led::widget::PortType type)
{
    switch (type)
    {
        case PortType::inlet:
            m_inlets->push_back(name);
            emit addedInletPoint(name);
            break;
        case PortType::outlet:
            m_outlets->push_back(name);
            emit addedOutletPoint(name);
            break;
    }
}