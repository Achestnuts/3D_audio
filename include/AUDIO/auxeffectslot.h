#ifndef AUXEFFECTSLOT_H
#define AUXEFFECTSLOT_H

#include "AL/al.h"
#include <mutex>
#define AL_ALEXT_PROTOTYPES
#include <AL/efx.h>

#include <QObject>
#include <QVector3D>

// 辅助效果槽参数 前右后左：0123
#define FrontEffect 0
#define RightEffect 1
#define BackEffect 2
#define LeftEffect 3

class AuxEffectSlot : public QObject
{
    Q_OBJECT
public:

    AuxEffectSlot();
    // bool setDirection(int dir);
    bool updateEffectParams(float estimateRoomSize, QVector3D reflection, float gainFactor);
    bool resetEffect();

    void mirrorInit();

    ALuint slotId;   // 效果槽ID
    ALuint effectId; // 效果器ID

    ALCcontext* recordCtx;
    ALuint mirrorSlotId;
    ALuint mirrorEffectId;

    // float reflectDir[3];

    float decayTimeIntercept;
    float decayTimeFactor;
    float reflectionsDelayIntercept;
    float reflectionsDelayFactor;
    float lateReverbDelayIntercept;
    float lateReverbDelayFactor;
    float gainIntercept;
    float gainFactor;
    float reflectionsGainIntercept;
    float reflectionsGainFactor;
    float lateReverbGainIntercept;
    float lateReverbGainFactor;
    float airAbsorptionHFIntercept;
    float airAbsorptionHFFactor;
    float decayHFRatioIntercept;
    float decayHFRatioFactor;
    float decayLFRatioIntercept;
    float decayLFRatioFactor;
    float diffusionIntercept;
    float diffusionFactor;
    float densityIntercept;
    float densityFactor;

    float roomSize;
    float decayTime;
    float reflectionsDelay;
    float lateReverbDelay;
    float gain;
    float reflectionsGain;
    float lateReverbGain;
    float airAbsorptionHF;
    float decayHFRatio;
    float decayLFRatio;
    float diffusion;
    float density;

signals:
    void roomSizeChange(float newRoomSize);

private:
    std::mutex m_mutex; // 用于保护状态和 OpenAL API 调用
};

#endif // AUXEFFECTSLOT_H
