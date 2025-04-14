#include "OcclusionFilter.h"
#include <QDebug>

OcclusionFilter::OcclusionFilter() {
    // 构造函数中不直接创建 Filter，对象的初始化由 init() 完成
    init();
}

OcclusionFilter::~OcclusionFilter() {
    std::lock_guard<std::mutex> lock(mtx);
    if (filterId) {
        alDeleteFilters(1, &filterId);
        filterId = 0;
    }
}

bool OcclusionFilter::init() {
    std::lock_guard<std::mutex> lock(mtx);

    gain = 1.0f;
    gainHF = 1.0f;
    gainLF = 1.0f;
    alGenFilters(1, &filterId);
    if (alGetError() != AL_NO_ERROR) {
        qDebug() << "Failed to generate filter";
        return false;
    }
    // 设置为带通滤波器
    alFilteri(filterId, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
    if (alGetError() != AL_NO_ERROR) {
        qDebug() << "Failed to set filter type";
        return false;
    }
    // 初始化默认参数
    alFilterf(filterId, AL_BANDPASS_GAIN, 1.0f);
    alFilterf(filterId, AL_BANDPASS_GAINHF, 1.0f);
    alFilterf(filterId, AL_BANDPASS_GAINLF, 1.0f); // 如果需要设置低频参数

    return (alGetError() == AL_NO_ERROR);
}

bool OcclusionFilter::updateParameters(float newGain, float newGainHF, float newGainLF) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!filterId) return false;

    gain = newGain;
    gainHF = newGainHF;
    gainLF = newGainLF;

    // 更新带通滤波器参数：
    // gain: 整体增益（对整个滤波器效果的一个全局调节）
    // gainHF: 高频增益，通常在 0～1 之间，值越低表示更强的高频衰减
    // gainLF: 低频增益，通常在 0～1 之间，值越低表示更强的低频衰减
    alFilterf(filterId, AL_BANDPASS_GAIN, gain);
    alFilterf(filterId, AL_BANDPASS_GAINHF, gainHF);
    alFilterf(filterId, AL_BANDPASS_GAINLF, gainLF);

    if (alGetError() != AL_NO_ERROR) {
        qDebug() << "Error updating filter parameters";
        return false;
    }

    return true;
}

ALuint OcclusionFilter::getFilterId() const {
    std::lock_guard<std::mutex> lock(mtx);
    return filterId;
}
