#include "NodeItem.h"
#include <QPainter>
#include <QFont>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>

NodeItem::NodeItem(NodeType type, const QString& title, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_title(title), m_rect(0, 0, 160, 140), m_type(type)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setupPorts();
}

QRectF NodeItem::boundingRect() const {
    return m_rect.adjusted(-1, -1, 1, 1);
}

void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::black);
    painter->setBrush(QColor("#d0e1f9"));
    painter->drawRoundedRect(m_rect, 10, 10);

    painter->setFont(QFont("Segoe UI", 10, QFont::Bold));
    painter->drawText(m_rect.adjusted(10, 5, -10, -10), Qt::AlignTop | Qt::AlignLeft, m_title);

    if (!m_image.isNull()) {
        QRectF imageRect = m_rect.adjusted(10, 25, -10, -10);
        painter->drawPixmap(imageRect.toRect(), m_image.scaled(imageRect.size().toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void NodeItem::setImage(const QPixmap& pixmap) {
    m_image = pixmap;
    update();
}

void NodeItem::setTitle(const QString& title) {
    m_title = title;
    update();
}

QString NodeItem::getTitle() const {
    return m_title;
}

Port* NodeItem::getInputPort() const {
    return m_inputPorts.empty() ? nullptr : m_inputPorts[0];
}

Port* NodeItem::getOutputPort() const {
    return m_outputPorts.empty() ? nullptr : m_outputPorts[0];
}

NodeType NodeItem::nodeType() const {
    return m_type;
}


void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Check if click is inside the body (not on a port)
    QPointF localPos = event->pos();
    bool clickedInside = boundingRect().contains(localPos);

    if (clickedInside && m_type == NodeType::ImageLoader) {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Image", "", "Images (*.png *.jpg *.bmp)");
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (!image.isNull()) {
                setImage(QPixmap::fromImage(image));
            } else {
                qDebug("❌ Failed to load image: %s", qUtf8Printable(fileName));
            }
        }
    }

    QGraphicsItem::mousePressEvent(event);
}


void NodeItem::setupPorts() {
    if (m_type != NodeType::ImageLoader) {
        Port* inPort = new Port(PortType::Input, 0, this);
        inPort->setPos(m_rect.left(), m_rect.center().y());
        m_inputPorts.push_back(inPort);
    }

    if (m_type != NodeType::SaveImage) {
        Port* outPort = new Port(PortType::Output, 0, this);
        outPort->setPos(m_rect.right(), m_rect.center().y());
        m_outputPorts.push_back(outPort);
    }
}
