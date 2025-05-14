#include "mapscene.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMenu>
#include <QPainter>

MapScene::MapScene(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 8000, 8000); // 设置一个较大的地图区域
    menu = new QMenu();
    addAction = menu->addAction("添加新组件");
    clearAction = menu->addAction("清空场景");
}

void MapScene::addDraggableItem(QGraphicsItem *item)
{
    addItem(item);
}

void MapScene::drawBackground(QPainter *painter, const QRectF &rect) // 绘制网格
{
    const int gridSize = GridSize;
    painter->setPen(QPen(Qt::gray, 0.5));
    // 获取场景范围
    QRectF sceneRect = this->sceneRect();

    // 计算网格起点，确保从固定点开始绘制
    int left = std::floor(sceneRect.left() / gridSize) * gridSize;
    int top = std::floor(sceneRect.top() / gridSize) * gridSize;
    int right = std::ceil(sceneRect.right() / gridSize) * gridSize;
    int bottom = std::ceil(sceneRect.bottom() / gridSize) * gridSize;

    // 绘制竖直线
    for (int x = left; x <= right; x += gridSize) {
        painter->drawLine(x, top, x, bottom);
    }

    // 绘制水平线
    for (int y = top; y <= bottom; y += gridSize) {
        painter->drawLine(left, y, right, y);
    }
}

void MapScene::checkAndExtendScene()
{
    QGraphicsView *view = views().first(); // 假设只有一个视图
    if (!view) return;

    QRectF visibleRect = view->mapToScene(view->rect()).boundingRect();
    QRectF sceneRect = this->sceneRect();

    // 检查是否接近边缘，并相应地调整场景大小
    int extendAmount = 1000; // 假设每次扩展1000单位
    if (visibleRect.right() > sceneRect.right() - extendAmount) {
        sceneRect.setRight(sceneRect.right() + extendAmount);
    }
    if (visibleRect.bottom() > sceneRect.bottom() - extendAmount) {
        sceneRect.setBottom(sceneRect.bottom() + extendAmount);
    }
    if (visibleRect.left() < sceneRect.left() + extendAmount) {
        sceneRect.setLeft(sceneRect.left() - extendAmount);
        // 需要移动所有项，因为场景的左上角坐标改变了
        foreach (QGraphicsItem *item, items()) {
            item->setPos(item->pos() + QPointF(extendAmount, 0));
        }
    }
    if (visibleRect.top() < sceneRect.top() + extendAmount) {
        sceneRect.setTop(sceneRect.top() - extendAmount);
        // 需要移动所有项，因为场景的左上角坐标改变了
        foreach (QGraphicsItem *item, items()) {
            item->setPos(item->pos() + QPointF(0, extendAmount));
        }
    }

    setSceneRect(sceneRect);
}

// void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {
//     QGraphicsScene::mousePressEvent(event);

//     // 检查是否需要扩展场景
//     checkAndExtendScene();
// }
