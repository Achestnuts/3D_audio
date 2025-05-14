
// 文件：occlusionfilterpanel.h
#ifndef OCCLUSIONFILTERPANEL_H
#define OCCLUSIONFILTERPANEL_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPainter>
#include "ui_occlusionfilterpanel.h"
#include "occlusionfilter.h"

struct FilterTemplate {
    QString name;
    float gain;
    float gainHF;
    float gainLF;
};

const QVector<FilterTemplate> filterTemplates = {
    { "默认", 0.5f, 0.5f, 0.5f },
    { "墙体厚", 0.3f, 0.2f, 0.4f },
    { "玻璃", 0.8f, 0.9f, 0.6f }
};



namespace Ui {
class OcclusionFilterPanel;
}


class OcclusionFilterPanel : public QWidget
{
    Q_OBJECT

public:
    explicit OcclusionFilterPanel(QWidget *parent = nullptr);
    void setFilter(OcclusionFilter* filter);

    void onLoadTemplateClicked();
protected:
    QSize sizeHint() const override;
private slots:
    void onGainChanged(int value);
    void onGainHFChanged(int value);
    void onGainLFChanged(int value);
    void updateWaveform();

signals:
    void filterChanged();

private:
    void disconnectCurrentFilter();
    Ui::OcclusionFilterPanel *ui;
    OcclusionFilter* m_filter;
    QTimer* m_waveformTimer;
    QVector<float> waveformPoints;
};

#endif // OCCLUSIONFILTERPANEL_H
