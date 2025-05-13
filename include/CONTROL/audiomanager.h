#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QMutex>
#include <AL/al.h>
#include <AL/alc.h>
#include <QDir>
#include <QGraphicsScene>
#include <QReadWriteLock>
#include <draggablesource.h>
#include <unordered_map>
#include "audiorecorder.h"
#include "listener.h"
#include "wallrectitem.h"

class XWidget;

#define RoomHeight 1.0f

class AudioManager : public QObject {
    Q_OBJECT
public:
    explicit AudioManager(std::shared_ptr<QGraphicsScene> addScene, QObject *parent = nullptr);
    ~AudioManager();

    //ALuint addAudioSource(const QString &filePath, float x, float y, float volume);
    //void setAudioSource(const ALuint &sourceId, const QString &filePath, float x, float y, float volume);
    //void updateAudioSource(const ALuint &sourceId, float x, float y, float volume);
    //void updateListener(float x, float y, float z);
    //ALuint getSourceBuffer(ALuint sourceId);
    void removeAudioSource(const ALuint &sourceId);
    //void saveToFile(const QString &filename);
    //void loadFromFile(const QString &filename);
    //void playSingal(const ALuint &sourceId);
    void playAll();
    void stopAll();
    bool isSourceExist(const ALuint &sourceId);
    void removeWallRectItem(const ALuint &filterId);
    bool listenerIsExist(std::shared_ptr<Listener> checkListener);

    std::shared_ptr<WallRectItem> createWall();
    // 吸附功能: 让一个墙体与其他墙体对齐
    // void snapWall(std::shared_ptr<WallRectItem> item);
    void updateEffectSlots();

    std::unordered_map<ALuint, std::shared_ptr<DraggableSource>> sources;
    std::unordered_map<ALuint, std::shared_ptr<WallRectItem>> walls;
    std::shared_ptr<Listener> listener;
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<XWidget> xWidget;
    std::shared_ptr<AudioRecorder> recorder;

    float gridMeter;
    QMutex managerMutex;
    std::shared_ptr<QReadWriteLock> itemMutex;

    QString tempPath = QDir::currentPath() + "/temp";
    QString recordTempPath = QDir::currentPath() + "/temp/record_temp.wav";

    void stopRecordingAndSave();
    void startRecording();

private:
    ALCdevice *device;
    ALCcontext *context;


};

#endif // AUDIOMANAGER_H
