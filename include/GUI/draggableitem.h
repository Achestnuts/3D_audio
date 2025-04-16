#ifndef DRAGGABLEITEM_H
#define DRAGGABLEITEM_H


#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#define RoomHeight 1.0f

class DraggableItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit DraggableItem(const QPixmap &icon);
    //void setAudioSource(const QString &sourcName);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void initMenu();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;


// private slots:
//     void onAddActionTriggered();

protected:
    bool dragging;
    QPointF lastMousePos;
    QMenu *menu;

};

#endif // DRAGGABLEITEM_H
