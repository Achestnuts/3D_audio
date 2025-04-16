#ifndef DRAGGABLESOURCE_H
#define DRAGGABLESOURCE_H

#include "draggableitem.h"

#include <AudioSource.h>
#include <QMutex>
#include <QReadWriteLock>


class DraggableSource : public DraggableItem
{
    Q_OBJECT
public:
    explicit DraggableSource();
    ~DraggableSource();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void initMenu();
    bool setAudioSourceFile(QString filePath);
    void setPosition(QPointF newPos);
    void disconnectAll();

    QJsonObject toJson() const;
    static std::shared_ptr<DraggableSource> createFromJson(const QJsonObject &obj);

    // ALuint sourceId;
    QString sourceName;
    QString sourceFilePath;
    AudioSource* boundSource;

    std::shared_ptr<QReadWriteLock> mutex = nullptr; // 来自管理器的读写锁
signals:
    void itemSelected(DraggableSource* source);
    void needUpdateEffect();



private slots:
    void playVoice();
    void removeSelf();

};

#endif // DRAGGABLESOURCE_H
