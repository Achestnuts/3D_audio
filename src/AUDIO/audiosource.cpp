#include "audiosource.h"
#include <iostream>
#include <fstream>
#include <qapplication.h>
#include <qdebug>
#include <vector>

Q_DECLARE_OPAQUE_POINTER(ALCcontext)
Q_DECLARE_OPAQUE_POINTER(ALCcontext*)

AudioSource::AudioSource(const std::string& filePath)
    : volume(1.0f), posX(0.0f), posY(0.0f), posZ(0.0f),
    dirX(0.0f), dirY(0.0f), dirZ(0.0f) {

    usingBuffer = 1;
    duration = 0;

    alGenSources(1, &sourceId);
    alGenBuffers(1, &sourceBuffer);

    initMirrorSource();

    if (!loadWavFile(filePath)) {
        std::cerr << "Failed to load WAV file: " << filePath << std::endl;
    }

    // 初始队列缓冲区
    alSourceQueueBuffers(sourceId, 1, &sourceBuffer);

    initEffectSlots();

    loadBufferAndArguments();

    qDebug()<<"source创建完成";

}



void AudioSource::initEffectSlots() {
    qDebug()<<"effect准备创建";
        // 设置方向
        //auxEffectSlots.setDirection(i);
        // 将效果槽绑定到声源
    alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER, auxEffectSlots.slotId, 0, AL_FILTER_NULL);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSource3i(mirrorSourceId, AL_AUXILIARY_SEND_FILTER, auxEffectSlots.mirrorSlotId, 0, AL_FILTER_NULL);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------

    qDebug()<<"effect创建成功";
}
ALuint AudioSource::getSourceId() {
    return sourceId;
}
ALuint* AudioSource::getSourceIdPoint() {
    return &sourceId;
}
ALuint AudioSource::getSourceBuffer() {
    return sourceBuffer;
}
ALuint* AudioSource::getSourceBufferPoint() {
    return &sourceBuffer;
}

