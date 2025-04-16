#include "draggablesource.h"
#include "ui_xwidget.h"
#include "xwidget.h"
#include "roommap.h"
#include <QFileDialog>
#include <QWindow>
#include <QMetaObject>
#include <QMetaProperty>
#include <qtconcurrentrun.h>


DraggableSource::DraggableSource()
    : DraggableItem(QString(":/icons/play.svg"))
{
    std::shared_ptr<RoomMap> roomMap = qvariant_cast<std::shared_ptr<RoomMap>>(qApp->property("RoomMap"));
    roomMap->scene->addItem(this);
    // sourceId = 0;
    sourceName = "source" + QString::fromStdString(std::to_string(rand()));
    sourceFilePath = nullptr;
    boundSource = nullptr;
    initMenu();

    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    mutex = audioManager->itemMutex;
    connect(this, &DraggableSource::needUpdateEffect, [audioManager](){
        audioManager->updateEffectSlots();
    });

    // if(setAudioSourceFile()) {
    //     roomMap->scene->addItem(this);
    //     setPos(roomMap->mapToScene(roomMap->viewport()->rect().center()));
    // } else {
    //     return;
    // }


    // XWidget* xWidget = qvariant_cast<XWidget*>(qApp->property("MainXWidget"));
    // connect(this, &DraggableSource::itemSelected, xWidget, &XWidget::updateSourceParameterWidget);
    // std::shared_ptr<XWidget> xWidget = qvariant_cast<std::shared_ptr<XWidget>>(qApp->property("MainXWidget"));
    // connect(this, &DraggableSource::itemSelected, xWidget->ui->sourceParameterWidget, &SourceParameterWidget::boundSource);
}

DraggableSource::~DraggableSource() {
    removeSelf();
    // if(boundSource) {
    //     delete boundSource;
    // }
}

void DraggableSource::disconnectAll() {
    std::shared_ptr<XWidget> xWidget = qvariant_cast<std::shared_ptr<XWidget>>(qApp->property("MainXWidget"));
    xWidget->ui->audioSourcePanel->disconnectSource();
    xWidget->ui->sourceParameterWidget->disconnectBound();
}

void DraggableSource::removeSelf() {
    mutex->lockForWrite();
    boundSource->stop();
    disconnectAll();
    std::shared_ptr<RoomMap> roomMap = qvariant_cast<std::shared_ptr<RoomMap>>(qApp->property("RoomMap"));
    roomMap->scene->removeItem(this);
    if(roomMap->audioManager->isSourceExist(boundSource->sourceId)) {
        roomMap->audioManager->removeAudioSource(boundSource->sourceId);
    }
    mutex->unlock();
    emit needUpdateEffect();
}

void DraggableSource::initMenu()
{
    menu = new QMenu();
    QAction *playVoiceAction = menu->addAction("播放");
    QAction *setSourceFileAction = menu->addAction("设置音源");
    QAction *deleteAction = menu->addAction("删除");

    connect(playVoiceAction, &QAction::triggered, this, &DraggableSource::playVoice);
    connect(setSourceFileAction, &QAction::triggered, [this]() {
        QString filepath = QFileDialog::getOpenFileName(nullptr, "选择音频文件", "", "WAV 文件 (*.wav)");
        if(!filepath.isEmpty()) {
            setAudioSourceFile(filepath);
        }
    });
    connect(deleteAction, &QAction::triggered, this, &DraggableSource::removeSelf);
}

