#pragma once

#include <QFrame>
#include <vector>
#include <string>
#include <memory>

namespace led {
    namespace widget {
        
        using PORT_LIST = std::vector<std::string>;
        using PORT_LIST_PTR = std::unique_ptr<PORT_LIST>;
        
        enum class PortType {
            inlet,
            outlet
        };
        
        class BoxWidget : public QFrame
        {
            Q_OBJECT
        public:
            BoxWidget(QWidget *parent = 0);
            BoxWidget(QWidget *parent, PORT_LIST_PTR inlets, PORT_LIST_PTR outlets);
            ~BoxWidget();
            
            void addConnectionPoint(std::string name, PortType type);
            
        protected:
            void paintEvent(QPaintEvent *event);
            
        private:
            PORT_LIST_PTR m_inlets, m_outlets;
            
            
        signals:
            void addedInletPoint(std::string name);
            void addedOutletPoint(std::string name);
        };
        
    } // widget
} // led