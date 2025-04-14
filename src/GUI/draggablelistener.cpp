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

