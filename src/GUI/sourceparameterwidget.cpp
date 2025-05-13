#include "sourceparameterwidget.h"
#include "ui_sourceparameterwidget.h"

#include <audiomanager.h>

SourceParameterWidget::SourceParameterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SourceParameterWidget)
    , source(nullptr)
{

    ui->setupUi(this);
    // 关闭透明背景属性
    setAttribute(Qt::WA_TranslucentBackground, false);
    setMinimumSize(0, 0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // // 设置子部件的背景样式，例如设置为不透明的白色背景
    // setStyleSheet("background-color: white;");
}

// QSize SourceParameterWidget::sizeHint() const {
//     return QSize(0, 0); // 控制在合理范围内
// }


void SourceParameterWidget::disconnectBound()
{
    if(!source) {
        return;
    }
    disconnect();
    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    if((audioManager->isSourceExist(source->boundSource->sourceId))) {
        audioManager->sources[source->boundSource->sourceId]->boundSource->auxEffectSlots.disconnect();
    }

    ui->nameEdit->disconnect();

    ui->decayTimeIntercept->disconnect();
    ui->decayTimeFactor->disconnect();
    ui->decayTimeValue->disconnect();

    ui->reflectionsDelayIntercept->disconnect();
    ui->reflectionsDelayFactor->disconnect();
    ui->reflectionsDelayValue->disconnect();

    ui->lateReverbDelayIntercept->disconnect();
    ui->lateReverbDelayFactor->disconnect();
    ui->lateReverbDelayValue->disconnect();

    ui->gainIntercept->disconnect();
    ui->gainFactor->disconnect();
    ui->gainValue->disconnect();

    ui->reflectionsGainIntercept->disconnect();
    ui->reflectionsGainFactor->disconnect();
    ui->reflectionsGainValue->disconnect();

    ui->lateReverbGainIntercept->disconnect();
    ui->lateReverbGainFactor->disconnect();
    ui->lateReverbGainValue->disconnect();

    ui->airAbsorptionHFIntercept->disconnect();
    ui->airAbsorptionHFFactor->disconnect();
    ui->airAbsorptionHFValue->disconnect();

    ui->decayHFRatioIntercept->disconnect();
    ui->decayHFRatioFactor->disconnect();
    ui->decayHFRatioValue->disconnect();

    ui->decayLFRatioIntercept->disconnect();
    ui->decayLFRatioFactor->disconnect();
    ui->decayLFRatioValue->disconnect();

    ui->diffusionIntercept->disconnect();
    ui->diffusionFactor->disconnect();
    ui->diffusionValue->disconnect();

    ui->densityIntercept->disconnect();
    ui->densityFactor->disconnect();
    ui->densityValue->disconnect();

    source = nullptr;
    qDebug()<<"断开连接";
}

bool SourceParameterWidget::boundSource(DraggableSource *boundSource)
{
    disconnect();
    source = boundSource;

    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    if(!(audioManager->isSourceExist(boundSource->boundSource->sourceId))) {
        return false;
    }

    AuxEffectSlot* eSlot = &(audioManager->sources[source->boundSource->sourceId]->boundSource->auxEffectSlots);
    qDebug()<<"准备连接";
    auto changeParameterConnect = [=] (QLineEdit* edit, float* needChangeParameter) {
        this->connect(edit, &QLineEdit::editingFinished, [=] () {
            // qDebug()<<"pre change";
            audioManager->itemMutex->lockForWrite();
            *needChangeParameter = edit->text().toFloat();
            audioManager->itemMutex->unlock();
            audioManager->updateEffectSlots();
            // qDebug()<<"change ok";
        });
        edit->setText(QString::number(*needChangeParameter));
    };

    auto showSlotParameterConnect = [=] (QLabel* label, float* showParameter){
        connect(eSlot, &AuxEffectSlot::roomSizeChange, [=] (float newRoomSize) {
            // qDebug()<<"pre show";
            audioManager->itemMutex->lockForRead();
            label->setText(QString::number(*showParameter));
            audioManager->itemMutex->unlock();
            // qDebug()<<"show ok";
        } );
        label->setText(QString::number(*showParameter));
    };

    showSlotParameterConnect(ui->roomSizeValue, &(eSlot->roomSize));

    connect(ui->nameEdit, &QLineEdit::editingFinished, [this]() {
        this->source->sourceName = this->ui->nameEdit->text();
    });
    ui->nameEdit->setText(source->sourceName);
    qDebug()<<"连接完成";

    changeParameterConnect(ui->decayTimeIntercept, &(eSlot->decayTimeIntercept));
    changeParameterConnect(ui->decayTimeFactor, &(eSlot->decayTimeFactor));
    showSlotParameterConnect(ui->decayTimeValue, &(eSlot->decayTime));

    changeParameterConnect(ui->reflectionsDelayIntercept, &(eSlot->reflectionsDelayIntercept));
    changeParameterConnect(ui->reflectionsDelayFactor, &(eSlot->reflectionsDelayFactor));
    showSlotParameterConnect(ui->reflectionsDelayValue, &(eSlot->reflectionsDelay));

    changeParameterConnect(ui->lateReverbDelayIntercept, &(eSlot->lateReverbDelayIntercept));
    changeParameterConnect(ui->lateReverbDelayFactor, &(eSlot->lateReverbDelayFactor));
    showSlotParameterConnect(ui->lateReverbDelayValue, &(eSlot->lateReverbDelay));

    changeParameterConnect(ui->gainIntercept, &(eSlot->gainIntercept));
    changeParameterConnect(ui->gainFactor, &(eSlot->gainFactor));
    showSlotParameterConnect(ui->gainValue, &(eSlot->gain));

    changeParameterConnect(ui->reflectionsGainIntercept, &(eSlot->reflectionsGainIntercept));
    changeParameterConnect(ui->reflectionsGainFactor, &(eSlot->reflectionsGainFactor));
    showSlotParameterConnect(ui->reflectionsGainValue, &(eSlot->reflectionsGain));


    changeParameterConnect(ui->lateReverbGainIntercept, &(eSlot->lateReverbGainIntercept));
    changeParameterConnect(ui->lateReverbGainFactor, &(eSlot->lateReverbGainFactor));
    showSlotParameterConnect(ui->lateReverbGainValue, &(eSlot->lateReverbGain));

    changeParameterConnect(ui->airAbsorptionHFIntercept, &(eSlot->airAbsorptionHFIntercept));
    changeParameterConnect(ui->airAbsorptionHFFactor, &(eSlot->airAbsorptionHFFactor));
    showSlotParameterConnect(ui->airAbsorptionHFValue, &(eSlot->airAbsorptionHF));

    changeParameterConnect(ui->decayHFRatioIntercept, &(eSlot->decayHFRatioIntercept));
    changeParameterConnect(ui->decayHFRatioFactor, &(eSlot->decayHFRatioFactor));
    showSlotParameterConnect(ui->decayHFRatioValue, &(eSlot->decayHFRatio));

    changeParameterConnect(ui->decayLFRatioIntercept, &(eSlot->decayLFRatioIntercept));
    changeParameterConnect(ui->decayLFRatioFactor, &(eSlot->decayLFRatioFactor));
    showSlotParameterConnect(ui->decayLFRatioValue, &(eSlot->decayLFRatio));

    changeParameterConnect(ui->diffusionIntercept, &(eSlot->diffusionFactor));
    changeParameterConnect(ui->diffusionFactor, &(eSlot->diffusionFactor));
    showSlotParameterConnect(ui->diffusionValue, &(eSlot->diffusion));

    changeParameterConnect(ui->densityIntercept, &(eSlot->densityIntercept));
    changeParameterConnect(ui->densityFactor, &(eSlot->densityFactor));
    showSlotParameterConnect(ui->densityValue, &(eSlot->density));

    return true;
}
