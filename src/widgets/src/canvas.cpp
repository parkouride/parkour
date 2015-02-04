#include "canvas.h"

using namespace led::widget;

DevelopmentCanvas::DevelopmentCanvas(QWidget *parent)
    : QGraphicsView(parent), scene(nullptr)
{
    if (parent != nullptr) {
        scene = new QGraphicsScene(0,0, parent->width(), parent->height());
    } else {
        scene = new QGraphicsScene(0,0, DEFAULT_SIZE, DEFAULT_SIZE);
    }
    
    setScene(scene);
    setDragMode(QGraphicsView::RubberBandDrag);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

DevelopmentCanvas::~DevelopmentCanvas()
{
    if (scene != nullptr) {
        delete scene;
    }
}

void DevelopmentCanvas::addItem(QGraphicsItem *item)
{
    scene->addItem(item);
}