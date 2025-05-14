#ifndef FFMPEGWORKER_H
#define FFMPEGWORKER_H

#include <QObject>
#include <QProcess>

class FFmpegWorker : public QObject
{
    Q_OBJECT
public:
    explicit FFmpegWorker(const QString &input, const QString &output, const QStringList &args, QObject *parent = nullptr);
    void start();
    void requestCancel();

signals:
    void progressUpdated(int percent);
    void finished(bool success, const QString &errorString = QString());

private slots:
    void readStandardError();

private:
    QString inputPath, outputPath;
    QStringList arguments;
    QProcess *process;
    bool cancelled;
};

#endif // FFMPEGWORKER_H
