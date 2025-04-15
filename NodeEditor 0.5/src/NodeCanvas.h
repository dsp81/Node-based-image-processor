#pragma once

#include <QGraphicsView>
#include <vector>
#include <QList>          // Required for node reconstruction
#include <QString>        // Required for file paths

class NodeItem;
class Edge;
class Port;

class NodeCanvas : public QGraphicsView {
    Q_OBJECT
public:
    NodeCanvas(QWidget* parent = nullptr);

    void handlePortClick(Port* port);
    void addNode(NodeItem* node);

    // ✅ Save/Load functionality
    void saveToJson(const QString& filename);
    void loadFromJson(const QString& filename);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QGraphicsScene* m_scene;
    Port* m_selectedPort = nullptr;
    std::vector<Edge*> m_edges;
};
