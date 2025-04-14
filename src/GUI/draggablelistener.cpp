#include "draggablelistener.h"

DraggableListener::DraggableListener(AudioManager *newManager)
    : DraggableItem(QString(":/icons/listener.svg"), newManager)
{
    //manager->updateListener(10, 10, RoomHeight);
    // setPos(10, 10);
}

void DraggableListener::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastMousePos = event->scenePos();
    dragging = true;
    setZValue(1); // 选中后置顶
    emit itemSelected(this);
    QGraphicsPixmapItem::mousePressEvent(event);
}


void DraggableListener::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) {
        QPointF delta = event->scenePos() - lastMousePos;
        setPos(this->pos() + delta);
        lastMousePos = event->scenePos();
        if(manager) {
            manager->updateListener(this->pos().x(), this->pos().y(), RoomHeight); // 更新位置
        }
    }
}


void DraggableListener::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    menu->exec(event->screenPos());
}
void DraggableListener::initMenu(){

}

QJsonObject DraggableListener::toJson() const {
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

DraggableListener* DraggableListener::createFromJson(const QJsonObject &obj) {
    QRectF rect(0, 0, obj["width"].toDouble(), obj["height"].toDouble());
    WallRectItem* wall = new WallRectItem(rect);
    wall->updateLocation(QPointF(obj["leftTopX"].toDouble(), obj["leftTopY"].toDouble()));
    wall->filter.gain = obj["filterGain"].toDouble();
    wall->filter.gainHF = obj["filterGainHF"].toDouble();
    wall->filter.gainLF = obj["filterGainLF"].toDouble();
    // 其他属性……
    return wall;
}
