#include "waveformwidget.h"
#include <QPainter>

WaveformWidget::WaveformWidget(QWidget *parent) : QWidget(parent) {}

void WaveformWidget::setFilterParams(float gain, float gainLF, float gainHF)
{
    // 模拟频率响应数据
    waveformPoints.clear();
    const int N = 200;
    for (int i = 0; i < N; ++i) {
        float f = i / static_cast<float>(N - 1);  // 归一化频率 [0, 1]

        // 模拟带通响应图像（简化）：中间频率增益最大，两端低
        float gainValue = gain * qExp(-std::pow((f - 0.5f) * 5.0f / (gainHF + 0.01f), 2));
        gainValue *= qExp(-std::pow((f - 0.5f) * 5.0f / (gainLF + 0.01f), 2));
        waveformPoints.append(gainValue);
    }

    update();
}

void WaveformWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 2));

    int w = width();
    int h = height();

    for (int i = 1; i < waveformPoints.size(); ++i) {
        float x1 = (i - 1) * w / static_cast<float>(waveformPoints.size());
        float y1 = h - waveformPoints[i - 1] * h;
        float x2 = i * w / static_cast<float>(waveformPoints.size());
        float y2 = h - waveformPoints[i] * h;
        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }
}
