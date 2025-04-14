#ifndef ROOMMAP_H
#define ROOMMAP_H

#include "audiomanager.h"
#include "draggablelistener.h"
#include "mapscene.h"

#include <QWheelEvent>
#include <QGraphicsView>

class RoomMap : public QGraphicsView
{
    Q_OBJECT

public:
    explicit RoomMap(QWidget *parent = nullptr);
    MapScene *scene;
    DraggableListener *listenerItem;

protected:
    void wheelEvent(QWheelEvent *event) override; // 处理滚轮缩放
    //void drawBackground(QPainter *painter, const QRectF &rect) override; // 绘制网格
    void drawForeground(QPainter *painter, const QRectF &rect) override; // 绘制比例尺
    void contextMenuEvent(QContextMenuEvent *event) override; // 右键菜单
    void addWall();

private slots:
    void addObject(); // 创建物体

private:

    QAction *addObjectAction;
    QAction *addWallAction;
    AudioManager *audioManager;
    //WallManager *wallManager;

    QMenu *menu;

};

#endif // ROOMMAP_H
