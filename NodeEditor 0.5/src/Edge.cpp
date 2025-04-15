#include "Edge.h"
#include "Port.h"
#include <QPainterPath>
#include <QPen>

Edge::Edge(Port* from, Port* to, QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_from(from), m_to(to)
{
    setZValue(-1);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    updatePosition();
}

void Edge::updatePosition() {
    if (!m_from || !m_to) return;

    QPointF start = m_from->scenePos();
    QPointF end = m_to->scenePos();
    qreal dx = (end.x() - start.x()) * 0.5;

    QPainterPath path(start);
    path.cubicTo(start.x() + dx, start.y(), end.x() - dx, end.y(), end.x(), end.y());
    setPath(path);
}
