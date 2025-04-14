#include "audiorecorder.h"
#include "AL/al.h"
#include "AL/alc.h"
#include <QDebug>
#include <QDataStream>
#include <vector>

#define AL_ALEXT_PROTOTYPES
#include <AL/alc.h>

AudioRecorder::AudioRecorder(QObject *parent, const ALCchar* deviceName) : QObject(parent),
    m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &AudioRecorder::captureLoop);
    soundDeviceName = const_cast<ALCchar*>(deviceName);
}

AudioRecorder::~AudioRecorder() {
    stopRecording();
}

bool AudioRecorder::startRecording(const QString &filename) {
    if (m_isRecording) return false;

    typedef ALCdevice* (*LPALCLOOPBACKOPENDEVICESOFT)(const ALCchar*);
    LPALCLOOPBACKOPENDEVICESOFT alcLoopbackOpenDeviceSOFT = (LPALCLOOPBACKOPENDEVICESOFT)alcGetProcAddress(nullptr, "alcLoopbackOpenDeviceSOFT");
    if (!alcLoopbackOpenDeviceSOFT) {
        qDebug() << "Failed to get alcLoopbackOpenDeviceSOFT function pointer.";
        //alcCloseDevice(device);
        return 1;
    }

    m_loopbackDevice = alcLoopbackOpenDeviceSOFT(soundDeviceName);
    if (!m_loopbackDevice) {
        qWarning() << "Failed to open loopback device.";
        return false;
    }

    ALCenum err = alcGetError(m_loopbackDevice);
    if(err != ALC_NO_ERROR) {
        qWarning() << "Render error:" << alcGetString(m_loopbackDevice, err);
    }

    // 获取枚举值
    ALCenum ALC_FORMAT_CHANNELS_SOFT = alcGetEnumValue(m_loopbackDevice, "ALC_FORMAT_CHANNELS_SOFT");
    ALCenum ALC_FORMAT_TYPE_SOFT = alcGetEnumValue(m_loopbackDevice, "ALC_FORMAT_TYPE_SOFT");
    ALCenum ALC_SHORT_SOFT = alcGetEnumValue(m_loopbackDevice, "ALC_SHORT_SOFT");
    if (ALC_FORMAT_CHANNELS_SOFT == AL_NONE || ALC_FORMAT_TYPE_SOFT == AL_NONE || ALC_SHORT_SOFT == AL_NONE) {
        qDebug() << "Failed to get enum value.";
        alcCloseDevice(m_loopbackDevice);
        //alcCloseDevice(device);
        return false;
    }

    // 打印枚举值进行调试
    qDebug() << "ALC_FORMAT_CHANNELS_SOFT: " << ALC_FORMAT_CHANNELS_SOFT;
    qDebug() << "ALC_FORMAT_TYPE_SOFT: " << ALC_FORMAT_TYPE_SOFT;
    qDebug() << "ALC_SHORT_SOFT: " << ALC_SHORT_SOFT;

    // 验证参数
    if (m_sampleRate <= 0 || (m_channels != 1 && m_channels != 2)) {
        qCritical() << "Invalid parameters: channels=" << m_channels
                    << " sampleRate=" << m_sampleRate;
        alcCloseDevice(m_loopbackDevice);
        return false;
    }

    // 替换原有属性设置代码
    ALCenum ALC_MONO_SOFT = alcGetEnumValue(m_loopbackDevice, "ALC_MONO_SOFT");
    ALCenum ALC_STEREO_SOFT = alcGetEnumValue(m_loopbackDevice, "ALC_STEREO_SOFT");
    // 设置正确的通道格式
    const ALCenum channelFormat = (m_channels == 1) ?
                                      ALC_MONO_SOFT : ALC_STEREO_SOFT;

    ALCint attrs[] = {
        ALC_FORMAT_CHANNELS_SOFT, channelFormat,
        ALC_FORMAT_TYPE_SOFT, ALC_SHORT_SOFT,
        ALC_FREQUENCY, m_sampleRate,
        0  // 必须的终止符
    };

    // 创建上下文
    m_loopbackContext = alcCreateContext(m_loopbackDevice, attrs);
    if (!m_loopbackContext) {
        const ALCenum error = alcGetError(m_loopbackDevice);
        qCritical() << "Context creation failed (Error: 0x"
                    << Qt::hex << error << ")";
        alcCloseDevice(m_loopbackDevice);
        return false;
    }

    // 在创建上下文后获取渲染函数
    alcRenderSamplesSOFT = reinterpret_cast<LPALCRENDERSAMPLESSOFT>(
        alcGetProcAddress(m_loopbackDevice, "alcRenderSamplesSOFT")
        );
    if (!alcRenderSamplesSOFT) {
        qCritical() << "Failed to get alcRenderSamplesSOFT";
        alcDestroyContext(m_loopbackContext);
        alcCloseDevice(m_loopbackDevice);
        return false;
    }

    m_outputFile.setFileName(filename);
    if (!m_outputFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing.";
        return false;
    }

    // 在startRecording中添加格式验证
    ALCint actualFormat;
    alcGetIntegerv(m_loopbackDevice, ALC_FORMAT_CHANNELS_SOFT, 1, &actualFormat);
    qDebug() << "Actual channel format:" << actualFormat;

    ALCint actualRate;
    alcGetIntegerv(m_loopbackDevice, ALC_FREQUENCY, 1, &actualRate);
    qDebug() << "Actual sample rate:" << actualRate;

    m_pcmBuffer.clear();
    writeWavHeader();

    m_isRecording = true;
    m_elapsedSeconds = 0;
    // 根据缓冲区大小计算精确间隔
    constexpr int framesPerBuffer = 512;
    const int bufferDurationMs = (framesPerBuffer * 1000) / m_sampleRate;
    m_timer->start(bufferDurationMs); // 512帧 → 约12ms
    return true;
}

