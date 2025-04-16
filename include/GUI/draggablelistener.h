#ifndef DRAGGABLELISTENER_H
#define DRAGGABLELISTENER_H

#include "draggableitem.h"

#include <Listener.h>
#include <QMutex>
#include <QReadWriteLock>

class DraggableListener : public DraggableItem
{
    Q_OBJECT
public:
    explicit DraggableListener();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void initMenu() override;
    void setListener(std::shared_ptr<Listener> newListener);
    void setPosition(QPointF newPos);

    //QJsonObject toJson() const;
    // static DraggableListener* createFromJson(const QJsonObject &obj);

    std::shared_ptr<Listener> listener = nullptr;

    std::shared_ptr<QReadWriteLock> mutex = nullptr; // 来自管理器的读写锁

signals:
    void itemSelected(DraggableListener* listener);
// private slots:
//     void playVoice();

};

#endif // DRAGGABLELISTENER_H
