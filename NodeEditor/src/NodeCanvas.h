#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

class NodeCanvas : public QGraphicsView {
    Q_OBJECT
public:
    NodeCanvas(QWidget *parent = nullptr);
};
