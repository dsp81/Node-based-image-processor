#include "Port.h"
#include "NodeCanvas.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>


Port::Port(PortType type, int index, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_type(type), m_index(index)
{
    setFlags(ItemSendsGeometryChanges);
}

QRectF Port::boundingRect() const {
    return QRectF(-m_radius, -m_radius, m_radius * 2, m_radius * 2);
}




void Port::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setRenderHint(QPainter::Antialiasing);
    QColor fillColor = (m_type == PortType::Input) ? QColor("#ffffff") : QColor("#64b5f6");
    painter->setPen(Qt::black);
    painter->setBrush(fillColor);
    painter->drawEllipse(boundingRect());
}

PortType Port::portType() const {
    return m_type;
}

int Port::index() const {
    return m_index;
}

void Port::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton && scene()) {
        auto* view = scene()->views().first();
        if (auto* canvas = dynamic_cast<NodeCanvas*>(view)) {
            canvas->handlePortClick(this);
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void Port::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton && scene()) {
        auto* canvas = dynamic_cast<NodeCanvas*>(scene()->views().first());
        if (canvas) {
            canvas->handlePortClick(this);
        }
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

#include "Edge.h"

void Port::addEdge(Edge* edge) {
    m_edges.push_back(edge);
}

const std::vector<Edge*>& Port::edges() const {
    return m_edges;
}
