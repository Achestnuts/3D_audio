#include "auxeffectslot.h"
#include <cstring>
#include <qDebug>


AuxEffectSlot::AuxEffectSlot() {
    std::lock_guard<std::mutex> lock(m_mutex);
    // 生成效果槽与效果器
    alGenAuxiliaryEffectSlots(1, &slotId);
    alGenEffects(1, &effectId);

    qDebug()<<"effect效果槽准备创建";

    // reflectDir[0]=0, reflectDir[1]=0, reflectDir[2]=0;

    roomSize = 0;

    decayTimeIntercept = 0.5f;
    decayTimeFactor = 0.3f;
    reflectionsDelayIntercept = 0.0f;
    reflectionsDelayFactor = 0.005f;
    lateReverbDelayIntercept = 0.0f;
    lateReverbDelayFactor = 0.001f;
    gainIntercept = 1.5f;
    gainFactor = -0.04f;
    reflectionsGainIntercept = 1.2f;
    reflectionsGainFactor = -0.015f;
    lateReverbGainIntercept = 1.8f;
    lateReverbGainFactor = -0.01f;
    airAbsorptionHFIntercept = 0.994f;
    airAbsorptionHFFactor = -0.0001f;
    decayHFRatioIntercept = 1.0f;
    decayHFRatioFactor = -0.005f;
    decayLFRatioIntercept = 1.0f;
    decayLFRatioFactor = 0.003f;
    diffusionIntercept = 0.8f;
    diffusionFactor = 0.005f;
    densityIntercept = 0.6f;
    densityFactor = -0.002f;

    //resetEffect();

    // 绑定效果到效果槽
    alAuxiliaryEffectSloti(slotId, AL_EFFECTSLOT_EFFECT, effectId);
}

// bool AuxEffectSlot::setDirection(int dir) {
//     std::lock_guard<std::mutex> lock(m_mutex);
//     float reflectDir[3] = {0.0f, 0.0f, 0.0f};

//     if(dir == FrontEffect) {
//         reflectDir[2] = -1.0f;
//     } else if(dir == RightEffect) {
//         reflectDir[0] = -1.0f;
//     } else if(dir == BackEffect) {
//         reflectDir[2] = 1.0f;
//     } else if(dir == LeftEffect) {
//         reflectDir[0] = 1.0f;
//     } else {
//         return true;
//     }
//     return true;
// }

bool AuxEffectSlot::resetEffect() {
    std::lock_guard<std::mutex> lock(m_mutex);
    // 设置效果器初始混响参数
    alEffecti(effectId, AL_EFFECT_TYPE, AL_EFFECT_NULL);
    alAuxiliaryEffectSloti(slotId, AL_EFFECTSLOT_EFFECT, effectId);

    return true;
}

bool AuxEffectSlot::updateEffectParams(float estimateRoomSize, QVector3D reflection, float wallGain) {
    std::lock_guard<std::mutex> lock(m_mutex);
    qDebug()<<"准备发送更新";
    emit roomSizeChange(estimateRoomSize);
    qDebug()<<"已发送更新";


    // 参数范围约束函数
    auto clamp = [](float value, float min, float max) {
        return std::fmax(min, std::fmin(value, max));
    };

    // 基础参数计算（基于房间体积的立方根估算线性尺寸）
    const float linearSize = estimateRoomSize;
    roomSize = estimateRoomSize;

    // 1. 时间相关参数
    decayTime = clamp(decayTimeIntercept + linearSize * decayTimeFactor, 0.1f, 20.0f);       // 衰减时间：0.1-20秒
    reflectionsDelay = clamp(reflectionsDelayIntercept + linearSize * reflectionsDelayFactor, 0.0f, 0.3f);      // 反射延迟：0-0.3秒
    lateReverbDelay = clamp(lateReverbDelayIntercept + linearSize * lateReverbDelayFactor, 0.0f, 0.1f);       // 混响延迟：0-0.1秒

    // 2. 能量相关参数
    gain = clamp(wallGain * (gainIntercept + linearSize * gainFactor), 0.1f, 1.0f);            // 总增益：0.0-1.0
    reflectionsGain = clamp(reflectionsGainIntercept + linearSize * reflectionsGainFactor, 0.0f, 3.16f);// 反射增益：0.0-3.16
    lateReverbGain = clamp(lateReverbGainIntercept + linearSize * lateReverbGainFactor, 0.0f, 10.0f); // 后期混响增益：0.0-10.

    // 3. 频率特性
    airAbsorptionHF = clamp(airAbsorptionHFIntercept + linearSize * airAbsorptionHFFactor, 0.892f, 1.0f); // 高频空气吸收
    decayHFRatio = clamp(decayHFRatioIntercept + linearSize * decayHFRatioFactor, 0.1f, 2.0f);   // 高频衰减比
    decayLFRatio = clamp(decayLFRatioIntercept + linearSize * decayLFRatioFactor, 0.1f, 2.0f);   // 低频衰减比

    // 4. 空间特性
    diffusion = clamp(diffusionIntercept + linearSize * diffusionFactor, 0.0f, 1.0f);      // 扩散度
    density = clamp(densityIntercept - linearSize * densityFactor, 0.0f, 1.0f);        // 密度

    // 设置EAX Reverb参数
    alEffecti(effectId, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);

    // 时间参数
    alEffectf(effectId, AL_EAXREVERB_DECAY_TIME, decayTime);
    alEffectf(effectId, AL_EAXREVERB_REFLECTIONS_DELAY, reflectionsDelay);
    alEffectf(effectId, AL_EAXREVERB_LATE_REVERB_DELAY, lateReverbDelay);

    // 能量参数
    alEffectf(effectId, AL_EAXREVERB_GAIN, gain);
    alEffectf(effectId, AL_EAXREVERB_REFLECTIONS_GAIN, reflectionsGain);
    alEffectf(effectId, AL_EAXREVERB_LATE_REVERB_GAIN, lateReverbGain);

    // 频率参数
    alEffectf(effectId, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, airAbsorptionHF);
    alEffectf(effectId, AL_EAXREVERB_DECAY_HFRATIO, decayHFRatio);
    alEffectf(effectId, AL_EAXREVERB_DECAY_LFRATIO, decayLFRatio);

    // 空间特性
    alEffectf(effectId, AL_EAXREVERB_DIFFUSION, diffusion);
    alEffectf(effectId, AL_EAXREVERB_DENSITY, density);

    // 固定参数（可根据需要调整）
    alEffectf(effectId, AL_EAXREVERB_HFREFERENCE, 5000.0f);    // 高频参考点5kHz
    alEffectf(effectId, AL_EAXREVERB_LFREFERENCE, 250.0f);     // 低频参考点250Hz
    alEffecti(effectId, AL_EAXREVERB_DECAY_HFLIMIT, AL_TRUE);  // 启用高频衰减限制

    // 检查错误
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        // 处理错误...
    }
    float reflectDir[] = {reflection.x(), reflection.y(), reflection.z()};
    alEffectfv(effectId, AL_EAXREVERB_REFLECTIONS_PAN, reflectDir);

    alAuxiliaryEffectSloti(slotId, AL_EFFECTSLOT_EFFECT, effectId);
    return true;
}

