#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QAction>
#include <QGraphicsScene>

#define GridSize 50
#define RoomHeight 1.0f

class MapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MapScene(QObject *parent = nullptr);
    void addDraggableItem(QGraphicsItem *item);
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void checkAndExtendScene();
    //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

// private slots:
//     void addObject();


    QAction *addAction;
    QAction *clearAction;
    QMenu *menu;


};

#endif // MAPSCENE_H
