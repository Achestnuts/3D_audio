#include "AudioImportDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

AudioImportDialog::AudioImportDialog(const QString &filePath, QWidget *parent)
    : QDialog(parent), userChoice(Cancel) {
    setWindowTitle("导入音频");
    setModal(true);
    resize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString("检测到音频文件:\n%1").arg(filePath)));

    QPushButton *importBtn = new QPushButton("导入为声源");
    QPushButton *convertBtn = new QPushButton("转换格式");
    QPushButton *cancelBtn = new QPushButton("取消");

    layout->addWidget(importBtn);
    layout->addWidget(convertBtn);
    layout->addWidget(cancelBtn);

    connect(importBtn, &QPushButton::clicked, this, [this]() {
        userChoice = ImportAsSource;
        accept();
    });
    connect(convertBtn, &QPushButton::clicked, this, [this]() {
        userChoice = ConvertFormat;
        accept();
    });
    connect(cancelBtn, &QPushButton::clicked, this, [this]() {
        userChoice = Cancel;
        reject();
    });

    qDebug()<<"dialog ok";
}

AudioImportDialog::ImportChoice AudioImportDialog::choice() const {
    return userChoice;
}
