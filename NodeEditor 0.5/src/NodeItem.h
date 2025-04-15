#pragma once

#include <QGraphicsItem>
#include <QString>
#include <vector>
#include <QPixmap>
#include "Port.h"

enum class NodeType {
    ImageLoader,
    Grayscale,
    Blur,
    Contrast,
    Brightness,
    Invert,
    Sharpen,
    EdgeDetect,
    SaveImage,
    Custom
};

class NodeItem : public QGraphicsItem {
public:
    NodeItem(NodeType type, const QString& title = "Node", QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setTitle(const QString& title);
    QString getTitle() const;

    void setImage(const QPixmap& pixmap);
    Port* getInputPort() const;
    Port* getOutputPort() const;

    NodeType nodeType() const;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QString m_title;
    QRectF m_rect;
    std::vector<Port*> m_inputPorts;
    std::vector<Port*> m_outputPorts;
    QPixmap m_image;
    NodeType m_type;

    void setupPorts();
};
