#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

namespace led {
    namespace widget {
        
        const int DEFAULT_SIZE = 500;
        
        class DevelopmentCanvas : public QGraphicsView {
        public:
            DevelopmentCanvas(QWidget *parent=nullptr);
            
            virtual ~DevelopmentCanvas();
            
            void addItem(QGraphicsItem *item);
        private:
            QGraphicsScene *scene;
        };
    }
}