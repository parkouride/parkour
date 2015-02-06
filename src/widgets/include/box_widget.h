#pragma once

#include <QGraphicsItem>
#include <QRectF>
#include <vector>
#include <string>
#include <memory>

namespace led {
    namespace widget {
        
        class BoxPort;
        
        using PORT_LIST = std::vector<BoxPort*>;
        
        enum class PortType {
            inlet,
            outlet
        };
        
        class BoxWidget : public QGraphicsItem
        {
        public:
            BoxWidget();
            BoxWidget(const QString& initialName);
            
            virtual ~BoxWidget();
            
            QRectF boundingRect() const;
            void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
            
            void addPort(BoxPort *port, PortType type);
            
        private:
            QRectF outlineRect() const;
            void updatePortSizes(PORT_LIST& ports);
            
            QString m_name;
            PORT_LIST m_inlets;
            PORT_LIST m_outlets;
        };
        
    } // widget
} // led