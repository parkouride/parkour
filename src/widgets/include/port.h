#pragma once

#include <QGraphicsPathItem> 
#include <QPath>
#include <QString>

namespace led {
    namespace widget {
        class BoxPort : public QGraphicsPathItem {
        public:
            BoxPort(const QString& name);
            
        protected:
            
        private:
            QString m_name;
        };
    }
}