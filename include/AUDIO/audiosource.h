#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <AL/alc.h>
#include <string>
#include <QString>

#include "OcclusionFilter.h"
#include "auxeffectslot.h"

class AudioSource {
public:
    explicit AudioSource(const std::string& filePath = "");
    ~AudioSource();

    void initEffectSlots();

    void play();
    void pause();
    void stop();
    void setLooping(bool loop);
    void setVolume(float volume);
    void setPosition(float x, float y, float z);
    void setDirection(float x, float y, float z);
    void setAttenuation(float rolloffFactor, float referenceDistance, float maxDistance);
    bool loadWavFile(const std::string& filePath);
    void loadBufferAndArguments();
    void switchAudio(const std::string& newFile);
    bool addFilter(OcclusionFilter* filterIndex);
    void removeFilter(const ALuint& filterId);
    void updateFilter();

    ALuint getSourceId();
    ALuint* getSourceIdPoint();
    ALuint getSourceBuffer();
    ALuint* getSourceBufferPoint();

    bool isPlaying() const;

    QString filePath;
    float posX, posY, posZ;
    float volume;
    double duration; // 音频时长
    ALuint sourceId;
    ALuint sourceBuffer; // 缓冲保证切换流畅
    float dirX, dirY, dirZ;
    bool usingBuffer; // 表示当前使用的缓冲区
    OcclusionFilter filter; // 声源总过滤器，由其他过滤器叠加得到

    AuxEffectSlot auxEffectSlots; // 四个方向共用的效果器
    std::unordered_map<ALuint, OcclusionFilter*> filterIndexs; // 过滤器的对象指针，通过过滤器id查找对应指针

private:

    mutable std::mutex mtx;

};

#endif // AUDIOSOURCE_H
