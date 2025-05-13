#include "audiosourcepanel.h"
#include "ui_audiosourcepanel.h"

AudioSourcePanel::AudioSourcePanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::AudioSourcePanel), m_source(nullptr)
{
    ui->setupUi(this);
    // // 关闭透明背景属性
    // setAttribute(Qt::WA_TranslucentBackground, false);
    // // 设置子部件的背景样式，例如设置为不透明的白色背景
    // setStyleSheet("background-color: white;");
    setMinimumSize(0, 0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    ui->volumeSlider->setRange(0, 100);
    ui->progressSlider->setRange(0, 1000);

    connect(ui->playPauseButton, &QPushButton::clicked, this, &AudioSourcePanel::onPlayPauseClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &AudioSourcePanel::onStopClicked);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &AudioSourcePanel::onVolumeChanged);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &AudioSourcePanel::updateProgress);
    m_timer->start(100);

    connect(ui->progressSlider, &QSlider::sliderPressed, this, [=]() {
        // std::mutex mutex;
        // std::lock_guard<std::mutex> lock(mutex);
        m_isDragging = true;
    });

    connect(ui->progressSlider, &QSlider::sliderReleased, this, [=]() {
        // std::mutex mutex;
        // std::lock_guard<std::mutex> lock(mutex);
        onProgressChanged();
        m_isDragging = false;
    });

}

AudioSourcePanel::~AudioSourcePanel() {
    delete ui;
}

// QSize AudioSourcePanel::sizeHint() const {
//     return QSize(0, 0); // 控制在合理范围内
// }

void AudioSourcePanel::setSource(AudioSource* source) {
    m_source = source;
    if (m_source) {
        ui->volumeSlider->setValue(static_cast<int>(m_source->volume * 100));
        m_durationSeconds = m_source->duration;  // 在 AudioSource 中补充 duration 读取
    }
}

void AudioSourcePanel::disconnectSource() {
    m_source = nullptr;

    ui->volumeSlider->setRange(0, 100);
    ui->progressSlider->setRange(0, 1000);
    m_timer->start(100);
}


void AudioSourcePanel::onPlayPauseClicked() {
    if (!m_source) return;
    if (m_source->isPlaying()) {
        m_source->pause();
        ui->playPauseButton->setText("播放");
    } else {
        m_source->play();
        ui->playPauseButton->setText("暂停");
    }
}

void AudioSourcePanel::onStopClicked() {
    if (!m_source) return;
    m_source->stop();
    ui->playPauseButton->setText("播放");
    ui->progressSlider->setValue(0);
}

void AudioSourcePanel::onVolumeChanged(int value) {
    if (!m_source) return;
    m_source->setVolume(value / 100.0f);
}

void AudioSourcePanel::onProgressChanged() {
    // std::mutex mutex;
    // std::lock_guard<std::mutex> lock(mutex);
    if (!m_source || m_durationSeconds <= 0.0f) return;
    float percentage = ui->progressSlider->value() / 1000.0f;
    float targetSec = percentage * m_durationSeconds;
    alSourcef(m_source->sourceId, AL_SEC_OFFSET, targetSec);
}

void AudioSourcePanel::updateProgress() {
    if (!m_source || !m_source->isPlaying() || m_isDragging) return;

    float offset = 0.0f;
    alGetSourcef(m_source->sourceId, AL_SEC_OFFSET, &offset);

    if (m_durationSeconds > 0.0f) {
        int sliderValue = static_cast<int>(offset / m_durationSeconds * 1000.0f);
        ui->progressSlider->setValue(sliderValue);

        auto formatTime = [](float sec) {
            int m = static_cast<int>(sec) / 60;
            int s = static_cast<int>(sec) % 60;
            return QString("%1:%2").arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0'));
        };

        ui->labelProgress->setText(
            formatTime(offset) + " / " + formatTime(m_durationSeconds));

    }
}

