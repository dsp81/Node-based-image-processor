#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <vector>

enum class PortType {
    Input,
    Output
};

class Edge;  // Forward declaration

class Port : public QGraphicsItem {
public:
    Port(PortType type, int index, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    PortType portType() const;
    int index() const;

    void addEdge(Edge* edge);
    const std::vector<Edge*>& edges() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    PortType m_type;
    int m_index;
    qreal m_radius = 6;
    std::vector<Edge*> m_edges;
};
