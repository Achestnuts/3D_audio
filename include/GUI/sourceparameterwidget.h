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
    {
        "默认环境",
        1.0f, 1.0f,
        0.02f, 1.0f,
        0.01f, 1.0f,
        1.0f, 1.0f,
        0.7f, 1.0f,
        1.2f, 1.0f,
        0.994f, 1.0f,
        0.83f, 1.0f,
        1.0f, 1.0f,
        1.0f, 1.0f
    },
    {
        "混响大厅",
        1.5f, 1.2f,
        0.05f, 1.1f,
        0.03f, 1.0f,
        1.2f, 1.1f,
        0.9f, 1.2f,
        1.4f, 1.1f,
        0.98f, 1.0f,
        0.7f, 1.1f,
        1.0f, 1.0f,
        1.0f, 1.0f
    },
    {
        "户外空间",
        0.8f, 0.9f,
        0.01f, 0.8f,
        0.005f, 0.9f,
        0.6f, 0.8f,
        0.3f, 0.9f,
        0.9f, 0.8f,
        0.999f, 1.0f,
        0.6f, 0.9f,
        0.5f, 0.9f,
        0.5f, 0.8f
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

public slots:
    //void parametersChanged();

protected:
    QSize sizeHint() const override;
private:


};

#endif // SOURCEPARAMETERWIDGET_H
