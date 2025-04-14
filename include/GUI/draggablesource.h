#ifndef DRAGGABLESOURCE_H
#define DRAGGABLESOURCE_H

#include "draggableitem.h"


class DraggableSource : public DraggableItem
{
    Q_OBJECT
public:
    explicit DraggableSource(AudioManager* newManager);
    ~DraggableSource();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void initMenu();
    bool setAudioSourceFile();

    QJsonObject toJson() const;
    static DraggableSource* createFromJson(const QJsonObject &obj);

    ALuint sourceId;
    QString sourceName;
    QString sourceFilePath;
signals:
    void itemSelected(DraggableSource* source);



private slots:
    void playVoice();
    void removeSelf();

};

#endif // DRAGGABLESOURCE_H
