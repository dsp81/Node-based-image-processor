#pragma once

#include <QMainWindow>
#include "NodeItem.h"
#include <QApplication>
class NodeCanvas;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void addNode(NodeType type);
    void saveScene();
    void loadScene();

private:
    NodeCanvas* m_canvas;
    void setupMenu();
};
