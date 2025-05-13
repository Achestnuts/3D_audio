#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <AL/alc.h>

class AudioRecorder : public QObject
{
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = nullptr, const ALCchar* deviceName = nullptr);
    ~AudioRecorder();

    bool init();
    bool startRecording(const QString &filename);
    void pauseRecording();
    void stopRecording();
    bool isRecording() const;

    bool saveRecording(const QString &tempFilePath, const QString &filePath, const QString &format);
signals:
    void recordingStopped();
    void recordingTimeUpdated(float seconds);

private:
    void captureLoop();
    void writeWavHeader();
    void finalizeWavHeader();

    QFile m_outputFile;
    QByteArray m_pcmBuffer;
    QTimer* m_timer;
    bool m_isRecording = false;

    float m_elapsedSeconds = 0.0f;
    int m_sampleRate = 48000;
    int m_channels = 2;
    int m_bits = 16;

    ALCdevice* m_loopbackDevice = nullptr;
    ALCchar* soundDeviceName = nullptr;
    ALCcontext* m_loopbackContext = nullptr;

    // 添加函数指针声明
    typedef void (ALC_APIENTRY* LPALCRENDERSAMPLESSOFT)(ALCdevice *, ALCvoid *, ALCsizei);
    LPALCRENDERSAMPLESSOFT alcRenderSamplesSOFT = nullptr;

    ALCenum ALC_FORMAT_CHANNELS_SOFT;
    ALCenum ALC_FORMAT_TYPE_SOFT;
    ALCenum ALC_SHORT_SOFT;
};

#endif // AUDIORECORDER_H
