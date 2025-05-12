#include "occlusionfilterpanel.h"
#include <QtMath>
#include <QTime>
#include <audiomanager.h>

OcclusionFilterPanel::OcclusionFilterPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::OcclusionFilterPanel), m_filter(nullptr)
{
    ui->setupUi(this);
    // // 关闭透明背景属性
    // setAttribute(Qt::WA_TranslucentBackground, false);
    // // 设置子部件的背景样式，例如设置为不透明的白色背景
    // setStyleSheet("background-color: white;");
    setMinimumSize(0, 0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    ui->knobGain->setRange(0, 100);
    ui->knobGainHF->setRange(0, 100);
    ui->knobGainLF->setRange(0, 100);

    connect(ui->knobGain, &QDial::valueChanged, this, &OcclusionFilterPanel::onGainChanged);
    connect(ui->knobGainHF, &QDial::valueChanged, this, &OcclusionFilterPanel::onGainHFChanged);
    connect(ui->knobGainLF, &QDial::valueChanged, this, &OcclusionFilterPanel::onGainLFChanged);

    m_waveformTimer = new QTimer(this);
    connect(m_waveformTimer, &QTimer::timeout, this, &OcclusionFilterPanel::updateWaveform);
    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    connect(this, &OcclusionFilterPanel::filterChanged, [=](){
        audioManager->updateEffectSlots();
    });
    m_waveformTimer->start(33); // ~30fps
}

void OcclusionFilterPanel::disconnectCurrentFilter() {
    // 可选：断开旧连接（如果 filter 是 QObject 派生类，可在这里处理）
    m_filter = nullptr;
}

void OcclusionFilterPanel::setFilter(OcclusionFilter* filter) {
    disconnectCurrentFilter();
    m_filter = filter;

    if (!m_filter) return;

    ui->knobGain->setValue(static_cast<int>(m_filter->gain * 100));
    ui->knobGainHF->setValue(static_cast<int>(m_filter->gainHF * 100));
    ui->knobGainLF->setValue(static_cast<int>(m_filter->gainLF * 100));

    ui->labelGain->setText(QString::number(m_filter->gain, 'f', 2));
    ui->labelGainHF->setText(QString::number(m_filter->gainHF, 'f', 2));
    ui->labelGainLF->setText(QString::number(m_filter->gainLF, 'f', 2));

    emit filterChanged();
}

void OcclusionFilterPanel::onGainChanged(int value) {
    if (m_filter) {
        float g = value / 100.0f;
        m_filter->updateParameters(g, m_filter->gainHF, m_filter->gainLF);
        ui->labelGain->setText(QString::number(g, 'f', 2));
    }
}

void OcclusionFilterPanel::onGainHFChanged(int value) {
    if (m_filter) {
        float hf = value / 100.0f;
        m_filter->updateParameters(m_filter->gain, hf, m_filter->gainLF);
        ui->labelGainHF->setText(QString::number(hf, 'f', 2));
    }
}

void OcclusionFilterPanel::onGainLFChanged(int value) {
    if (m_filter) {
        float lf = value / 100.0f;
        m_filter->updateParameters(m_filter->gain, m_filter->gainHF, lf);
        ui->labelGainLF->setText(QString::number(lf, 'f', 2));
    }
}

void OcclusionFilterPanel::updateWaveform() {
    // QVector<float> data;
    // float base = m_filter ? m_filter->gain : 0.5f;
    // float freq = m_filter ? 3.0f + m_filter->gainHF * 5.0f : 5.0f;
    // int t = QTime::currentTime().msec();

    // for (int i = 0; i < 100; ++i) {
    //     float val = base * qSin((i + t / 10.0f) * freq * 0.1f);
    //     data.append(val);
    // }
    if(!m_filter) {
        ui->waveformWidget->setFilterParams(0.5f, 0.5f, 0.5f);
        return;
    }

    ui->waveformWidget->setFilterParams(m_filter->gain, m_filter->gainHF, m_filter->gainLF);  // 使用 set 方法传给自定义组件
}

