
// 文件：occlusionfilterpanel.h
#ifndef OCCLUSIONFILTERPANEL_H
#define OCCLUSIONFILTERPANEL_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPainter>
#include "ui_occlusionfilterpanel.h"
#include "occlusionfilter.h"

namespace Ui {
class OcclusionFilterPanel;
}


class OcclusionFilterPanel : public QWidget
{
    Q_OBJECT

public:
    explicit OcclusionFilterPanel(QWidget *parent = nullptr);
    void setFilter(OcclusionFilter* filter);

// protected:
//     QSize sizeHint() const override;
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