bool DraggableSource::setAudioSourceFile(QString filePath)
{
    QWriteLocker locker(mutex.get());
    qDebug()<<"准备绑定音源";
    sourceFilePath = filePath;
    qDebug()<<"this is source filepath:"<<sourceFilePath;
    // QFileDialog::getOpenFileName(nullptr, "选择音频文件", "", "WAV 文件 (*.wav)");
    if(sourceFilePath.isEmpty()) {
        return false;
    }
    std::shared_ptr<XWidget> xWidget = qvariant_cast<std::shared_ptr<XWidget>>(qApp->property("MainXWidget"));
    if(!boundSource) {
        qDebug()<<"here";
        boundSource = new AudioSource(sourceFilePath.toStdString());
        // 绑定一下GUI更新数据
        connect(this, &DraggableSource::itemSelected, [this, xWidget](DraggableSource* selectedSource) {
            disconnectAll();
            xWidget->ui->audioSourcePanel->setSource(boundSource);
            xWidget->ui->sourceParameterWidget->boundSource(this);
        });
    } else if(xWidget->ui->roomMap->audioManager->isSourceExist(boundSource->sourceId)) {
        boundSource->switchAudio(sourceFilePath.toStdString());
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

void DraggableSource::setPosition(QPointF newPos) {
    mutex->lockForWrite();
    setPos(newPos);
    qDebug()<<"drag to"<<newPos;
    if(boundSource) {
        boundSource->setPosition(pos().x(), pos().y(), RoomHeight);
    }
    mutex->unlock();
    emit needUpdateEffect();
}

void DraggableSource::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (dragging) {
        QPointF delta = event->scenePos() - lastMousePos;
        // setPos(this->pos() + delta);
        // if(boundSource) {
        //     boundSource->setPosition(pos().x(), pos().y(), RoomHeight);
        // }

        setPosition(this->pos() + delta);
        lastMousePos = event->scenePos();

        // if(manager) {
        //     manager->updateAudioSource(sourceId, this->mapToScene(this->boundingRect()).boundingRect().center().x(),
        //                                this->mapToScene(this->boundingRect()).boundingRect().center().y(), RoomHeight); // 更新位置
        //     manager->updateEffectSlots();
        // }
    }
}


void DraggableSource::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->exec(event->screenPos());
}

void DraggableSource::playVoice()
{
    mutex->lockForWrite();

    if(boundSource) {
        QtConcurrent::run([this]() {
            this->boundSource->play();
        });
    }

    mutex->unlock();
    emit needUpdateEffect();
}

QJsonObject DraggableSource::toJson() const {
    QReadLocker locker(mutex.get());
    QJsonObject obj;
    obj["sourceFilePath"] = sourceFilePath;
    obj["sourceName"] = sourceName;
    if(!boundSource) {
        return obj;
    }
    obj["posX"] = boundSource->posX; // 以场景坐标保存
    obj["posY"] = boundSource->posY;
    //obj["posZ"] = boundSource->posZ;
    obj["volume"] = boundSource->volume;
    // obj["dirX"] = boundSource->dirX;
    // obj["dirY"] = boundSource->dirY;
    // obj["dirZ"] = boundSource->dirZ;

    // obj["reflectDirX"] = boundSource->auxEffectSlots.reflectDir[0];
    // obj["reflectDirY"] = boundSource->auxEffectSlots.reflectDir[1];
    // obj["reflectDirZ"] = boundSource->auxEffectSlots.reflectDir[2];

    obj["decayTimeIntercept"] = boundSource->auxEffectSlots.decayTimeIntercept;
    obj["decayTimeFactor"] = boundSource->auxEffectSlots.decayTimeFactor;
    obj["reflectionsDelayIntercept"] = boundSource->auxEffectSlots.reflectionsDelayIntercept;
    obj["reflectionsDelayFactor"] = boundSource->auxEffectSlots.reflectionsDelayFactor;
    obj["lateReverbDelayIntercept"] = boundSource->auxEffectSlots.lateReverbDelayIntercept;
    obj["lateReverbDelayFactor"] = boundSource->auxEffectSlots.lateReverbDelayFactor;
    obj["gainIntercept"] = boundSource->auxEffectSlots.gainIntercept;
    obj["gainFactor"] = boundSource->auxEffectSlots.gainFactor;
    obj["reflectionsGainIntercept"] = boundSource->auxEffectSlots.reflectionsGainIntercept;
    obj["reflectionsGainFactor"] = boundSource->auxEffectSlots.reflectionsGainFactor;
    obj["lateReverbGainIntercept"] = boundSource->auxEffectSlots.lateReverbGainIntercept;
    obj["lateReverbGainFactor"] = boundSource->auxEffectSlots.lateReverbGainFactor;
    obj["airAbsorptionHFIntercept"] = boundSource->auxEffectSlots.airAbsorptionHFIntercept;
    obj["airAbsorptionHFFactor"] = boundSource->auxEffectSlots.airAbsorptionHFFactor;
    obj["decayHFRatioIntercept"] = boundSource->auxEffectSlots.decayHFRatioIntercept;
    obj["decayHFRatioFactor"] = boundSource->auxEffectSlots.decayHFRatioFactor;
    obj["decayLFRatioIntercept"] = boundSource->auxEffectSlots.decayLFRatioIntercept;
    obj["decayLFRatioFactor"] = boundSource->auxEffectSlots.decayLFRatioFactor;
    obj["diffusionIntercept"] = boundSource->auxEffectSlots.diffusionIntercept;
    obj["diffusionFactor"] = boundSource->auxEffectSlots.diffusionFactor;
    obj["densityIntercept"] = boundSource->auxEffectSlots.densityIntercept;
    obj["densityFactor"] = boundSource->auxEffectSlots.densityFactor;

    // obj["roomSize"] = boundSource->auxEffectSlots.roomSize;
    // obj["decayTime"] = boundSource->auxEffectSlots.decayTime;
    // obj["reflectionsDelay"] = boundSource->auxEffectSlots.reflectionsDelay;
    // obj["lateReverbDelay"] = boundSource->auxEffectSlots.lateReverbDelay;
    // obj["gain"] = boundSource->auxEffectSlots.gain;
    // obj["reflectionsGain"] = boundSource->auxEffectSlots.reflectionsGain;
    // obj["lateReverbGain"] = boundSource->auxEffectSlots.lateReverbGain;
    // obj["airAbsorptionHF"] = boundSource->auxEffectSlots.airAbsorptionHF;
    // obj["decayHFRatio"] = boundSource->auxEffectSlots.decayHFRatio;
    // obj["decayLFRatio"] = boundSource->auxEffectSlots.decayLFRatio;
    // obj["diffusion"] = boundSource->auxEffectSlots.diffusion;
    // obj["density"] = boundSource->auxEffectSlots.density;

    // obj[""]
    // 其他属性……
    return obj;
}

