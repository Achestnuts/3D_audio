#ifndef OCCLUSIONFILTER_H
#define OCCLUSIONFILTER_H

#define AL_ALEXT_PROTOTYPES

#include <AL/al.h>
#include <AL/efx.h>
#include <mutex>

/**
 * OcclusionFilter 封装了 OpenAL Filter 对象，用于模拟墙体遮挡导致的音频过滤效果。
 * 目前采用带通滤波器 AL_FILTER_BANDPASS，允许外部设置 cutoff 相关参数（例如 AL_LOWPASS_GAINHF）。
 */
class OcclusionFilter {
public:
    OcclusionFilter();
    ~OcclusionFilter();

    // 设置滤波器类型为低通，并初始化默认参数
    bool init();

    float gain;
    float gainHF;
    float gainLF;

    /**
     * 更新滤波器参数。
     * @param gain: 总体增益，控制过滤后的音量（0～1）
     * @param gainHF: 高频增益，用于控制高频衰减效果，值越低，高频衰减越严重
     * @param gainLF: 低频增益，用于控制低频衰减效果，值越低，低频衰减越严重
     */
    bool updateParameters(float gain, float gainHF, float gainLF);

    // 获取内部 Filter ID
    ALuint getFilterId() const;

private:
    ALuint filterId;      // OpenAL Filter 对象 ID
    mutable std::mutex mtx;       // 保护 filterId 和参数设置的互斥量
};

#endif // OCCLUSIONFILTER_H
