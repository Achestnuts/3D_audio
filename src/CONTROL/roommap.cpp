#include "roommap.h"
#include "mapscene.h"
#include "draggablesource.h"

#include <QGraphicsEllipseItem>
#include <QFileDialog>
#include<QMenu>
#include <scenefilehandler.h>



RoomMap::RoomMap(QWidget *parent) : QGraphicsView(parent)
{
    qDebug()<<"prepare create roommap";
    qApp->setProperty("RoomMap", QVariant::fromValue(std::shared_ptr<RoomMap>(this))); // 存储指针

    scene = std::make_shared<MapScene>(this);
    sceneFileHandler = std::shared_ptr<SceneFileHandler>();
    setScene(scene.get());

    setRenderHint(QPainter::Antialiasing); // 开启抗锯齿
    setDragMode(QGraphicsView::ScrollHandDrag); // 允许鼠标拖动整个场景
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 让缩放围绕鼠标进行

    audioManager = std::make_shared<AudioManager>(scene, this);

    // wallManager = new WallManager(scene, this);

    listenerItem = std::make_shared<DraggableListener>();
    listenerItem->setListener(audioManager->listener);
    scene->addItem(listenerItem.get());
    listenerItem->setPos(scene->sceneRect().center());
    listenerItem->setPosition(scene->sceneRect().center());
    //audioManager->updateListener(scene->sceneRect().center().x(), .y(), RoomHeight);
    // audioManager->addAudioSource("source1", "E:/WorkPlace/QT/3D_audio/music/test2.wav", 10.0f, 5.0f, 1.0f);

    menu = std::make_shared<QMenu>(this);
    addObjectAction = std::make_shared<QAction>("创建音源", this);
    addWallAction = std::make_shared<QAction>("创建墙体", this);

    connect(addObjectAction.get(), &QAction::triggered, this, &RoomMap::addSource);
    connect(addWallAction.get(), &QAction::triggered, this, &RoomMap::addWall);
    qDebug()<<"finish create roommap";
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
    QString meterString = QString::number(audioManager->gridMeter) + " m";
    painter->drawText(rect.right() - scaleSize - 10, rect.bottom() - 15, meterString);
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
        menu->addAction(addObjectAction.get());
        menu->addAction(addWallAction.get());
        menu->exec(event->globalPos());
    }
}


void RoomMap::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = (event->angleDelta().y() > 0) ? 1.2 : 0.8;
    double newScale = m_currentScale * scaleFactor;

    // 检查新的缩放比例是否在上下限范围内
    if (newScale >= m_minScale && newScale <= m_maxScale) {
        scale(scaleFactor, scaleFactor);
        m_currentScale = newScale;
    }

    event->accept();
}

void RoomMap::addSource()
{
    std::shared_ptr<DraggableSource> source;

    QString filepath = QFileDialog::getOpenFileName(nullptr, "选择音频文件", "",
                                                    "目标音频文件 (*.mp3 *.ogg *.wav *.acc *.flac)");
    if(!filepath.isEmpty()) {
        source = std::make_shared<DraggableSource>();
        // qDebug()<<"分配指针完成";
        source->setAudioSourceFile(filepath);
        audioManager->sources[source->boundSource->sourceId] = source;
        // qDebug()<<"音频文件设置完成";
        // scene->addItem(source.get());
        source->setPos(mapToScene(viewport()->rect().center()));
    }
    // if (item->setAudioSourceFile()) {
    //     //item->setAudioSource("source" + QString::fromStdString(std::to_string(rand())));
    //     qDebug()<<"成功绑定";
    //     scene->addItem(item);
    //     item->setPos(mapToScene(viewport()->rect().center()));
    // }
}

void RoomMap::addWall() {
    //QRectF newWall(100, 100, 400, 400);
    std::shared_ptr<WallRectItem> wall = audioManager->createWall();
    //scene->addItem(wall);
}

void RoomMap::saveSceneFile() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "保存场景文件", "", "场景文件 (*.json)");
    if(!fileName.isEmpty()) {
        std::list<std::shared_ptr<WallRectItem>> needStoreWalls;
        for(auto [fileterId, wall] : audioManager->walls) {
            needStoreWalls.push_back(wall);
        }
        std::list<std::shared_ptr<DraggableSource>> needStoreSources;
        for(auto [sourceId, source] : audioManager->sources) {
            needStoreSources.push_back(source);
        }
        sceneFileHandler->saveScene(fileName, needStoreWalls, needStoreSources, audioManager->gridMeter);
    }
}

void RoomMap::loadSceneFile() {
    QString fileName = QFileDialog::getOpenFileName(nullptr, "读取场景文件", "", "场景文件 (*.json)");
    if(!fileName.isEmpty()) {
        std::list<std::shared_ptr<WallRectItem>> needLoadWalls;

        std::list<std::shared_ptr<DraggableSource>> needLoadSources;

        sceneFileHandler->loadScene(fileName, needLoadWalls, needLoadSources, audioManager->gridMeter);

        for(auto wall : needLoadWalls) {
            audioManager->walls[wall->filter.getFilterId()] = wall;

        }

        for(auto source : needLoadSources) {
            audioManager->sources[source->boundSource->getSourceId()] = source;
        }
    }

    qDebug()<<"finish load all";
}

