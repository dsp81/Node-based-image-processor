#include "NodeCanvas.h"
#include <QGraphicsEllipseItem>

NodeCanvas::NodeCanvas(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);

    auto* circle = scene->addEllipse(100, 100, 100, 100,
                                     QPen(Qt::black), QBrush(Qt::lightGray));
    circle->setFlag(QGraphicsItem::ItemIsMovable);
    scene->setSceneRect(0, 0, 800, 600);
}
