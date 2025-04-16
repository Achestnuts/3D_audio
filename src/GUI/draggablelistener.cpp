#include "draggablelistener.h"
#include <audiomanager.h>
#include <qcoreapplication.h>

DraggableListener::DraggableListener()
    : DraggableItem(QString(":/icons/listener.svg"))
{
    // listener = std::make_shared<Listener>();
    // std::shared_ptr<AudioManager> audiomanager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    // audiomanager->listener = listener;
    //manager->updateListener(10, 10, RoomHeight);
    // setPos(10, 10);
    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    mutex = audioManager->itemMutex;
}

void DraggableListener::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastMousePos = event->scenePos();
    dragging = true;
    setZValue(1); // 选中后置顶
    emit itemSelected(this);
    QGraphicsPixmapItem::mousePressEvent(event);
}

void DraggableListener::setListener(std::shared_ptr<Listener> newListener) {

    QWriteLocker locker(mutex.get());
    std::shared_ptr<AudioManager> audiomanager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    if(newListener && audiomanager->listenerIsExist(newListener)) {
        listener = newListener;
    }
}

void DraggableListener::setPosition(QPointF newPos) {
    QWriteLocker locker(mutex.get());
    setPos(newPos);
    if(listener) {
        listener->setPosition(pos().x(), pos().y(), RoomHeight);
    }
}

void DraggableListener::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) {
        QPointF delta = event->scenePos() - lastMousePos;
        // setPos(this->pos() + delta);
        // if(manager) {
        //     manager->updateListener(this->pos().x(), this->pos().y(), RoomHeight); // 更新位置
        // }
        setPosition(this->pos() + delta);
        lastMousePos = event->scenePos();

    }
}


void DraggableListener::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    menu->exec(event->screenPos());
}
void DraggableListener::initMenu(){

}

// QJsonObject DraggableListener::toJson() const {
//     QJsonObject obj;
//     obj["posX"] = listener->posX;
//     obj["posY"] = listener->posY;
//     obj["posZ"] = listener->posZ;
//     // obj["leftTopX"] = leftTopX; // 以场景坐标保存
//     // obj["leftTopY"] = leftTopY;
//     // obj["width"] = width;
//     // obj["height"] = height;
//     // obj["filterGain"] = filter.gain;
//     // obj["filterGainHF"] = filter.gainHF;
//     // obj["filterGainLF"] = filter.gainLF;
//     // obj[""]
//     // 其他属性……
//     return obj;
// }

// DraggableListener* DraggableListener::createFromJson(const QJsonObject &obj) {
//     QRectF rect(0, 0, obj["width"].toDouble(), obj["height"].toDouble());
//     WallRectItem* wall = new WallRectItem(rect);
//     wall->updateLocation(QPointF(obj["leftTopX"].toDouble(), obj["leftTopY"].toDouble()));
//     wall->filter.gain = obj["filterGain"].toDouble();
//     wall->filter.gainHF = obj["filterGainHF"].toDouble();
//     wall->filter.gainLF = obj["filterGainLF"].toDouble();
//     // 其他属性……
//     return wall;
// }
