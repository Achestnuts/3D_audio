#include "FFmpegWorker.h"
#include <QRegularExpression>
#include <QFileInfo>

FFmpegWorker::FFmpegWorker(const QString &input, const QString &output, const QStringList &args, QObject *parent)
    : QObject(parent), inputPath(input), outputPath(output), arguments(args), process(nullptr), cancelled(false) {}

void FFmpegWorker::start()
{
    process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardError, this, &FFmpegWorker::readStandardError);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this](int exitCode, QProcess::ExitStatus) {
                emit finished(exitCode == 0 && !cancelled, process->readAllStandardError());
                process->deleteLater();
            });

    QStringList fullArgs;
    fullArgs << "-y";                       // 自动覆盖已有文件
    fullArgs << "-i" << inputPath;          // 输入文件路径
    fullArgs += arguments;                  // 输出参数（如 -ar -ac 等）
    fullArgs << outputPath;                 // 输出文件路径，必须完整（如 output.wav）

    qDebug() << "Starting ffmpeg with args:" << fullArgs;

    process->start("ffmpeg", fullArgs);
}


void FFmpegWorker::requestCancel()
{
    cancelled = true;
    if (process) {
        process->kill();
    }
}

void FFmpegWorker::readStandardError()
{
    QString output = QString::fromUtf8(process->readAllStandardError());

    // time=00:01:23.45
    static QRegularExpression timeRx(R"(time=(\d{2}):(\d{2}):(\d{2})\.(\d{2}))");

    QRegularExpressionMatchIterator i = timeRx.globalMatch(output);
    int seconds = 0;

    while (i.hasNext()) {
        QRegularExpressionMatch m = i.next();
        int h = m.captured(1).toInt();
        int m_ = m.captured(2).toInt();
        int s = m.captured(3).toInt();
        int cs = m.captured(4).toInt();  // centiseconds

        seconds = h * 3600 + m_ * 60 + s;
        seconds += cs / 100.0;
    }

    // 需要准确的总时长（秒），推荐通过 FFprobe 预先读取
    int totalDuration = 369;  // 假设总长 6 分 9 秒 = 369 秒，可传入构造

    if (totalDuration > 0 && seconds > 0) {
        int percent = qMin(100, static_cast<int>(seconds * 100 / totalDuration));
        emit progressUpdated(percent);
    }
}
