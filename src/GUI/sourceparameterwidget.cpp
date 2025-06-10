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
    // setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // // 设置子部件的背景样式，例如设置为不透明的白色背景
    // setStyleSheet("background-color: white;");
    for (const auto& t : reverbTemplates)
        ui->templateComboBox->addItem(t.name);

    connect(ui->loadTemplateButton, &QPushButton::clicked, this, &SourceParameterWidget::onLoadTemplateClicked);

    qApp->setProperty("SourceParameterWidget", QVariant::fromValue(this)); // 存储指针
}

void SourceParameterWidget::reset() {
    auto changeParameter = [=] (QLineEdit* edit, float updateParameter) {
        edit->setText(QString::number(updateParameter));
    };

    // 为每个参数字段设置对应的值
    // 更新和存储每个参数值
    ui->roomSizeValue->clear();

    changeParameter(ui->decayTimeIntercept, 0);
    changeParameter(ui->decayTimeFactor, 0);
    ui->decayTimeValue->clear();

    changeParameter(ui->reflectionsDelayIntercept, 0);
    changeParameter(ui->reflectionsDelayFactor, 0);
    ui->reflectionsDelayValue->clear();

    changeParameter(ui->lateReverbDelayIntercept, 0);
    changeParameter(ui->lateReverbDelayFactor, 0);
    ui->lateReverbDelayValue->clear();

    changeParameter(ui->gainIntercept, 0);
    changeParameter(ui->gainFactor, 0);
    ui->gainValue->clear();

    changeParameter(ui->reflectionsGainIntercept, 0);
    changeParameter(ui->reflectionsGainFactor, 0);
    ui->reflectionsGainValue->clear();

    changeParameter(ui->lateReverbGainIntercept, 0);
    changeParameter(ui->lateReverbGainFactor, 0);
    ui->lateReverbGainValue->clear();

    changeParameter(ui->airAbsorptionHFIntercept, 0);
    changeParameter(ui->airAbsorptionHFFactor, 0);
    ui->airAbsorptionHFValue->clear();

    changeParameter(ui->decayHFRatioIntercept, 0);
    changeParameter(ui->decayHFRatioFactor, 0);
    ui->decayHFRatioValue->clear();

    changeParameter(ui->decayLFRatioIntercept, 0);
    changeParameter(ui->decayLFRatioFactor, 0);
    ui->decayLFRatioValue->clear();

    changeParameter(ui->diffusionIntercept, 0);
    changeParameter(ui->diffusionFactor, 0);
    ui->diffusionValue->clear();

    changeParameter(ui->densityIntercept, 0);
    changeParameter(ui->densityFactor, 0);
    ui->densityValue->clear();
}

void SourceParameterWidget::onLoadTemplateClicked() {
    // 获取当前选中的模板索引
    int index = ui->templateComboBox->currentIndex();
    if (index < 0 || index >= reverbTemplates.size()) return;

    const auto& t = reverbTemplates[index]; // 选中的模板数据

    if(!source) return;
    std::shared_ptr<AudioManager> audioManager = qvariant_cast<std::shared_ptr<AudioManager>>(qApp->property("AudioManager"));
    if(!(audioManager->isSourceExist(source->boundSource->sourceId))) {
        return;
    }

    auto changeParameter = [=] (QLineEdit* edit, float* needChangeParameter, float updateParameter) {
        audioManager->itemMutex->lockForWrite();
        *needChangeParameter = updateParameter;
        audioManager->itemMutex->unlock();
        edit->setText(QString::number(*needChangeParameter));
    };

    // 为每个参数字段设置对应的值
    // 更新和存储每个参数值
    AuxEffectSlot* eSlot = &source->boundSource->auxEffectSlots;
    changeParameter(ui->decayTimeIntercept, &eSlot->decayTimeIntercept, t.decayTimeIntercept);
    changeParameter(ui->decayTimeFactor, &eSlot->decayTimeFactor, t.decayTimeFactor);

    changeParameter(ui->reflectionsDelayIntercept, &eSlot->reflectionsDelayIntercept, t.reflectionsDelayIntercept);
    changeParameter(ui->reflectionsDelayFactor, &eSlot->reflectionsDelayFactor, t.reflectionsDelayFactor);

    changeParameter(ui->lateReverbDelayIntercept, &eSlot->lateReverbDelayIntercept, t.lateReverbDelayIntercept);
    changeParameter(ui->lateReverbDelayFactor, &eSlot->lateReverbDelayFactor, t.lateReverbDelayFactor);

    changeParameter(ui->gainIntercept, &eSlot->gainIntercept, t.gainIntercept);
    changeParameter(ui->gainFactor, &eSlot->gainFactor, t.gainFactor);

    changeParameter(ui->reflectionsGainIntercept, &eSlot->reflectionsGainIntercept, t.reflectionsGainIntercept);
    changeParameter(ui->reflectionsGainFactor, &eSlot->reflectionsGainFactor, t.reflectionsGainFactor);

    changeParameter(ui->lateReverbGainIntercept, &eSlot->lateReverbGainIntercept, t.lateReverbGainIntercept);
    changeParameter(ui->lateReverbGainFactor, &eSlot->lateReverbGainFactor, t.lateReverbGainFactor);

    changeParameter(ui->airAbsorptionHFIntercept, &eSlot->airAbsorptionHFIntercept, t.airAbsorptionHFIntercept);
    changeParameter(ui->airAbsorptionHFFactor, &eSlot->airAbsorptionHFFactor, t.airAbsorptionHFFactor);

    changeParameter(ui->decayHFRatioIntercept, &eSlot->decayHFRatioIntercept, t.decayHFRatioIntercept);
    changeParameter(ui->decayHFRatioFactor, &eSlot->decayHFRatioFactor, t.decayHFRatioFactor);

    changeParameter(ui->decayLFRatioIntercept, &eSlot->decayLFRatioIntercept, t.decayLFRatioIntercept);
    changeParameter(ui->decayLFRatioFactor, &eSlot->decayLFRatioFactor, t.decayLFRatioFactor);

    changeParameter(ui->diffusionIntercept, &eSlot->diffusionIntercept, t.diffusionIntercept);
    changeParameter(ui->diffusionFactor, &eSlot->diffusionFactor, t.diffusionFactor);

    changeParameter(ui->densityIntercept, &eSlot->densityIntercept, t.densityIntercept);
    changeParameter(ui->densityFactor, &eSlot->densityFactor, t.densityFactor);

    audioManager->updateEffectSlots();
}



QSize SourceParameterWidget::sizeHint() const {
    return QSize(0, 0); // 控制在合理范围内
}


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
    ui->nameEdit->clear();

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
    disconnectBound();
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
            label->setText(QString::number(*showParameter) + QString(""));
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
