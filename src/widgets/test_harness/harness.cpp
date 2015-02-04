#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include "box_widget.h"
#include "canvas.h"

class HarnessWindow : public QMainWindow
{
public:
    HarnessWindow() {
        view = new led::widget::DevelopmentCanvas(this);
        view->addItem(new led::widget::BoxWidget("Accelerometer"));
        view->addItem(new led::widget::BoxWidget("OnValueThresholds"));
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