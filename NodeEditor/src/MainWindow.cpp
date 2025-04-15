#include "MainWindow.h"
#include "NodeCanvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    NodeCanvas* canvas = new NodeCanvas(this);
    setCentralWidget(canvas);
}
