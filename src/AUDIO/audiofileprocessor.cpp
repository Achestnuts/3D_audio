#include "audiofileprocessor.h"
#include <QProcess>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <QCoreApplication>
#include <FFmpegWorker.h>
#include <AudioProgressDialog.h>
#include <QThread>

AudioFileProcessor::AudioFileProcessor(QObject *parent) : QObject(parent) {
#ifdef Q_OS_WIN
    ffmpegExecutable = "ffmpeg.exe";
#else
    ffmpegExecutable = "ffmpeg";
#endif
}

// void AudioFileProcessor::setInputFile(const QString &inputPath) {
//     inputFile = inputPath;
// }

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

bool AudioFileProcessor::convertAndExport(const QString &inputPath, const QString &outputPath, const QString &format)
{
    // 构造 format-specific 参数
    QStringList ffmpegArgs;

    if (format == "wav") {
        ffmpegArgs << "-vn" << "-ar" << "48000" << "-ac" << "2" << "-sample_fmt" << "s16";
    } else if (format == "mp3") {
        ffmpegArgs << "-vn" << "-ar" << "48000" << "-ac" << "2" << "-b:a" << "192k";
    } else if (format == "ogg") {
        ffmpegArgs << "-vn" << "-c:a" << "libvorbis" << "-qscale:a" << "5";
    } else if (format == "aac" || format == "m4a") {
        ffmpegArgs << "-vn" << "-c:a" << "aac" << "-b:a" << "192k";
    } else if (format == "flac") {
        ffmpegArgs << "-vn" << "-c:a" << "flac" << "-ar" << "48000" << "-ac" << "2";
    } else {
        qWarning() << "Unsupported format:" << format;
        return false;
    }


    // 构造进度对话框和工作线程
    auto dialog = new AudioProgressDialog;
    auto worker = new FFmpegWorker(inputPath, outputPath, ffmpegArgs);

    connect(worker, &FFmpegWorker::progressUpdated, dialog, &AudioProgressDialog::setProgress);
    connect(dialog, &AudioProgressDialog::cancelRequested, worker, &FFmpegWorker::requestCancel);

    QThread *thread = new QThread;
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &FFmpegWorker::start);
    connect(worker, &FFmpegWorker::finished, dialog, [dialog](bool success, const QString &log) {
        if (!success) {
            qWarning() << "FFmpeg failed with log:\n" << log;
        }
        dialog->accept();
    });

    connect(worker, &FFmpegWorker::finished, thread, &QThread::quit);
    connect(worker, &FFmpegWorker::finished, worker, &FFmpegWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
    dialog->exec();  // 会阻塞，直到 accept()/reject()

    bool cancelled = dialog->isCancelled();
    dialog->deleteLater();
    return !cancelled;
}




// bool AudioFileProcessor::convertAndExport(const QString &outputPath, const QString &format, QString *error, std::function<bool(int)> progressCallback, std::atomic_bool *cancelFlag)
// {
//     if (!QFile::exists(inputFile)) {
//         if (error) *error = "Input file does not exist.";
//         return false;
//     }

//     if (!isFFmpegAvailable(error)) {
//         return false;
//     }

//     QFileInfo outInfo(outputPath);
//     QString actualOutputPath = outputPath;

//     if (outInfo.suffix().toLower() != format.toLower()) {
//         actualOutputPath = outInfo.absolutePath() + "/" + outInfo.completeBaseName() + "." + format;
//     }

//     QProcess process;
//     QStringList args = {
//         "-y", "-i", inputFile,
//         "-progress", "pipe:1", // 输出进度到 stdout
//         "-nostats",
//         actualOutputPath
//     };

//     process.setProcessChannelMode(QProcess::MergedChannels);
//     process.start(ffmpegExecutable, args);

//     if (!process.waitForStarted()) {
//         if (error) *error = "FFmpeg 启动失败";
//         return false;
//     }

//     int progress = 0;
//     qint64 durationMs = 0;

//     // 获取音频总时长（用 ffprobe）
//     {
//         QProcess probe;
//         probe.start(ffmpegExecutable, {"-i", inputFile});
//         probe.waitForFinished();

//         QString errOutput = probe.readAllStandardError();
//         QRegularExpression re("Duration: (\\d+):(\\d+):(\\d+\\.\\d+)");
//         QRegularExpressionMatch match = re.match(errOutput);
//         if (match.hasMatch()) {
//             int h = match.captured(1).toInt();
//             int m = match.captured(2).toInt();
//             double s = match.captured(3).toDouble();
//             durationMs = static_cast<qint64>((h * 3600 + m * 60 + s) * 1000);
//         }
//     }

//     while (process.state() == QProcess::Running) {
//         if (cancelFlag && cancelFlag->load()) {
//             process.kill();
//             if (error) *error = "用户取消了转换操作";
//             return false;
//         }

//         while (process.canReadLine()) {
//             QByteArray line = process.readLine();
//             QString text(line.trimmed());
//             if (text.startsWith("out_time_ms=")) {
//                 bool ok = false;
//                 qint64 currentMs = text.mid(QString("out_time_ms=").length()).toLongLong(&ok);
//                 if (ok && durationMs > 0) {
//                     progress = static_cast<int>((currentMs * 100) / durationMs);
//                     if (progressCallback) progressCallback(qMin(progress, 100));
//                 }
//             }
//         }

//         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//     }

//     if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
//         if (error) *error = QString::fromUtf8(process.readAllStandardError());
//         return false;
//     }

//     if (progressCallback) progressCallback(100); // 最后一次确保满进度
//     return true;
// }

