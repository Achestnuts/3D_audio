#include "audiofileprocessor.h"
#include <QProcess>
#include <QFileInfo>
#include <QDebug>
#include <QDir>

AudioFileProcessor::AudioFileProcessor() {
#ifdef Q_OS_WIN
    ffmpegExecutable = "ffmpeg.exe";
#else
    ffmpegExecutable = "ffmpeg";
#endif
}

void AudioFileProcessor::setInputFile(const QString &inputPath) {
    inputFile = inputPath;
}

QStringList AudioFileProcessor::supportedFormats() const {
    return getCommonFormats();
}

QStringList AudioFileProcessor::getCommonFormats() const {
    return {"wav", "mp3", "ogg", "aac", "flac"};
}

bool AudioFileProcessor::isFFmpegAvailable(QString *error) const {
    QProcess process;
    process.start(ffmpegExecutable, QStringList() << "-version");
    process.waitForFinished();

    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        if (error) *error = QString::fromUtf8(process.readAllStandardError());
        return false;
    }
    return true;
}

bool AudioFileProcessor::convertAndExport(const QString &outputPath, const QString &format, QString *error) {
    if (!QFile::exists(inputFile)) {
        if (error) *error = "Input file does not exist.";
        return false;
    }

    if (!isFFmpegAvailable(error)) {
        return false;
    }

    QFileInfo outInfo(outputPath);
    QString actualOutputPath = outputPath;

    if (outInfo.suffix().toLower() != format.toLower()) {
        actualOutputPath = outInfo.absolutePath() + "/" + outInfo.completeBaseName() + "." + format;
    }

    QProcess process;
    QStringList args = { "-y", "-i", inputFile, actualOutputPath };
    process.start(ffmpegExecutable, args);
    if (!process.waitForFinished()) {
        if (error) *error = "FFmpeg 进程执行失败或超时";
        return false;
    }

    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        if (error) *error = QString::fromUtf8(process.readAllStandardError());
        return false;
    }

    qDebug() << "stdout:" << process.readAllStandardOutput();
    qDebug() << "stderr:" << process.readAllStandardError();


    return true;
}