std::shared_ptr<DraggableSource> DraggableSource::createFromJson(const QJsonObject &obj) {

    std::shared_ptr<DraggableSource> source = std::make_shared<DraggableSource>();

    source->setAudioSourceFile(obj["sourceFilePath"].toString());

    source->setPosition(QPointF(obj["posX"].toDouble(), obj["posY"].toDouble()));

    source->mutex->lockForWrite();
    source->sourceName = obj["sourceName"].toString();

    source->boundSource->setVolume(obj["volume"].toDouble());
    source->boundSource->auxEffectSlots.decayTimeIntercept = obj["decayTimeIntercept"].toDouble();
    source->boundSource->auxEffectSlots.decayTimeFactor = obj["decayTimeFactor"].toDouble();
    source->boundSource->auxEffectSlots.reflectionsDelayIntercept = obj["reflectionsDelayIntercept"].toDouble();
    source->boundSource->auxEffectSlots.reflectionsDelayFactor = obj["reflectionsDelayFactor"].toDouble();
    source->boundSource->auxEffectSlots.lateReverbDelayIntercept = obj["lateReverbDelayIntercept"].toDouble();
    source->boundSource->auxEffectSlots.lateReverbDelayFactor = obj["lateReverbDelayFactor"].toDouble();
    source->boundSource->auxEffectSlots.gainIntercept = obj["gainIntercept"].toDouble();
    source->boundSource->auxEffectSlots.gainFactor = obj["gainFactor"].toDouble();
    source->boundSource->auxEffectSlots.reflectionsGainIntercept = obj["reflectionsGainIntercept"].toDouble();
    source->boundSource->auxEffectSlots.reflectionsGainFactor = obj["reflectionsGainFactor"].toDouble();
    source->boundSource->auxEffectSlots.lateReverbGainIntercept = obj["lateReverbGainIntercept"].toDouble();
    source->boundSource->auxEffectSlots.lateReverbGainFactor = obj["lateReverbGainFactor"].toDouble();
    source->boundSource->auxEffectSlots.airAbsorptionHFIntercept = obj["airAbsorptionHFIntercept"].toDouble();
    source->boundSource->auxEffectSlots.airAbsorptionHFFactor = obj["airAbsorptionHFFactor"].toDouble();
    source->boundSource->auxEffectSlots.decayHFRatioIntercept = obj["decayHFRatioIntercept"].toDouble();
    source->boundSource->auxEffectSlots.decayHFRatioFactor = obj["decayHFRatioFactor"].toDouble();
    source->boundSource->auxEffectSlots.decayLFRatioIntercept = obj["decayLFRatioIntercept"].toDouble();
    source->boundSource->auxEffectSlots.decayLFRatioFactor = obj["decayLFRatioFactor"].toDouble();
    source->boundSource->auxEffectSlots.diffusionIntercept = obj["diffusionIntercept"].toDouble();
    source->boundSource->auxEffectSlots.diffusionFactor = obj["diffusionFactor"].toDouble();
    source->boundSource->auxEffectSlots.densityIntercept = obj["densityIntercept"].toDouble();
    source->boundSource->auxEffectSlots.densityFactor = obj["densityFactor"].toDouble();

    source->mutex->unlock();
    // 其他属性……
    qDebug()<<source->sourceName<<"finish load";
    return source;
}
