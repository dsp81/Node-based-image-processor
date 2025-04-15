#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Node-Based Image Editor");
    window.resize(1200, 900);
    window.show();
    return app.exec();
}
