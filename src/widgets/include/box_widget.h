#pragma once

#include <QGraphicsItem>
#include <QRectF>
#include <vector>
#include <string>
#include <memory>

namespace led {
    namespace widget {
        
        class BoxPort;
        
        using PORT_LIST = std::vector<std::string>;
        using PORT_LIST_PTR = std::unique_ptr<PORT_LIST>;
        
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
            
            void addPort(std::shared_ptr<BoxPort> port, PortType type);
            
        private:
            QRectF outlineRect() const;
            
            QString m_name;
            PORT_LIST m_inlets, m_outlets;
        };
        
    } // widget
} // led