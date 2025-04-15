#include "NodeCanvas.h"
#include "NodeItem.h"
#include "Edge.h"
#include "Port.h"

#include <QMouseEvent>
#include <QGraphicsScene>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

NodeCanvas::NodeCanvas(QWidget *parent)
    : QGraphicsView(parent), m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);
    m_scene->setSceneRect(0, 0, 1200, 900);
}

void NodeCanvas::addNode(NodeItem* node) {
    m_scene->addItem(node);
    node->setPos(100 + (m_scene->items().size() * 30), 100 + (m_scene->items().size() * 20));
}

void NodeCanvas::handlePortClick(Port* clickedPort) {
    if (!m_selectedPort) {
        m_selectedPort = clickedPort;
        return;
    }

    Port* from = nullptr;
    Port* to = nullptr;

    if (m_selectedPort->portType() == PortType::Output && clickedPort->portType() == PortType::Input) {
        from = m_selectedPort;
        to = clickedPort;
    } else if (m_selectedPort->portType() == PortType::Input && clickedPort->portType() == PortType::Output) {
        from = clickedPort;
        to = m_selectedPort;
    }

    if (from && to) {
        for (auto it = m_edges.begin(); it != m_edges.end(); ++it) {
            Edge* edge = *it;
            if ((edge->startPort() == from && edge->endPort() == to) ||
                (edge->startPort() == to && edge->endPort() == from)) {
                m_scene->removeItem(edge);
                delete edge;
                m_edges.erase(it);
                m_selectedPort = nullptr;
                return;
            }
        }

        Edge* edge = new Edge(from, to);
        m_scene->addItem(edge);
        m_edges.push_back(edge);

        from->addEdge(edge);
        to->addEdge(edge);
    }

    m_selectedPort = nullptr;
}

void NodeCanvas::mouseMoveEvent(QMouseEvent* event) {
    QGraphicsView::mouseMoveEvent(event);
    for (Edge* edge : m_edges)
        edge->updatePosition();
}

void NodeCanvas::saveToJson(const QString& filename) {
    QJsonArray nodesArray;
    QJsonArray edgesArray;
    QList<NodeItem*> nodeList;

    // Collect all NodeItems in order
    for (QGraphicsItem* item : m_scene->items()) {
        if (auto* node = dynamic_cast<NodeItem*>(item)) {
            nodeList.prepend(node);  // Maintain stacking order

            QJsonObject obj;
            obj["type"] = static_cast<int>(node->nodeType());
            obj["title"] = node->getTitle();
            obj["x"] = node->pos().x();
            obj["y"] = node->pos().y();
            nodesArray.append(obj);
        }
    }

    // Save edges by node index
    for (Edge* edge : m_edges) {
        NodeItem* fromNode = dynamic_cast<NodeItem*>(edge->startPort()->parentItem());
        NodeItem* toNode   = dynamic_cast<NodeItem*>(edge->endPort()->parentItem());

        int fromIndex = nodeList.indexOf(fromNode);
        int toIndex = nodeList.indexOf(toNode);

        if (fromIndex != -1 && toIndex != -1) {
            QJsonObject edgeObj;
            edgeObj["fromIndex"] = fromIndex;
            edgeObj["toIndex"] = toIndex;
            edgesArray.append(edgeObj);
        }
    }

    QJsonObject root;
    root["nodes"] = nodesArray;
    root["edges"] = edgesArray;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
        file.close();
    }
}


void NodeCanvas::loadFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray nodesArray = root["nodes"].toArray();
    QJsonArray edgesArray = root["edges"].toArray();

    m_scene->clear();
    m_edges.clear();

    QList<NodeItem*> createdNodes;

    for (const QJsonValue& val : nodesArray) {
        QJsonObject obj = val.toObject();
        NodeType type = static_cast<NodeType>(obj["type"].toInt());
        QString title = obj["title"].toString();
        qreal x = obj["x"].toDouble();
        qreal y = obj["y"].toDouble();

        NodeItem* node = new NodeItem(type, title);
        node->setPos(x, y);
        m_scene->addItem(node);
        createdNodes.append(node);
    }

    for (const QJsonValue& val : edgesArray) {
        QJsonObject obj = val.toObject();
        int fromIndex = obj["fromIndex"].toInt();
        int toIndex = obj["toIndex"].toInt();

        if (fromIndex >= 0 && fromIndex < createdNodes.size() &&
            toIndex >= 0 && toIndex < createdNodes.size()) {
            Port* from = createdNodes[fromIndex]->getOutputPort();
            Port* to = createdNodes[toIndex]->getInputPort();
            Edge* edge = new Edge(from, to);
            m_scene->addItem(edge);
            m_edges.push_back(edge);

            from->addEdge(edge);
            to->addEdge(edge);
        }
    }
}
