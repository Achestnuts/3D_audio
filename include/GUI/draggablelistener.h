#ifndef DRAGGABLELISTENER_H
#define DRAGGABLELISTENER_H

#include "draggableitem.h"

class DraggableListener : public DraggableItem
{
    Q_OBJECT
public:
    explicit DraggableListener(AudioManager *newManager);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void initMenu() override;
    void setListener(const QString &id);

signals:
    void itemSelected(DraggableListener* listener);
// private slots:
//     void playVoice();

};

#endif // DRAGGABLELISTENER_H