void AudioSource::loadBufferAndArguments() {
    //alSourceQueueBuffers(source, 2, buffer);
    //alSourcei(source, AL_BUFFER, buffer[usingBuffer]);
    alSourcef(sourceId, AL_GAIN, volume);

    // 默认开启衰减
    setAttenuation(5.0f, 700.0f, 900.0f);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSourcef(mirrorSourceId, AL_GAIN, volume);
    // 默认开启衰减
    setAttenuation(5.0f, 700.0f, 900.0f);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

AudioSource::~AudioSource() {
    // 释放 OpenAL 资源
    alDeleteSources(1, &sourceId);
    alDeleteBuffers(1, &sourceBuffer);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    // 释放 OpenAL 资源
    alDeleteSources(1, &mirrorSourceId);
    alDeleteBuffers(1, &mirrorBufferId);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::play() {
    std::lock_guard<std::mutex> lock(mtx);
    //qDebug()<<buffer[usingBuffer]<<"buffer start play";

    alSourcePlay(sourceId);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    qDebug()<<"record:"<<recordCtx;
    qDebug()<<"main:"<<currentCtx;
    qDebug()<<"now:"<<alcGetCurrentContext();
    if (alcGetCurrentContext() == currentCtx) {
        qWarning() << "当前上下文不是 loopbackContext，alSourcePlay 无效！";
    }

    ALint checkBuffer;
    alGetSourcei(mirrorSourceId, AL_BUFFER, &checkBuffer);
    qDebug() << "绑定的 buffer 是：" << checkBuffer;

    alSourcePlay(mirrorSourceId);

    ALint state = 0;
    alGetSourcei(mirrorSourceId, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING) {
        qDebug() << "Mirror source is playing.";
    } else {
        qWarning() << "Mirror source is NOT playing.";
    }

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::pause() {
    std::lock_guard<std::mutex> lock(mtx);
    alSourcePause(sourceId);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSourcePause(mirrorSourceId);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::stop() {
    std::lock_guard<std::mutex> lock(mtx);
    alSourceStop(sourceId);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSourceStop(mirrorSourceId);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::setLooping(bool loop) {
    std::lock_guard<std::mutex> lock(mtx);
    alSourcei(sourceId, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSourcei(mirrorSourceId, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::setVolume(float newVolume) {
    std::lock_guard<std::mutex> lock(mtx);
    volume = newVolume;
    alSourcef(sourceId, AL_GAIN, volume);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSourcef(mirrorSourceId, AL_GAIN, volume);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::setPosition(float x, float y, float z) {
    std::lock_guard<std::mutex> lock(mtx);
    qDebug()<<"source is"<<x<<" "<<y<<" "<<z;
    posX = x;
    posY = y;
    alSource3f(sourceId, AL_POSITION, x, y, z);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSource3f(mirrorSourceId, AL_POSITION, x, y, z);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::setDirection(float x, float y, float z) {
    std::lock_guard<std::mutex> lock(mtx);
    dirX = x; dirY = y; dirZ = z;
    float direction[] = { x, y, z };
    alSourcefv(sourceId, AL_DIRECTION, direction);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alSourcefv(mirrorSourceId, AL_DIRECTION, direction);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

void AudioSource::setAttenuation(float rolloffFactor, float referenceDistance, float maxDistance) {
    std::lock_guard<std::mutex> lock(mtx);
    // 衰減速度，內插範圍內才有效
    alSourcef(sourceId, AL_ROLLOFF_FACTOR, rolloffFactor);
    // 內插範圍內界，進內界之前不會衰減
    alSourcef(sourceId, AL_REFERENCE_DISTANCE, referenceDistance);
    // 內插範圍外界，出外界之後不再衰減
    alSourcef(sourceId, AL_MAX_DISTANCE, maxDistance);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    // 衰減速度，內插範圍內才有效
    alSourcef(mirrorSourceId, AL_ROLLOFF_FACTOR, rolloffFactor);
    // 內插範圍內界，進內界之前不會衰減
    alSourcef(mirrorSourceId, AL_REFERENCE_DISTANCE, referenceDistance);
    // 內插範圍外界，出外界之後不再衰減
    alSourcef(mirrorSourceId, AL_MAX_DISTANCE, maxDistance);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

bool AudioSource::isPlaying() const {
    std::lock_guard<std::mutex> lock(mtx);
    ALint state;
    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------

    return state == AL_PLAYING;
}

void AudioSource::initMirrorSource() {
    if (mirrorInitialized) return;

    recordCtx = qvariant_cast<ALCcontext*>(qApp->property("recordCtx"));

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alGenSources(1, &mirrorSourceId);
    alGenBuffers(1, &mirrorBufferId);

    alGenFilters(1, &mirrorFilterId);
    // 设置为带通滤波器
    alFilteri(mirrorFilterId, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
    // 初始化默认参数
    alFilterf(mirrorFilterId, AL_BANDPASS_GAIN, 1.0f);
    alFilterf(mirrorFilterId, AL_BANDPASS_GAINHF, 1.0f);
    alFilterf(mirrorFilterId, AL_BANDPASS_GAINLF, 1.0f);

    // // 暂不确定是不是这里绑定比较好
    // alSourceQueueBuffers(mirrorSourceId, 1, &mirrorBufferId);

    // 同步基本参数
    alSourcef(mirrorSourceId, AL_GAIN, this->volume);
    alSource3f(mirrorSourceId, AL_POSITION, this->posX, this->posY, this->posZ);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
    mirrorInitialized = true;

}

/**
 * 解析 WAV 文件并加载到 OpenAL 缓冲区 注：一定要转为单声道，要不无法有空间音频效果
 */
bool AudioSource::loadWavFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open WAV file: " << filePath << std::endl;
        return false;
    }

    // WAV 文件头
    char chunkId[4];
    file.read(chunkId, 4);
    if (strncmp(chunkId, "RIFF", 4) != 0) {
        std::cerr << "Error: Not a valid WAV file (missing RIFF header)" << std::endl;
        return false;
    }

    file.seekg(4, std::ios::cur);  // 跳过文件大小字段

    char format[4];
    file.read(format, 4);
    if (strncmp(format, "WAVE", 4) != 0) {
        std::cerr << "Error: Not a valid WAV file (missing WAVE header)" << std::endl;
        return false;
    }

    // 查找 "fmt " 子块
    char subchunkId[4];
    int subchunkSize;
    while (true) {
        file.read(subchunkId, 4);
        file.read(reinterpret_cast<char*>(&subchunkSize), 4);

        if (strncmp(subchunkId, "fmt ", 4) == 0) {
            break;
        }
        file.seekg(subchunkSize, std::ios::cur);
    }

    // 解析 WAV 格式
    short audioFormat, numChannels;
    int byteRate;
    short blockAlign, bitsPerSample;

    file.read(reinterpret_cast<char*>(&audioFormat), sizeof(audioFormat));
    file.read(reinterpret_cast<char*>(&numChannels), sizeof(numChannels));
    file.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));
    file.read(reinterpret_cast<char*>(&byteRate), sizeof(byteRate));
    file.read(reinterpret_cast<char*>(&blockAlign), sizeof(blockAlign));
    file.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));

    if (audioFormat != 1) { // 1 = PCM 格式
        std::cerr << "Error: Unsupported WAV format (not PCM)" << std::endl;
        return false;
    }

    // 查找 "data" 子块
    while (true) {
        file.read(subchunkId, 4);
        file.read(reinterpret_cast<char*>(&subchunkSize), 4);

        if (strncmp(subchunkId, "data", 4) == 0) {
            break;
        }
        file.seekg(subchunkSize, std::ios::cur);
    }

    // 计算音频时长
    const int bytesPerSample = bitsPerSample / 8;
    // 考虑声道数，计算单声道等效的数据大小
    const int monoEquivalentSize = subchunkSize / numChannels;
    duration = static_cast<double>(monoEquivalentSize) / (sampleRate * bytesPerSample);
    std::cout << "音频时长: " << duration << " 秒" << std::endl;

    // 读取原始 PCM 数据
    std::vector<char> rawData(subchunkSize);
    file.read(rawData.data(), subchunkSize);

    // 单声道转换核心逻辑

    //const int bytesPerSample = bitsPerSample / 8;

    // 仅当原始是单声道时直接使用原数据
    if (numChannels == 1) {
        monoData = std::move(rawData);
        bit_format = (bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    }
    else {
        // 检查支持的声道数
        if (numChannels < 1 || numChannels > 8) {
            std::cerr << "Error: Unsupported number of channels (" << numChannels << ")" << std::endl;
            return false;
        }

        // 计算样本总数（总字节数 / 每个样本的字节数）
        const size_t totalSamples = subchunkSize / bytesPerSample;
        const size_t monoSize = totalSamples / numChannels * bytesPerSample;
        monoData.resize(monoSize);

        // 根据位深度处理转换
        if (bitsPerSample == 16) {
            // 16-bit 处理（short类型）
            const short* src = reinterpret_cast<const short*>(rawData.data());
            short* dst = reinterpret_cast<short*>(monoData.data());

            for (size_t i = 0; i < totalSamples; i += numChannels) {
                int sum = 0;
                for (int c = 0; c < numChannels; ++c) {
                    sum += src[i + c];
                }
                dst[i / numChannels] = static_cast<short>(sum / numChannels);
            }

            bit_format = AL_FORMAT_MONO16;
        }
        else if (bitsPerSample == 8) {
            // 8-bit 处理（char类型）
            const char* src = rawData.data();
            char* dst = monoData.data();

            for (size_t i = 0; i < totalSamples; i += numChannels) {
                int sum = 0;
                for (int c = 0; c < numChannels; ++c) {
                    sum += src[i + c];
                }
                dst[i / numChannels] = static_cast<char>(sum / numChannels);
            }

            bit_format = AL_FORMAT_MONO8;
        }
        else {
            std::cerr << "Error: Unsupported bit depth (" << bitsPerSample << ")" << std::endl;
            return false;
        }
    }


    // 重新填充缓冲数据
    alBufferData(
        sourceBuffer,
        bit_format,
        monoData.data(),
        static_cast<ALsizei>(monoData.size()),
        sampleRate
        );

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alBufferData(
        mirrorBufferId,
        bit_format,
        monoData.data(),
        static_cast<ALsizei>(monoData.size()),
        sampleRate
        ); // 和主源一致

    // 暂不确定是不是这里绑定比较好
    alSourceQueueBuffers(mirrorSourceId, 1, &mirrorBufferId);

    qDebug()<<"record:"<<recordCtx;
    qDebug()<<"main:"<<currentCtx;
    qDebug()<<"now:"<<alcGetCurrentContext();
    if (alcGetCurrentContext() == currentCtx) {
        qWarning() << "当前上下文不是 loopbackContext，alSourcePlay 无效！";
    }

    ALint checkBuffer;
    alGetSourcei(mirrorSourceId, AL_BUFFER, &checkBuffer);
    qDebug() << "绑定的 buffer 是：" << checkBuffer;
    qDebug() << "目标的 buffer 是：" << mirrorBufferId;


    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------

    qDebug()<<sourceBuffer<<" finish bound";

    return true;
}

void AudioSource::switchAudio(const std::string& newFile) {
    std::lock_guard<std::mutex> lock(mtx);

    // 1. 停止播放并解绑所有缓冲区
    ALint state;
    alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
    bool wasPlaying = (state == AL_PLAYING);

    alSourceStop(sourceId);
    alSourcei(sourceId, AL_BUFFER, 0); // 清除绑定的缓冲区

    // 2. 释放旧的缓冲区数据
    ALint processed = 0;
    alGetSourcei(sourceId, AL_BUFFERS_PROCESSED, &processed);
    while (processed-- > 0) {
        ALuint buf;
        alSourceUnqueueBuffers(sourceId, 1, &buf);
    }

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    // 1. 停止播放并解绑所有缓冲区
    ALint mirrorState;
    alGetSourcei(mirrorSourceId, AL_SOURCE_STATE, &mirrorState);
    bool mirrorWasPlaying = (mirrorState == AL_PLAYING);

    alSourceStop(mirrorSourceId);
    alSourcei(mirrorSourceId, AL_BUFFER, 0); // 清除绑定的缓冲区

    // 2. 释放旧的缓冲区数据
    ALint mirrorProcessed = 0;
    alGetSourcei(mirrorSourceId, AL_BUFFERS_PROCESSED, &mirrorProcessed);
    while (mirrorProcessed-- > 0) {
        ALuint buf;
        alSourceUnqueueBuffers(mirrorSourceId, 1, &buf);
    }

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------

    // 3. 重新加载新音频数据
    if (!loadWavFile(newFile)) {
        std::cerr << "Error: Failed to load new WAV file: " << newFile << std::endl;
        return;
    }

    // 4. 重新绑定缓冲区
    alSourceQueueBuffers(sourceId, 1, &sourceBuffer);

    // 5. 只有之前在播放才恢复播放
    if (wasPlaying) {
        alSourcePlay(sourceId);
    }

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    // 4. 重新绑定缓冲区
    alSourceQueueBuffers(mirrorSourceId, 1, &mirrorBufferId);

    // 5. 只有之前在播放才恢复播放
    if (wasPlaying) {
        alSourcePlay(mirrorSourceId);
    }

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}

// 获取[left, right]范围的随机数
int getRandom(int left, int right) {
    return (rand() % (right - left))+ left + 1;
}

bool AudioSource::addFilter(OcclusionFilter* filterIndex)
{
    std::lock_guard<std::mutex> lock(mtx);
    if(!alIsFilter(filterIndex->getFilterId())) {
        qDebug()<<"no fileter";
        return false;
    }

    if(filterIndexs.find(filterIndex->getFilterId()) == filterIndexs.end()) {
        // 索引中没有该id
        filterIndexs[filterIndex->getFilterId()] = filterIndex;
    } else {
        qDebug()<<"过滤器已被添加";
        return true;
    }

    return true;
}

void AudioSource::removeFilter(const ALuint &filterId)
{
    std::lock_guard<std::mutex> lock(mtx);
    if(!alIsFilter(filterId)) {
        qDebug()<<"no fileter";
        return ;
    }

    if(filterIndexs.find(filterId) == filterIndexs.end()) {
        //qDebug()<<"no store this fileter index";
        return ;
    }
    filterIndexs.erase(filterId);

    // // 将辅助槽该位置设为空
    // alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER,
    //            auxEffectSlots.slotId, index, AL_FILTER_NULL);

    return ;
}

void AudioSource::updateFilter()
{
    std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);

    // 先重置为1.0
    float gain = 1.0f;
    float gainHF = 1.0f;
    float gainLF = 1.0f;
    // 如果为空就重置
    if(filterIndexs.empty()) {
        alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER,
                   auxEffectSlots.slotId, 0, AL_FILTER_NULL);
        alSourcei(sourceId, AL_DIRECT_FILTER, AL_FILTER_NULL);

        // 保存播放上下文并切换到录音上下文-------------------------------------------------
        ALCcontext* currentCtx = alcGetCurrentContext();
        alcMakeContextCurrent(recordCtx);

        alSource3i(mirrorSourceId, AL_AUXILIARY_SEND_FILTER,
                   auxEffectSlots.mirrorSlotId, 0, AL_FILTER_NULL);
        alSourcei(mirrorSourceId, AL_DIRECT_FILTER, AL_FILTER_NULL);

        // 切回原上下文
        alcMakeContextCurrent(currentCtx);
        // ----------------------------------------------------------------------------
        return;
    }
    // 依次叠加
    qDebug()<<filterIndexs.size();
    for(auto it : filterIndexs) {
        gain *= it.second->gain;
        gainHF *= it.second->gainHF;
        gainLF *= it.second->gainLF;
        qDebug()<<it.second->gain;
        qDebug()<<it.second->gainHF;
        qDebug()<<it.second->gainLF;
    }

    filter.updateParameters(gain, gainHF, gainLF);

    // 设置干声和混声的过滤
    alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER,
               auxEffectSlots.slotId, 0, filter.getFilterId());
    alSourcei(sourceId, AL_DIRECT_FILTER, filter.getFilterId());

    // 保存播放上下文并切换到录音上下文-------------------------------------------------
    ALCcontext* currentCtx = alcGetCurrentContext();
    alcMakeContextCurrent(recordCtx);

    alFilterf(mirrorFilterId, AL_BANDPASS_GAIN, gain);
    alFilterf(mirrorFilterId, AL_BANDPASS_GAINHF, gainHF);
    alFilterf(mirrorFilterId, AL_BANDPASS_GAINLF, gainLF);

    // 设置干声和混声的过滤
    alSource3i(mirrorSourceId, AL_AUXILIARY_SEND_FILTER,
               auxEffectSlots.mirrorSlotId, 0, mirrorFilterId);
    alSourcei(mirrorSourceId, AL_DIRECT_FILTER, mirrorFilterId);

    // 切回原上下文
    alcMakeContextCurrent(currentCtx);
    // ----------------------------------------------------------------------------
}
