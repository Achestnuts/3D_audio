#ifndef DRAGGABLEITEM_H
#define DRAGGABLEITEM_H

#include "audiomanager.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#define RoomHeight 1.0f

class DraggableItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit DraggableItem(const QPixmap &icon, AudioManager *newManager = nullptr);
    //void setAudioSource(const QString &sourcName);
    void setManager(AudioManager* newManager);


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
    AudioManager *manager;
    QMenu *menu;

};

#endif // DRAGGABLEITEM_H
