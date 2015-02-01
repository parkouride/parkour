#pragma once

#include <QFrame>

class BoxWidget : public QFrame
{
    Q_OBJECT
public:
    BoxWidget(QWidget *parent = 0);
    ~BoxWidget();
    
signals:
    void connectionMade();
    void connectionRemoved();
    void selected();
    void editted();
    
};