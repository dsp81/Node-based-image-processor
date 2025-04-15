#include "MainWindow.h"
#include "NodeCanvas.h"
#include "NodeItem.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_canvas = new NodeCanvas(this);
    setCentralWidget(m_canvas);
    setupMenu();
}

void MainWindow::setupMenu() {
    QMenu* fileMenu = menuBar()->addMenu("File");

    fileMenu->addAction("Save Scene", this, SLOT(saveScene()));
    fileMenu->addAction("Load Scene", this, SLOT(loadScene()));
    fileMenu->addAction("Exit", qApp, SLOT(quit()));

    QMenu* addMenu = menuBar()->addMenu("Add Node");

    auto addNodeAction = [&](const QString& name, NodeType type) {
        QAction* action = new QAction(name, this);
        connect(action, &QAction::triggered, this, [=]() { addNode(type); });
        addMenu->addAction(action);
    };

    addNodeAction("Image Loader", NodeType::ImageLoader);
    addNodeAction("Grayscale",   NodeType::Grayscale);
    addNodeAction("Blur",        NodeType::Blur);
    addNodeAction("Contrast",    NodeType::Contrast);
    addNodeAction("Brightness",  NodeType::Brightness);
    addNodeAction("Invert",      NodeType::Invert);
    addNodeAction("Sharpen",     NodeType::Sharpen);
    addNodeAction("Edge Detect", NodeType::EdgeDetect);
    addNodeAction("Save Image",  NodeType::SaveImage);
}

void MainWindow::addNode(NodeType type) {
    QString title;

    switch (type) {
        case NodeType::ImageLoader: title = "Image Loader"; break;
        case NodeType::Grayscale:   title = "Grayscale";    break;
        case NodeType::Blur:        title = "Blur";         break;
        case NodeType::Contrast:    title = "Contrast";     break;
        case NodeType::Brightness:  title = "Brightness";   break;
        case NodeType::Invert:      title = "Invert";       break;
        case NodeType::Sharpen:     title = "Sharpen";      break;
        case NodeType::EdgeDetect:  title = "Edge Detect";  break;
        case NodeType::SaveImage:   title = "Save Image";   break;
        default:                    title = "Node";         break;
    }

    NodeItem* node = new NodeItem(type, title);
    m_canvas->addNode(node);
}

void MainWindow::saveScene() {
    QString filename = QFileDialog::getSaveFileName(this, "Save Scene", "", "JSON (*.json)");
    if (!filename.isEmpty()) {
        m_canvas->saveToJson(filename);
    }
}

void MainWindow::loadScene() {
    QString filename = QFileDialog::getOpenFileName(this, "Load Scene", "", "JSON (*.json)");
    if (!filename.isEmpty()) {
        m_canvas->loadFromJson(filename);
    }
}
