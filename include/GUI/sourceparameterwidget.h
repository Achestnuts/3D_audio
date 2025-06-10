#ifndef SOURCEPARAMETERWIDGET_H
#define SOURCEPARAMETERWIDGET_H

#include "draggablesource.h"
#include <QWidget>

struct ReverbTemplate {
    QString name;
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
};


const QVector<ReverbTemplate> reverbTemplates = {
    // {
    //     "默认环境",
    //     1.0f, 1.0f,
    //     0.02f, 1.0f,
    //     0.01f, 1.0f,
    //     1.0f, 1.0f,
    //     0.7f, 1.0f,
    //     1.2f, 1.0f,
    //     0.994f, 1.0f,
    //     0.83f, 1.0f,
    //     1.0f, 1.0f,
    //     1.0f, 1.0f
    // },
    // {
    //     "混响大厅",
    //     1.5f, 1.2f,
    //     0.05f, 1.1f,
    //     0.03f, 1.0f,
    //     1.2f, 1.1f,
    //     0.9f, 1.2f,
    //     1.4f, 1.1f,
    //     0.98f, 1.0f,
    //     0.7f, 1.1f,
    //     1.0f, 1.0f,
    //     1.0f, 1.0f
    // },
    // {
    //     "户外空间",
    //     0.8f, 0.9f,
    //     0.01f, 0.8f,
    //     0.005f, 0.9f,
    //     0.6f, 0.8f,
    //     0.3f, 0.9f,
    //     0.9f, 0.8f,
    //     0.999f, 1.0f,
    //     0.6f, 0.9f,
    //     0.5f, 0.9f,
    //     0.5f, 0.8f
    // },
    {
        "小而明亮的房间",
        0.5f, 0.1f,      // decayTimeIntercept, decayTimeFactor
        0.01f, 0.005f,   // reflectionsDelayIntercept, reflectionsDelayFactor
        0.02f, 0.002f,   // lateReverbDelayIntercept, lateReverbDelayFactor
        0.8f, -0.05f,    // gainIntercept, gainFactor（大房间降低总增益）
        1.5f, -0.05f,    // reflectionsGainIntercept, reflectionsGainFactor（大房间减少早期反射）
        3.0f, 0.1f,      // lateReverbGainIntercept, lateReverbGainFactor
        0.95f, -0.005f,  // airAbsorptionHFIntercept, airAbsorptionHFFactor（大房间增加高频吸收）
        1.2f, -0.05f,    // decayHFRatioIntercept, decayHFRatioFactor（大房间减少高频衰减比）
        0.9f, -0.02f,    // decayLFRatioIntercept, decayLFRatioFactor
        0.7f, 0.05f,     // diffusionIntercept, diffusionFactor
        0.9f, -0.02f     // densityIntercept, densityFactor（大房间降低密度）
    },
    {
        "大型音乐厅",
        1.5f, 0.3f,      // decayTimeIntercept, decayTimeFactor
        0.05f, 0.01f,    // reflectionsDelayIntercept, reflectionsDelayFactor
        0.05f, 0.005f,   // lateReverbDelayIntercept, lateReverbDelayFactor
        0.7f, -0.05f,    // gainIntercept, gainFactor
        0.8f, -0.05f,    // reflectionsGainIntercept, reflectionsGainFactor
        5.0f, 0.2f,      // lateReverbGainIntercept, lateReverbGainFactor
        0.9f, -0.01f,    // airAbsorptionHFIntercept, airAbsorptionHFFactor
        0.8f, 0.03f,     // decayHFRatioIntercept, decayHFRatioFactor（大房间增加高频衰减）
        1.0f, 0.05f,     // decayLFRatioIntercept, decayLFRatioFactor
        0.9f, -0.02f,    // diffusionIntercept, diffusionFactor（大房间降低扩散）
        0.95f, -0.01f    // densityIntercept, densityFactor
    },
    {
        "金属仓库",
        2.0f, 0.4f,      // decayTimeIntercept, decayTimeFactor
        0.03f, 0.005f,   // reflectionsDelayIntercept, reflectionsDelayFactor
        0.03f, 0.005f,   // lateReverbDelayIntercept, lateReverbDelayFactor
        0.7f, -0.05f,    // gainIntercept, gainFactor
        2.0f, -0.1f,     // reflectionsGainIntercept, reflectionsGainFactor
        8.0f, 0.3f,      // lateReverbGainIntercept, lateReverbGainFactor
        0.98f, -0.002f,  // airAbsorptionHFIntercept, airAbsorptionHFFactor
        1.5f, -0.05f,    // decayHFRatioIntercept, decayHFRatioFactor
        1.2f, -0.05f,    // decayLFRatioIntercept, decayLFRatioFactor
        0.6f, 0.05f,     // diffusionIntercept, diffusionFactor
        0.8f, -0.03f     // densityIntercept, densityFactor
    },
    {
        "吸音房间",
        0.3f, 0.05f,     // decayTimeIntercept, decayTimeFactor
        0.005f, 0.001f,  // reflectionsDelayIntercept, reflectionsDelayFactor
        0.01f, 0.001f,   // lateReverbDelayIntercept, lateReverbDelayFactor
        0.9f, -0.02f,    // gainIntercept, gainFactor
        0.2f, -0.01f,    // reflectionsGainIntercept, reflectionsGainFactor
        0.5f, -0.02f,    // lateReverbGainIntercept, lateReverbGainFactor（大房间进一步减少后期混响）
        0.99f, -0.001f,  // airAbsorptionHFIntercept, airAbsorptionHFFactor
        0.5f, 0.01f,     // decayHFRatioIntercept, decayHFRatioFactor（大房间增加高频衰减）
        0.7f, 0.01f,     // decayLFRatioIntercept, decayLFRatioFactor
        0.3f, 0.02f,     // diffusionIntercept, diffusionFactor
        0.4f, -0.01f     // densityIntercept, densityFactor
    },
    {
        "洞穴",
        3.0f, 0.5f,      // decayTimeIntercept, decayTimeFactor
        0.07f, 0.01f,    // reflectionsDelayIntercept, reflectionsDelayFactor
        0.07f, 0.01f,    // lateReverbDelayIntercept, lateReverbDelayFactor
        0.6f, -0.05f,    // gainIntercept, gainFactor
        1.2f, -0.07f,    // reflectionsGainIntercept, reflectionsGainFactor
        6.0f, 0.3f,      // lateReverbGainIntercept, lateReverbGainFactor
        0.892f, 0.001f,  // airAbsorptionHFIntercept, airAbsorptionHFFactor（大洞穴略微增加高频吸收）
        0.3f, 0.01f,     // decayHFRatioIntercept, decayHFRatioFactor（大洞穴进一步减少高频）
        1.8f, -0.05f,    // decayLFRatioIntercept, decayLFRatioFactor（大洞穴减少低频衰减）
        0.5f, 0.03f,     // diffusionIntercept, diffusionFactor
        0.6f, -0.02f     // densityIntercept, densityFactor
    }
};


namespace Ui {
class SourceParameterWidget;
}

class SourceParameterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SourceParameterWidget(QWidget *parent = nullptr);
    void disconnectBound();
    bool boundSource(DraggableSource* boundSource);
    Ui::SourceParameterWidget *ui;
    DraggableSource* source;
    void onLoadTemplateClicked();

    void reset();
public slots:
    //void parametersChanged();

protected:
    QSize sizeHint() const override;
private:


};

#endif // SOURCEPARAMETERWIDGET_H
