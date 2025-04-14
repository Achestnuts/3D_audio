#include "audiomanager.h"
#include "roommap.h"
#include "wallrectitem.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QDebug>
#include <cmath>
#include <QTimer>
#include <XWidget.h>
#include "ui_xwidget.h"

// const int GridSize = 10; // 假设网格大小为10

WallRectItem::WallRectItem(const QRectF rect, AudioManager* addManager, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent),
    m_snapThreshold(80.0f),
    m_resizable(true),
    m_resizeMode(NoResize),
    manager(addManager)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPen(QPen(Qt::black, 2));
    setBrush(QBrush(Qt::lightGray));

    RoomMap *roomMap = qvariant_cast<RoomMap*>(qApp->property("RoomMap"));
    roomMap->scene->addItem(this);
    setPos(roomMap->mapToScene(roomMap->viewport()->rect().center()));
    updateLocation();
    addManager->scene->addItem(this);
    addManager->walls[filter.getFilterId()] = this;
    //qDebug()<<pos();
    //setPos(rect.topLeft());

    //connect()
    XWidget* xWidget = qvariant_cast<XWidget*>(qApp->property("MainXWidget"));
    connect(this, &WallRectItem::itemSelected, [this, xWidget](WallRectItem* selectedWall) {
        xWidget->ui->occlusionFilterPanel->setFilter(&(selectedWall->filter));
    });

    initMenu();

}

void WallRectItem::initMenu()
{
    menu = new QMenu();
    // QAction *playVoiceAction = menu->addAction("播放");
    // QAction *setSourceFileAction = menu->addAction("设置音源");
    QAction *deleteAction = menu->addAction("删除");

    // connect(playVoiceAction, &QAction::triggered, this, &DraggableSource::playVoice);
    // connect(setSourceFileAction, &QAction::triggered, this, &DraggableSource::setAudioSourceFile);
    connect(deleteAction, &QAction::triggered, [this] () {
        manager->removeWallRectItem(filter.getFilterId());
    });
}

void WallRectItem::updateLocation() {
    leftTopX = pos().x();
    leftTopY = pos().y();
    width = rect().width();
    height = rect().height();
}

void WallRectItem::setSnapThreshold(float threshold) {
    m_snapThreshold = threshold;
}

float WallRectItem::snapThreshold() const {
    return m_snapThreshold;
}

void WallRectItem::setResizable(bool resizable) {
    m_resizable = resizable;
}

bool WallRectItem::isResizable() const {
    return m_resizable;
}

void WallRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_pressPos = event->pos();        // 在本地坐标中的按下点
    m_pressRect = rect();

    if (m_resizable) {
        m_resizeMode = hitTest(m_pressPos);
    } else {
        m_resizeMode = NoResize;
    }

    emit itemSelected(this);
    QGraphicsRectItem::mousePressEvent(event);
}

void WallRectItem::snapToGrid(int gridSize) {
    QPointF pos = scenePos();
    qreal snappedX = round(pos.x() / gridSize) * gridSize;
    qreal snappedY = round(pos.y() / gridSize) * gridSize;
    setPos(snappedX, snappedY);
}



void WallRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_resizeMode != NoResize) {
        resizeItem(event->pos());
    } else {
        // 平移模式
        QPointF delta = event->pos() - m_pressPos;
        RoomMap *roomMap = qvariant_cast<RoomMap*>(qApp->property("RoomMap"));
        setPos(((this->pos() + delta)));
        // qDebug()<<m_pressPos;
        // qDebug()<<event->pos();
        // qDebug()<<delta;
    }
    updateLocation();
    QTimer::singleShot(0, manager, &AudioManager::updateEffectSlots);
    scene()->update();
}

void WallRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mouseReleaseEvent(event);
    snapToGrid(GridSize);
}

QVariant WallRectItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        // 在这里可以添加自动吸附逻辑
        //qDebug()<<this->rect();
        return QGraphicsRectItem::itemChange(change, QVariant(newPos));
    }

    return QGraphicsRectItem::itemChange(change, value);
}

WallRectItem::ResizeMode WallRectItem::hitTest(const QPointF &pos) const {
    QRectF r = rect();
    const float margin = 80.0f; // 边缘判定范围

    bool left   = std::fabs(pos.x() - r.left())   < margin;
    bool right  = std::fabs(pos.x() - r.right())  < margin;
    bool top    = std::fabs(pos.y() - r.top())    < margin;
    bool bottom = std::fabs(pos.y() - r.bottom()) < margin;

    if (top && left) return ResizeTopLeft;
    if (top && right) return ResizeTopRight;
    if (bottom && left) return ResizeBottomLeft;
    if (bottom && right) return ResizeBottomRight;
    if (top) return ResizeTop;
    if (bottom) return ResizeBottom;
    if (left) return ResizeLeft;
    if (right) return ResizeRight;

    return NoResize;
}

void WallRectItem::resizeItem(const QPointF &pos) {
    QRectF newRect = m_pressRect;
    QPointF diff = pos - m_pressPos; // 本地坐标差
    //qDebug()<<"before:"<<diff;
    diff.setX((round(diff.x() / GridSize) * GridSize));
    diff.setY((round(diff.y() / GridSize) * GridSize));
    //qDebug()<<"after:"<<diff;

    switch (m_resizeMode) {
    case ResizeLeft:
        newRect.setLeft(m_pressRect.left() + diff.x());
        break;
    case ResizeRight:
        newRect.setRight(m_pressRect.right() + diff.x());
        break;
    case ResizeTop:
        newRect.setTop(m_pressRect.top() + diff.y());
        break;
    case ResizeBottom:
        newRect.setBottom(m_pressRect.bottom() + diff.y());
        break;
    case ResizeTopLeft:
        newRect.setLeft(m_pressRect.left() + diff.x());
        newRect.setTop(m_pressRect.top() + diff.y());
        break;
    case ResizeTopRight:
        newRect.setRight(m_pressRect.right() + diff.x());
        newRect.setTop(m_pressRect.top() + diff.y());
        break;
    case ResizeBottomLeft:
        newRect.setLeft(m_pressRect.left() + diff.x());
        newRect.setBottom(m_pressRect.bottom() + diff.y());
        break;
    case ResizeBottomRight:
        newRect.setRight(m_pressRect.right() + diff.x());
        newRect.setBottom(m_pressRect.bottom() + diff.y());
        break;
    default:
        break;
    }

    // 保持最小尺寸
    if (newRect.width() < 100) newRect.setWidth(100);
    if (newRect.height() < 100) newRect.setHeight(100);

    prepareGeometryChange();
    // qDebug()<<"before:"<<leftTopX<<" "<<leftTopY;
    setRect(newRect);
    // qDebug()<<"after:"<<leftTopX<<" "<<leftTopY;
}

void WallRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->exec(event->screenPos());
}
