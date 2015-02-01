#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include "box_widget.h"

class HarnessWindow : public QMainWindow
{
public:
    HarnessWindow() {
        QGridLayout* layout = new QGridLayout;
        
        QWidget* boxWidget = new led::widget::BoxWidget;
        layout->addWidget(boxWidget);
        
        QWidget* central = new QWidget;
        setCentralWidget(central);
        central->setLayout(layout);
        
        setWindowTitle("LedIDE Widget Test Harness");
        setFixedSize(400, 400);
    }
};

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    HarnessWindow window;
    window.show();

    return app.exec();
}