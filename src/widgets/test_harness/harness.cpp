#include <memory>

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>

#include "box_widget.h"
#include "port.h"
#include "canvas.h"

class HarnessWindow : public QMainWindow
{
public:
    HarnessWindow() {
        view = new led::widget::DevelopmentCanvas(this);
        auto box = new led::widget::BoxWidget("Accel");
        box->setPos(150, 150);
        auto port = new led::widget::BoxPort("out");
        box->addPort(port, led::widget::PortType::outlet);
        
        port = new led::widget::BoxPort("data");
        box->addPort(port, led::widget::PortType::inlet);
        
        port = new led::widget::BoxPort("scene");
        box->addPort(port, led::widget::PortType::outlet);
        
        view->addItem(box);
        
        box = new led::widget::BoxWidget("OnValueThresholds");
        box->setPos(250, 250);
        view->addItem(box);
        setCentralWidget(view);
        
        setWindowTitle("LedIDE Widget Test Harness");
    }
    
private:
    led::widget::DevelopmentCanvas *view;
};

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    HarnessWindow window;
    window.show();

    return app.exec();
}