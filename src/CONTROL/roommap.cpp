#include "roommap.h"
#include "mapscene.h"
#include "draggablesource.h"

#include <QGraphicsEllipseItem>
#include <QFileDialog>
#include<QMenu>



RoomMap::RoomMap(QWidget *parent) : QGraphicsView(parent)
{
    scene = new MapScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing); // 开启抗锯齿
    setDragMode(QGraphicsView::ScrollHandDrag); // 允许鼠标拖动整个场景
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 让缩放围绕鼠标进行

    audioManager = new AudioManager(scene, this);
    qApp->setProperty("AudioManager", QVariant::fromValue(audioManager)); // 存储指针
    // wallManager = new WallManager(scene, this);

    listenerItem = new DraggableListener(audioManager);
    scene->addItem(listenerItem);
    listenerItem->setPos(scene->sceneRect().center());
    audioManager->updateListener(scene->sceneRect().center().x(), scene->sceneRect().center().y(), RoomHeight);
    // audioManager->addAudioSource("source1", "E:/WorkPlace/QT/3D_audio/music/test2.wav", 10.0f, 5.0f, 1.0f);

    menu = new QMenu(this);
    addObjectAction = new QAction("创建音源", this);
    addWallAction = new QAction("创建墙体", this);

    connect(addObjectAction, &QAction::triggered, this, &RoomMap::addObject);
    connect(addWallAction, &QAction::triggered, this, &RoomMap::addWall);
}

// void RoomMap::drawBackground(QPainter *painter, const QRectF &rect) // 绘制网格
// {
//     const int gridSize = GridSize;
//     painter->setPen(QPen(Qt::lightGray, 0.5));
//     for (int x = rect.left(); x < rect.right(); x += gridSize)
//         painter->drawLine(x, rect.top(), x, rect.bottom());
//     for (int y = rect.top(); y < rect.bottom(); y += gridSize)
//         painter->drawLine(rect.left(), y, rect.right(), y);
// }
void RoomMap::drawForeground(QPainter *painter, const QRectF &rect)    // 绘制比例尺
{
    painter->setPen(QPen(Qt::black, 2));
    int scaleSize = GridSize; // 50像素代表固定距离
    painter->drawLine(rect.right() - scaleSize - 10, rect.bottom() - 10,
                      rect.right() - 10, rect.bottom() - 10);
    painter->drawText(rect.right() - scaleSize - 10, rect.bottom() - 15, "50 px");
}
void RoomMap::contextMenuEvent(QContextMenuEvent *event) // 右键菜单
{

    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem *item = scene->itemAt(scenePos, QTransform());


    if (item)
    {
        // 创建并触发 QGraphicsSceneContextMenuEvent
        QGraphicsSceneContextMenuEvent sceneEvent(QEvent::GraphicsSceneContextMenu);

        // 设置事件的位置信息
        sceneEvent.setPos(scenePos);
        sceneEvent.setScenePos(scenePos);
        sceneEvent.setScreenPos(event->globalPos());

        // 发送事件给项
        scene->sendEvent(item, &sceneEvent);

    }
    else {
        menu->addAction(addObjectAction);
        menu->addAction(addWallAction);
        menu->exec(event->globalPos());
    }
}


void RoomMap::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = (event->angleDelta().y() > 0) ? 1.2 : 0.8;
    scale(scaleFactor, scaleFactor);
}

void RoomMap::addObject()
{
    DraggableSource* item = new DraggableSource(audioManager);
    // if (item->setAudioSourceFile()) {
    //     //item->setAudioSource("source" + QString::fromStdString(std::to_string(rand())));
    //     qDebug()<<"成功绑定";
    //     scene->addItem(item);
    //     item->setPos(mapToScene(viewport()->rect().center()));
    // }
}

void RoomMap::addWall() {
    //QRectF newWall(100, 100, 400, 400);
    WallRectItem* wall = audioManager->createWall();
    //scene->addItem(wall);
}

