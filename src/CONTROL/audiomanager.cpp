#include "audiomanager.h"
#include "parametercalculationengine.h"
#include <QDebug>
#include <memory>
#include <AL/al.h>
#include <AL/alc.h>
#define AL_ALEXT_PROTOTYPES
#include <AL/efx.h>
#include <QFileDialog>
#include <QVector3D>
#include <QtConcurrent>
#include <cmath> // 计算距离


AudioManager::AudioManager(std::shared_ptr<QGraphicsScene> addScene, QObject *parent) :
    QObject(parent) {

    qApp->setProperty("AudioManager", QVariant::fromValue(std::shared_ptr<AudioManager>(this))); // 存储指针

    gridMeter = 0.2;
    device = alcOpenDevice(nullptr);
    scene = addScene;

    itemMutex = std::make_shared<QReadWriteLock>();

    if (!device) {
        qDebug() << "Failed to open OpenAL device";
        return;
    }
    if (!alcIsExtensionPresent(device, "ALC_EXT_EFX"))
    {
        // EFX不被支持
        qDebug()<<"不支持efx";
    } else {
        qDebug()<<"支持efx";
    }

    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    const ALCchar* deviceName = alcGetString(device, ALC_DEVICE_SPECIFIER);
    recorder = std::make_shared<AudioRecorder>(this, deviceName);


    listener = std::make_shared<Listener>();

    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);


}