void AudioRecorder::pauseRecording() {
    m_isRecording = false;
    m_timer->stop();
}

void AudioRecorder::stopRecording() {
    if (!m_isRecording && !m_outputFile.isOpen()) return;

    m_isRecording = false;
    m_timer->stop();

    finalizeWavHeader();
    m_outputFile.close();

    if (m_loopbackContext) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_loopbackContext);
        m_loopbackContext = nullptr;
    }

    if (m_loopbackDevice) {
        alcCloseDevice(m_loopbackDevice);
        m_loopbackDevice = nullptr;
    }

    emit recordingStopped();
}

bool AudioRecorder::isRecording() const {
    return m_isRecording;
}

// void AudioRecorder::captureLoop() {
//     constexpr int framesPerBuffer = 512;
//     std::vector<short> buffer(framesPerBuffer * m_channels);

//     alcRenderSamplesSOFT(m_loopbackDevice, buffer.data(), framesPerBuffer);

//     // 在captureLoop中添加调试代码
//     short firstSample = buffer.empty() ? 0 : buffer[0];
//     if(!buffer.empty())qDebug() << "First sample value:" << firstSample;

//     m_pcmBuffer.append(
//         reinterpret_cast<const char*>(buffer.data()),
//         buffer.size() * sizeof(short)
//         );
// }

void AudioRecorder::captureLoop() {
    constexpr int framesPerBuffer = 512;
    std::vector<short> buffer(framesPerBuffer * m_channels); // 缓冲区大小 = 帧数 × 通道数（每通道16位=2字节）

    // 渲染音频数据
    alcRenderSamplesSOFT(m_loopbackDevice, buffer.data(), framesPerBuffer);
    ALCenum error = alcGetError(m_loopbackDevice);
    if (error != ALC_NO_ERROR) {
        // 获取并打印OpenAL错误码（比单纯输出字符串更准确）
        qWarning() << "Render failed. Error code: 0x" << Qt::hex << error;
        return;
    }

    // 写入文件（注意：WAV文件的data块需按顺序写入，避免跳跃式定位）
    qint64 bytesWritten = m_outputFile.write(
        reinterpret_cast<const char*>(buffer.data()),
        buffer.size() * sizeof(short)
        );
    if (bytesWritten != buffer.size() * sizeof(short)) {
        qWarning() << "Failed to write to file. Bytes written: " << bytesWritten;
    }
}

// Offset  Field           Value
//     0       ChunkID         "RIFF"
//     4       ChunkSize       文件总大小-8
//     8       Format          "WAVE"
//     12      Subchunk1ID     "fmt "
//     16      Subchunk1Size   16
//     20      AudioFormat     1 (PCM)
//     22      NumChannels     2
//     24      SampleRate      44100
//     28      ByteRate        176400 (44100*2*2)
//     32      BlockAlign      4 (2ch*2bytes)
//     34      BitsPerSample   16
//     36      Subchunk2ID     "data"
//     40      Subchunk2Size   实际音频数据长度
//     44      Data            [音频数据]

void AudioRecorder::writeWavHeader() {
    QDataStream out(&m_outputFile);
    out.setByteOrder(QDataStream::LittleEndian);

    out.writeRawData("RIFF", 4);
    out << quint32(0);  // ChunkSize placeholder
    out.writeRawData("WAVE", 4);

    out.writeRawData("fmt ", 4);
    out << quint32(16); // Subchunk1Size
    out << quint16(1);  // PCM
    out << quint16(m_channels);
    out << quint32(m_sampleRate);
    quint32 byteRate = m_sampleRate * m_channels * m_bits / 8;
    quint16 blockAlign = m_channels * m_bits / 8;
    out << byteRate;
    out << blockAlign;
    out << quint16(m_bits);

    out.writeRawData("data", 4);
    out << quint32(0); // DataSize placeholder
}

// void AudioRecorder::finalizeWavHeader() {
//     if (!m_outputFile.isOpen()) return;

//     // 将指针移动到文件末尾追加数据
//     m_outputFile.seek(m_outputFile.size());
//     m_outputFile.write(m_pcmBuffer);

//     // 更新头信息（保持原有逻辑）
//     const quint32 dataSize = m_pcmBuffer.size();
//     const quint32 chunkSize = 36 + dataSize;

//     m_outputFile.seek(4);
//     QDataStream out(&m_outputFile);
//     out.setByteOrder(QDataStream::LittleEndian);
//     out << quint32(chunkSize);

//     m_outputFile.seek(40);
//     out << quint32(dataSize);

//     m_outputFile.close();
// }

// 简化 finalizeWavHeader（无需 m_pcmBuffer）
void AudioRecorder::finalizeWavHeader() {
    if (!m_outputFile.isOpen()) return;
    const quint32 dataSize = m_outputFile.size() - 44; // 数据块起始位置为 44 字节
    m_outputFile.seek(4);  // ChunkSize = dataSize + 36（头文件大小 36 字节：RIFF+WAVE+fmt +data）
    QDataStream out(&m_outputFile);
    out.setByteOrder(QDataStream::LittleEndian);
    out << quint32(dataSize + 36);
    m_outputFile.seek(40); // DataSize 位于第 40 字节
    out << quint32(dataSize);
    m_outputFile.close();
}
