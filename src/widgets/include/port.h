#pragma once

#include <QGraphicsRectItem>
#include <QString>


namespace led {
    namespace widget {
        
        class BoxWidget;
        
        class BoxPort : public QGraphicsRectItem {
        public:
            static const int MARGIN = 3;
            BoxPort(QString const& name);
            
            void attach(BoxWidget* parent, int y_position);
            void updateSize(int x, int width);

            static const int HEIGHT = 5;
        protected:
            void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
            void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
            QRectF boundingRect() const override;
            
        private:
            QString m_name;

            static const auto HoverPen = Qt::red;
            static const auto DefaultPen = Qt::darkRed;

        };
    }
}