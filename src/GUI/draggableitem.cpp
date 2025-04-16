#include "draggableitem.h"

DraggableItem::DraggableItem(const QPixmap &icon)
    : QGraphicsPixmapItem(QPixmap(icon).scaled(100, 100, Qt::KeepAspectRatio))
{
    setFlags(ItemIsMovable | ItemIsSelectable); // 允许拖动和选择
}

void DraggableItem::initMenu()
{
    // menu = new QMenu();
    // QAction *playSourceAction = menu->addAction("播放");
    // QAction *deleteAction = menu->addAction("删除");

    //connect(playSourceAction, &QAction::triggered, this, &DraggableSource::playSource);
}

// void DraggableItem::setManager(AudioManager* newManager)
// {
//     manager = newManager;
// }

void DraggableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastMousePos = event->scenePos();
    dragging = true;
    setZValue(1); // 选中后置顶
    QGraphicsPixmapItem::mousePressEvent(event);
}

void DraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // if (dragging) {
    //     QPointF delta = event->scenePos() - lastMousePos;
    //     setPos(this->pos() + delta);
    //     lastMousePos = event->scenePos();
    //     if(manager) {
    //         manager->updateAudioSource(sourceId, this->pos().x(), this->pos().y(), 1.0f); // 更新位置
    //     }
    // }
}

void DraggableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    dragging = false;
    setZValue(0);
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void DraggableItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    //qDebug()<<"this way sir";
    // QAction *editAction = menu.addAction("播放");
    // QAction *deleteAction = menu.addAction("删除");

    // QAction *selectedAction = menu.exec(event->screenPos());
    // if (selectedAction == editAction) {
    //     qDebug() << "编辑 Item"<<manager;
    //     manager->playAll();
    //     //manager->saveToFile("scene.json");
    //     // 处理编辑操作
    // } else if (selectedAction == deleteAction) {
    //     qDebug() << "删除 Item";
    //     //delete this;
    // }
    // qDebug()<<"is playing?"<<manager->sources[sourceId]->isPlaying();
}

// void DraggableItem::onAddActionTriggered()
// {
//     // 当添加操作被触发时执行的代码
// }
