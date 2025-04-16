#ifndef ROOMMAP_H
#define ROOMMAP_H

#include "audiomanager.h"
#include "draggablelistener.h"
#include "mapscene.h"
#include "scenefilehandler.h"

#include <QWheelEvent>
#include <QGraphicsView>

class RoomMap : public QGraphicsView
{
    Q_OBJECT

public:
    explicit RoomMap(QWidget *parent = nullptr);
    std::shared_ptr<MapScene> scene;
    std::shared_ptr<DraggableListener> listenerItem;
    std::shared_ptr<AudioManager> audioManager;
    std::shared_ptr<SceneFileHandler> sceneFileHandler;

protected:
    void wheelEvent(QWheelEvent *event) override; // 处理滚轮缩放
    //void drawBackground(QPainter *painter, const QRectF &rect) override; // 绘制网格
    void drawForeground(QPainter *painter, const QRectF &rect) override; // 绘制比例尺
    void contextMenuEvent(QContextMenuEvent *event) override; // 右键菜单


public slots:
    void addSource(); // 创建音源
    void addWall();
    void saveSceneFile();
    void loadSceneFile();

private:

    std::shared_ptr<QAction> addObjectAction;
    std::shared_ptr<QAction> addWallAction;

    //WallManager *wallManager;

    std::shared_ptr<QMenu> menu;

    // 初始化缩放的上下限
    double m_minScale = 0.1;
    double m_maxScale = 5.0;
    // 初始化当前缩放比例
    double m_currentScale = 1.0;

};

#endif // ROOMMAP_H
