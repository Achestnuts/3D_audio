#include "sourceparameterwidget.h"
#include "ui_sourceparameterwidget.h"

SourceParameterWidget::SourceParameterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SourceParameterWidget)
    , source(nullptr)
{
    ui->setupUi(this);
}

void SourceParameterWidget::disconnectBound()
{
    if(!source) {
        return;
    }
    disconnect();
    AudioManager* audioManager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
    if((audioManager->isSourceExist(source->sourceId))) {
        audioManager->sources[source->sourceId]->auxEffectSlots.disconnect();
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
    QMutex mutex;
    QMutexLocker locker(&mutex);
    disconnect();
    source = boundSource;

    AudioManager* audioManager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
    if(!(audioManager->isSourceExist(boundSource->sourceId))) {
        return false;
    }

    AuxEffectSlot* eSlot = &(audioManager->sources[source->sourceId]->auxEffectSlots);
    qDebug()<<"准备连接";
    auto changeParameterConnect = [this] (QLineEdit* edit, float* needChangeParameter) {
        this->connect(edit, &QLineEdit::editingFinished, [needChangeParameter, edit] () {
            *needChangeParameter = edit->text().toFloat();
        });
        edit->setText(QString::number(*needChangeParameter));
    };

    auto showSlotParameterConnect = [this, eSlot] (QLabel* label, float* showParameter){
        connect(eSlot, &AuxEffectSlot::roomSizeChange, [label, showParameter] (float newRoomSize) {
            label->setText(QString::number(*showParameter));
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
