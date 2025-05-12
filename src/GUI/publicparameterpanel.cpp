#include "publicparameterpanel.h"
#include <audiomanager.h>
#include <roommap.h>




PublicParameterPanel::PublicParameterPanel(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::PublicParameterPanel)
{
    qDebug()<<"public prepare setup";
    ui->setupUi(this);
    // // 关闭透明背景属性
    // setAttribute(Qt::WA_TranslucentBackground, false);
    // // 设置子部件的背景样式，例如设置为不透明的白色背景
    // setStyleSheet("background-color: white;");
    qDebug()<<"public ui setup";
    setMinimumSize(0, 0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    AudioManager* audioManager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
    std::shared_ptr<RoomMap> roomMap = qvariant_cast<std::shared_ptr<RoomMap>>(qApp->property("RoomMap"));

    ui->gridMeterEdit->setText(QString::number(roomMap->audioManager->gridMeter));
    connect(ui->gridMeterEdit, &QLineEdit::editingFinished, this, [=]() {
        audioManager->gridMeter = ui->gridMeterEdit->text().toFloat();
    });

    connect(ui->startButton, &QPushButton::clicked, [=](){
        roomMap->audioManager->recorder->startRecording("E:/WorkPlace/QT/3D_audio_rebuild/3D_audio/resources/music/recorder.wav");
    });

    connect(ui->stopButton, &QPushButton::clicked, [=](){
        roomMap->audioManager->recorder->stopRecording();
    });

    connect(ui->sceneSaveButton, &QPushButton::clicked, [=]() {
        roomMap->saveSceneFile();
    });

    connect(ui->sceneLoadButton, &QPushButton::clicked, [=]() {
        roomMap->loadSceneFile();
    });

    qDebug()<<"public setup";
}


