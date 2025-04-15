#pragma once

#include <QGraphicsPathItem>

class Port;

class Edge : public QGraphicsPathItem {
public:
    Edge(Port* from, Port* to, QGraphicsItem* parent = nullptr);
    void updatePosition();

    // ✅ Make these public so NodeCanvas can query ports
    Port* startPort() const { return m_from; }
    Port* endPort() const { return m_to; }

private:
    Port* m_from;
    Port* m_to;
};
