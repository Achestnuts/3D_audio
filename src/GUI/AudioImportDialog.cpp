#include "AudioImportDialog.h"
#include "ui_AudioImportDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

AudioImportDialog::AudioImportDialog(const QString &filePath, QWidget *parent)
    : QDialog(parent), userChoice(Cancel), ui(new Ui::AudioImportDialog) {

    ui->setupUi(this);

    setWindowTitle("导入音频");
    setModal(true);
    resize(300, 150);

    ui->pathLabel->setText(QString("检测到音频文件:\n%1").arg(filePath));



    connect(ui->importBtn, &QPushButton::clicked, this, [this]() {
        userChoice = ImportAsSource;
        accept();
    });
    connect(ui->convertBtn, &QPushButton::clicked, this, [this]() {
        userChoice = ConvertFormat;
        accept();
    });
    connect(ui->cancelBtn, &QPushButton::clicked, this, [this]() {
        userChoice = Cancel;
        reject();
    });

    qDebug()<<"dialog ok";
}

AudioImportDialog::ImportChoice AudioImportDialog::choice() const {
    return userChoice;
}
