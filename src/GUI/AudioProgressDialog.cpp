#include "AudioProgressDialog.h"
#include <QVBoxLayout>


AudioProgressDialog::AudioProgressDialog(QWidget *parent)
    : QDialog(parent), cancelled(false)
{
    setWindowTitle("音频处理中...");
    setModal(true);
    resize(400, 120);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    statusLabel = new QLabel("正在处理...", this);

    cancelButton = new QPushButton("取消", this);
    connect(cancelButton, &QPushButton::clicked, this, [this]() {
        cancelled = true;
        emit cancelRequested();
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(statusLabel);
    layout->addWidget(progressBar);
    layout->addWidget(cancelButton);
    qDebug()<<"ok?";
}

void AudioProgressDialog::setProgress(int percent)
{
    progressBar->setValue(percent);
}

bool AudioProgressDialog::isCancelled() const
{
    return cancelled;
}
