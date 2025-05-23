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


WallRectItem::WallRectItem(const QRectF rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent),
    m_snapThreshold(80.0f),
    m_resizable(true),
    m_resizeMode(NoResize)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPen(QPen(Qt::black, 2));
    setBrush(QBrush(Qt::lightGray));

    std::shared_ptr<XWidget> xWidget = qvariant_cast<std::shared_ptr<XWidget>>(qApp->property("MainXWidget"));
    RoomMap* roomMap = xWidget->ui->roomMap;
    roomMap->scene->addItem(this);

    connect(this, &WallRectItem::itemSelected, [this, xWidget](WallRectItem* selectedWall) {
        xWidget->stackPanel->ui->occlusionFilterPanel->setFilter(&(selectedWall->filter));
    });

    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));

    mutex = audioManager->itemMutex;
    connect(this, &WallRectItem::needUpdateEffect, [=](){
        audioManager->updateEffectSlots();
        qDebug()<<audioManager->gridMeter;
    });

    initMenu();

    updateLocation(roomMap->mapToScene(roomMap->viewport()->rect().center()));
}

WallRectItem::~WallRectItem() {
    disconnect();
}

void WallRectItem::initMenu()
{
    menu = new QMenu();
    QAction *deleteAction = menu->addAction("删除");

    connect(deleteAction, &QAction::triggered, [=] () {
        std::shared_ptr<AudioManager> manager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
        //mutex->lockForWrite();
        manager->removeWallRectItem(filter.getFilterId());
        qDebug()<<"prepare for emit";
        emit needUpdateEffect();
        qDebug()<<"finish for emit";
        manager->updateEffectSlots();
        //mutex->unlock();
    });
}

void WallRectItem::updateLocation(const QPointF & newPos) {
    mutex->lockForWrite();
    qDebug()<<"before:"<<QPoint(leftTopX, leftTopY)<<" "<<width<<" "<<height;
    // std::shared_ptr<XWidget> xWidget = qvariant_cast<std::shared_ptr<XWidget>>(qApp->property("MainXWidget"));
    // RoomMap* roomMap = xWidget->ui->roomMap;
    // setPos(roomMap->mapToScene(newPos.toPoint()));
    setPos(newPos);
    leftTopX = pos().x() + rect().left();
    leftTopY = pos().y() + rect().top();
    width = rect().width();
    height = rect().height();
    qDebug()<<"after:"<<QPoint(leftTopX, leftTopY)<<" "<<rect().left()<<" "<<width<<" "<<height;
    mutex->unlock();
    emit needUpdateEffect();
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
    updateLocation(QPointF(snappedX, snappedY));
}



void WallRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_resizeMode != NoResize) {
        resizeItem(event->pos());
        updateLocation(QPointF(pos()));
    } else {
        // 平移模式
        QPointF delta = event->pos() - m_pressPos;
        updateLocation(((pos() + delta)));
    }
    qDebug()<<"moving";
    //std::shared_ptr<AudioManager> manager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    // QTimer::singleShot(0, manager.get(), &AudioManager::updateEffectSlots);
    // scene()->update();
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
    const float margin = 10.0f; // 边缘判定范围

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
    QPointF diff = pos - m_pressPos;

    diff.setX((round(diff.x() / GridSize) * GridSize));
    diff.setY((round(diff.y() / GridSize) * GridSize));

    // 记录当前“锚点”（变形参考点）在 scene 中的位置
    QPointF anchorPointLocal;
    switch (m_resizeMode) {
    case ResizeLeft:
    case ResizeTop:
    case ResizeTopLeft:
    case ResizeBottomLeft:
        anchorPointLocal = m_pressRect.topLeft();
        break;
    case ResizeRight:
    case ResizeTopRight:
    case ResizeBottomRight:
        anchorPointLocal = m_pressRect.topRight();
        break;
    case ResizeBottom:
        anchorPointLocal = m_pressRect.bottomLeft();
        break;
    default:
        anchorPointLocal = m_pressRect.topLeft();
        break;
    }
    QPointF anchorScenePos = mapToScene(anchorPointLocal);

    // 修改 rect
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
    if (newRect.width() < 50) {
        if (m_resizeMode == ResizeLeft || m_resizeMode == ResizeTopLeft || m_resizeMode == ResizeBottomLeft)
            newRect.setLeft(newRect.right() - 100);
        else
            newRect.setRight(newRect.left() + 100);
    }

    if (newRect.height() < 50) {
        if (m_resizeMode == ResizeTop || m_resizeMode == ResizeTopLeft || m_resizeMode == ResizeTopRight)
            newRect.setTop(newRect.bottom() - 100);
        else
            newRect.setBottom(newRect.top() + 100);
    }

    prepareGeometryChange();
    // qDebug()<<"newRect:"<<newRect.topLeft();
    // QPoint origin;
    // origin.setX(0), origin.setY(0);
    // newRect.setCoords(0, 0, newRect.width(), newRect.height());
    setRect(newRect);
    // qDebug()<<"rect:"<<rect().topLeft();

    // 获取调整后锚点在场景中的新位置
    QPointF newAnchorScenePos = mapToScene(anchorPointLocal);
    QPointF offset = newAnchorScenePos - anchorScenePos;

    // 修正 pos 保持锚点不动
    updateLocation(this->pos() - offset);
}

void WallRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->exec(event->screenPos());
}


QJsonObject WallRectItem::toJson() const {
    QReadLocker locker(mutex.get());
    QJsonObject obj;
    obj["leftTopX"] = leftTopX; // 以场景坐标保存
    obj["leftTopY"] = leftTopY;
    obj["width"] = width;
    obj["height"] = height;
    obj["filterGain"] = filter.gain;
    obj["filterGainHF"] = filter.gainHF;
    obj["filterGainLF"] = filter.gainLF;
    // obj[""]
    // 其他属性……
    return obj;
}

std::shared_ptr<WallRectItem> WallRectItem::createFromJson(const QJsonObject &obj) {
    QRectF rect(0, 0, obj["width"].toDouble(), obj["height"].toDouble());
    std::shared_ptr<WallRectItem> wall = std::make_shared<WallRectItem>(rect, nullptr);
    wall->updateLocation(QPointF(obj["leftTopX"].toDouble(), obj["leftTopY"].toDouble()));
    wall->mutex->lockForWrite();
    wall->filter.gain = obj["filterGain"].toDouble();
    wall->filter.gainHF = obj["filterGainHF"].toDouble();
    wall->filter.gainLF = obj["filterGainLF"].toDouble();
    // 其他属性……
    wall->mutex->unlock();
    return wall;
}
