#ifndef AUDIOSOURCEPANEL_H
#define AUDIOSOURCEPANEL_H

#include <QWidget>
#include <QTimer>
#include "audiosource.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AudioSourcePanel;
}
QT_END_NAMESPACE

class AudioSourcePanel : public QWidget {
    Q_OBJECT

public:
    explicit AudioSourcePanel(QWidget *parent = nullptr);
    ~AudioSourcePanel();

    void setSource(AudioSource* source);
    void disconnectSource();

protected:
    // QSize sizeHint() const override;
private slots:
    void onPlayPauseClicked();
    void onStopClicked();
    void onVolumeChanged(int value);
    void onProgressChanged();
    void updateProgress();

private:
    Ui::AudioSourcePanel *ui;
    AudioSource *m_source;
    QTimer *m_timer;
    float m_durationSeconds = 0.0f;
    bool m_isDragging = false;  // 进度条是否被拖拽

};

#endif // AUDIOSOURCEPANEL_H