AudioManager::~AudioManager() {
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void AudioManager::updateEffectSlots() {
    qDebug()<<"accept";
    QMutexLocker lock(&managerMutex);
    qDebug()<<"manager ok";
    QReadLocker locker(itemMutex.get());
    qDebug()<<"item ok";

    qDebug()<<"正在更新";
    // 假设 listener 和 source 均在 scene 坐标系中，且 sources 存储所有可见声源
    for (auto& [sourceId, source] : sources) {

        float estimateRoomSize = 0;
        QPointF totalReflection = {0.0, 0.0};
        int gain = ParameterCalculationEngine::calculateEffectParameter(
            source, listener, walls, gridMeter, &estimateRoomSize, &totalReflection
            );
        QVector3D reflection= {0.0, 0.0, 0.0};
        reflection.setX(totalReflection.x());
        reflection.setZ(totalReflection.y());

        if(gain) {
            source->boundSource->auxEffectSlots.updateEffectParams(estimateRoomSize, reflection, gain);
        } else {
            source->boundSource->auxEffectSlots.resetEffect();
        }
        // 更新声源的总过滤器
        source->boundSource->updateFilter();
    } // end sources loop
}

// ALuint AudioManager::addAudioSource(const QString &filePath, float x, float y, float volume) {
//     QmanagerMutexLocker locker(&managerMutex);
//     //if (sources.find(sourceId) != sources.end()) return;
//     qDebug()<<"source准备创建";
//     AudioSource *source = new AudioSource(filePath.toStdString());
//     //source->name = "noName";
//     //source->filePath = filePath;
//     source->posX = x;
//     source->posY = y;
//     source->volume = volume;

//     // 生成 OpenAL 音源
//     //alGenSources(1, &(source->source));
//     alSource3f(source->sourceId, AL_POSITION, x, y, 0.0f);
//     alSourcef(source->sourceId, AL_GAIN, volume);

//     sources[source->sourceId] = std::shared_ptr<AudioSource>(source);
//     return source->sourceId;
// }

// void AudioManager::setAudioSource(const ALuint &sourceId, const QString &filePath, float x, float y, float volume) {
//     QMutexLocker locker(&managerMutex);
//     if (sources.find(sourceId) == sources.end()) return;

//     std::shared_ptr<DraggableSource> source = sources[sourceId];
//     if (!source->boundSource->loadWavFile(filePath.toStdString())) {
//         qDebug() << "Failed to load WAV file: " << filePath;
//     }
//     source->filePath = filePath;
//     source->posX = x;
//     source->posY = y;
//     source->volume = volume;

//     // 生成 OpenAL 音源
//     alGenSources(1, &(source->sourceId));
//     alSource3f(source->sourceId, AL_POSITION, x, y, 0.0f);
//     alSourcef(source->sourceId, AL_GAIN, volume);

//     sources[sourceId] = std::shared_ptr<AudioSource>(source);
// }

// void AudioManager::updateAudioSource(const ALuint &sourceId, float x, float y, float volume) {
//     QMutexLocker locker(&managerMutex);
//     if (sources.find(sourceId) == sources.end()) return;

//     std::shared_ptr<AudioSource> source = sources[sourceId];
//     source->posX = x;
//     source->posY = y;
//     source->volume = volume;

//     alSource3f(source->sourceId, AL_POSITION, x, y, 0.0f);
//     alSourcef(source->sourceId, AL_GAIN, volume);

//     //qDebug()<<sourceName<<"is in:"<<x<<","<<y<<" now";
// }

// ALuint AudioManager::getSourceBuffer(ALuint sourceId) {
//     return sources[sourceId]->getSourceBuffer();
// }

// void AudioManager::updateListener(float x, float y, float z) {
//     QMutexLocker locker(&managerMutex);
//     //if (sources.find(sourceName) == sources.end()) return;

//     //std::shared_ptr<AudioSource> source = sources[sourceName];
//     listener->setPosition(x, y, z);

//     //qDebug()<<"Listener is in:"<<x<<","<<y<<" now";
// }

// 在 AudioManager 类中
void AudioManager::stopRecordingAndSave() {

    recorder->stopRecording();

    QString filePath = QFileDialog::getSaveFileName(nullptr, "保存音频", QDir::currentPath(), "音频文件 (*.mp3 *.ogg *.wav *.acc *.m4a *.flac)");

    if (filePath.isEmpty()) {
        return;
    }

    // 获取用户选择的文件扩展名
    QFileInfo fileInfo(filePath);
    QString fileExtension = fileInfo.suffix().toLower();

    // 根据选择的扩展名，保存音频文件
    if (!recorder->saveRecording(recordTempPath, filePath, fileExtension)) {
        qWarning() << "保存录音文件失败";
    }
}

void AudioManager::startRecording()
{
    recorder->startRecording(recordTempPath);
}

void AudioManager::removeAudioSource(const ALuint &sourceId) {
    // qDebug()<<"即将锁住管理器";
    QMutexLocker locker(&managerMutex);
    if (sources.find(sourceId) == sources.end()) return;
    // qDebug()<<sourceId<<"锁住并找到了";
    alDeleteSources(1, &(sourceId));
    // qDebug()<<"删除完成";
    sources.erase(sourceId);
    // qDebug()<<"管理器删除完成";
    return;
}

void AudioManager::removeWallRectItem(const ALuint &filterId) {
    QMutexLocker locker(&managerMutex);
    if (walls.find(filterId) == walls.end()) return;
    //alDeleteSources(1, &(sources[sourceId]->sourceId));
    std::shared_ptr<WallRectItem> wall = walls[filterId];
    for(auto& [sourceId, source] : sources) {
        source->boundSource->removeFilter(filterId);
    }
    walls.erase(filterId);
    // delete wall;
    return;
}

// void AudioManager::playSingal(const ALuint &sourceId) {
//     std::lock_guard<QMutex> lock(managerMutex);
//     if (sources.find(sourceId) != sources.end()) {
//         std::shared_ptr<DraggableSource> source = sources[sourceId];

//         // QtConcurrent 方式，无需手动管理线程
//         QtConcurrent::run([source]() {
//             source->boundSource->play();
//         });
//     }

//     // 获取设备采样率
//     ALCint frequency;
//     alcGetIntegerv(device, ALC_FREQUENCY, 1, &frequency);

//     std::cout << "The sample rate of the current device is: " << frequency << " Hz" << std::endl;
// }


// 定义一个辅助函数，用于调用 AudioSource 的 play 方法
void playAudioSource(std::shared_ptr<DraggableSource> audioSource) {
    if (audioSource) {
        audioSource->boundSource->play();
    }
}

void AudioManager::playAll() {
    qDebug()<<"ok"<<sources.size();
    for (auto &pair : sources) {
        if(pair.second && pair.second->boundSource->sourceId) {

            // qDebug()<<pair.second->sourceId<<"";
            QtConcurrent::run(playAudioSource, pair.second);
            //alSourcePlay(pair.second->source);
        } else {
            qDebug()<<"what's wrong?";
        }

    }
    qDebug()<<"out of for";
}

void AudioManager::stopAll() {
    QMutexLocker locker(&managerMutex);
    for (auto &pair : sources) {
        pair.second->boundSource->stop();
    }
}

bool AudioManager::listenerIsExist(std::shared_ptr<Listener> checkListener) {
    return checkListener && checkListener == listener;
}

bool AudioManager::isSourceExist(const ALuint &sourceId) {
    return sources.find(sourceId) != sources.end();
}



std::shared_ptr<WallRectItem> AudioManager::createWall()
{
    QRectF rect =  QRectF(0, 0, 50, 200);
    std::shared_ptr<WallRectItem> wall = std::make_shared<WallRectItem>(rect);
    //scene->addItem(wall.get());
    walls[wall->filter.getFilterId()] = wall;
    //wall->setRect(rect);

    return wall;
}

// // 在此实现具体吸附逻辑(示例: 当item松开时,检查与其他墙体的边是否在阈值内)
// void AudioManager::snapWall(std::shared_ptr<WallRectItem> item)
// {
//     QRectF r = item->sceneBoundingRect();
//     float snapT = item->snapThreshold();

//     qDebug()<<"准备对齐";

//     // 仅示例: 当某边与另一个墙体的边相距 < snapT，则对齐
//     for (auto otherPair : walls) {
//         std::shared_ptr<WallRectItem> other = otherPair.second;
//         if (other == item) continue;
//         QRectF temp = other->sceneBoundingRect();

//         // 例如对齐item的left到other的right
//         float distLeftRight = std::fabs(r.left() - temp.right());
//         if (distLeftRight < snapT) {
//             // 将item的left对齐到other.right
//             QPointF offset(distLeftRight * (r.left() > temp.right() ? -1 : 1), 0);
//             item->moveBy(-offset.x(), 0);
//             qDebug()<<"对齐成功";
//             // 你可以更准确地算： newX = or.right() - (r.width())
//         }

//         // 其他边判断...
//         // top->bottom, right->left, bottom->top
//     }
// }
