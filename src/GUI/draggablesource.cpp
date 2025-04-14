#include "draggablesource.h"

#include "xwidget.h"
#include "roommap.h"
#include <QFileDialog>
#include <QWindow>
#include <QMetaObject>
#include <QMetaProperty>
#include "ui_xwidget.h"


DraggableSource::DraggableSource(AudioManager *newManager)
    : DraggableItem(QString(":/icons/play.svg"), newManager)
{
    RoomMap *roomMap = qvariant_cast<RoomMap*>(qApp->property("RoomMap"));
    sourceId = 0;
    sourceName = "source" + QString::fromStdString(std::to_string(rand()));
    sourceFilePath = nullptr;
    initMenu();

    if(setAudioSourceFile()) {
        roomMap->scene->addItem(this);
        setPos(roomMap->mapToScene(roomMap->viewport()->rect().center()));
    } else {
        return;
    }


    XWidget* xWidget = qvariant_cast<XWidget*>(qApp->property("MainXWidget"));
    connect(this, &DraggableSource::itemSelected, xWidget, &XWidget::updateSourceParameterWidget);
    connect(this, &DraggableSource::itemSelected, [this, xWidget](DraggableSource* selectedSource) {
        AudioManager *audiomanager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
        xWidget->ui->audioSourcePanel->setSource(audiomanager->sources[selectedSource->sourceId]);
    });
}

DraggableSource::~DraggableSource() {
    AudioManager *audiomanager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
    if(audiomanager->isSourceExist(sourceId)) {
        audiomanager->removeAudioSource(sourceId);
    }

    disconnect(this);
}

void DraggableSource::removeSelf() {
    RoomMap *roomMap = qvariant_cast<RoomMap*>(qApp->property("RoomMap"));
    roomMap->scene->removeItem(this);
}

void DraggableSource::initMenu()
{
    menu = new QMenu();
    QAction *playVoiceAction = menu->addAction("播放");
    QAction *setSourceFileAction = menu->addAction("设置音源");
    QAction *deleteAction = menu->addAction("删除");

    connect(playVoiceAction, &QAction::triggered, this, &DraggableSource::playVoice);
    connect(setSourceFileAction, &QAction::triggered, this, &DraggableSource::setAudioSourceFile);
    connect(deleteAction, &QAction::triggered, this, &DraggableSource::removeSelf);
}

bool DraggableSource::setAudioSourceFile()
{
    qDebug()<<"准备绑定音源";
    sourceFilePath = QFileDialog::getOpenFileName(nullptr, "选择音频文件", "", "WAV 文件 (*.wav)");
    if(sourceFilePath.isEmpty()) {
        return false;
    }

    if(!(manager->isSourceExist(sourceId))) {
        qDebug()<<"开始创建音源";
        sourceId = manager->addAudioSource(sourceFilePath, 10.0f, 5.0f, RoomHeight);
        qDebug()<<"add a source:"<<sourceName;
    } else {
        //manager->sources[sourceId]->stop();
        manager->sources[sourceId]->switchAudio(sourceFilePath.toStdString());
    }
    return true;
}

void DraggableSource::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastMousePos = event->scenePos();
    dragging = true;
    setZValue(1); // 选中后置顶
    emit itemSelected(this);
    QGraphicsPixmapItem::mousePressEvent(event);
}

void DraggableSource::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) {
        QPointF delta = event->scenePos() - lastMousePos;
        setPos(this->pos() + delta);
        lastMousePos = event->scenePos();
        if(manager) {
            manager->updateAudioSource(sourceId, this->mapToScene(this->boundingRect()).boundingRect().center().x(),
                                       this->mapToScene(this->boundingRect()).boundingRect().center().y(), RoomHeight); // 更新位置
            manager->updateEffectSlots();
        }
    }
}


void DraggableSource::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->exec(event->screenPos());
}

void DraggableSource::playVoice()
{
    manager->playSingal(sourceId);
}
