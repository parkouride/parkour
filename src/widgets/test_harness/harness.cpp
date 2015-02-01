#include <QApplication>
#include <QLabel>
#include <QWidget>
int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    QLabel hello("<center>LedIDE Widget Test Harness</center>");
    hello.setWindowTitle("LedIDE Widget Test Harness");
    hello.resize(400, 400);
    hello.show();
    return app.exec();
}