#ifndef AUDIOFILEPROCESSOR_H
#define AUDIOFILEPROCESSOR_H

#pragma once

#include <QString>
#include <QStringList>

class AudioFileProcessor {
public:
    AudioFileProcessor();

    // 设置输入音频文件路径
    void setInputFile(const QString &inputPath);

    // 转换并导出音频文件，指定输出路径和目标格式（如 "mp3", "ogg"）
    bool convertAndExport(const QString &outputPath, const QString &format, QString *error = nullptr);

    // 获取支持的音频格式列表
    QStringList supportedFormats() const;

    // 检查 FFmpeg 是否可用
    bool isFFmpegAvailable(QString *error = nullptr) const;

    // bool saveRecording(const QString &filePath, const QString &format);

private:
    QString inputFile;

    QString ffmpegExecutable;

    QStringList getCommonFormats() const;
};


#endif // AUDIOFILEPROCESSOR_H
