/********************************************************************************
** Form generated from reading UI file 'sourceparameterwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOURCEPARAMETERWIDGET_H
#define UI_SOURCEPARAMETERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SourceParameterWidget
{
public:
    QVBoxLayout *SourceParameterWidgetLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *nameWidget;
    QGridLayout *gridLayout_4;
    QLineEdit *nameEdit;
    QLabel *nameLabel;
    QWidget *roomSizeWidget;
    QGridLayout *gridLayout_3;
    QLabel *roomSizeLabel;
    QLabel *roomSizeValue;
    QWidget *decayTimeWidget;
    QGridLayout *decayTimeWidgetLayout;
    QLabel *decayTimeMultiplacation;
    QLabel *decayTimeLabel;
    QLabel *decayTimeRoomSize;
    QLabel *decayTimePlus;
    QLineEdit *decayTimeIntercept;
    QLineEdit *decayTimeFactor;
    QLabel *decayTimeValue;
    QWidget *reflectionsDelayWidget;
    QGridLayout *reflectionDelayWidgetLayout;
    QLineEdit *reflectionsDelayFactor;
    QLabel *reflectionsDelayRoomSize;
    QLineEdit *reflectionsDelayIntercept;
    QLabel *reflectionsDelayPlus;
    QLabel *reflectionsDelayMultiplacation;
    QLabel *reflectionsDelayLabel;
    QLabel *reflectionsDelayValue;
    QWidget *lateReverbDelayWidget;
    QGridLayout *lateReverbDelayWidgetLayout;
    QLabel *lateReverbDelayRoomSize;
    QLineEdit *lateReverbDelayFactor;
    QLabel *lateReverbDelayMultiplacation;
    QLabel *lateReverbDelayLabel;
    QLabel *lateReverbDelayPlus;
    QLineEdit *lateReverbDelayIntercept;
    QLabel *lateReverbDelayValue;
    QWidget *gainWidget;
    QGridLayout *gainWidgetLayout;
    QLabel *gainPlus;
    QLineEdit *gainIntercept;
    QLabel *gainMultiplacation;
    QLineEdit *gainFactor;
    QLabel *gainLabel;
    QLabel *gainRoomSize;
    QLabel *gainValue;
    QWidget *reflectionsGainWidget;
    QGridLayout *reflectionsGainWidgetLayout;
    QLineEdit *reflectionsGainFactor;
    QLabel *reflectionsGainRoomSize;
    QLabel *reflectionsGainLabel;
    QLabel *reflectionsGainPlus;
    QLabel *reflectionsGainMultiplacation;
    QLineEdit *reflectionsGainIntercept;
    QLabel *reflectionsGainValue;
    QWidget *lateReverbGainWidget;
    QGridLayout *lateReverbGainLayout;
    QLineEdit *lateReverbGainIntercept;
    QLabel *lateReverbGainLabel;
    QLineEdit *lateReverbGainFactor;
    QLabel *lateReverbGainRoomSize;
    QLabel *lateReverbGainMultiplacation;
    QLabel *lateReverbGainPlus;
    QLabel *lateReverbGainValue;
    QWidget *airAbsorptionHFWidget;
    QGridLayout *airAbsorptionHFLayout;
    QLineEdit *airAbsorptionHFIntercept;
    QLabel *airAbsorptionHFRoomSize;
    QLabel *airAbsorptionHFLabel;
    QLabel *airAbsorptionHFMultiplacation;
    QLineEdit *airAbsorptionHFFactor;
    QLabel *airAbsorptionHFPlus;
    QLabel *airAbsorptionHFValue;
    QWidget *decayHFRatioWidget;
    QGridLayout *decayHFRatioWidgetLayout;
    QLabel *decayHFRatioLabel;
    QLabel *decayHFRatioMultiplacation;
    QLineEdit *decayHFRatioIntercept;
    QLabel *decayHFRatioPlus;
    QLineEdit *decayHFRatioFactor;
    QLabel *decayHFRatioRoomSize;
    QLabel *decayHFRatioValue;
    QWidget *decayLFRatioWidget;
    QGridLayout *decayLFRatioLayout;
    QLabel *decayLFRatioMultiplacation;
    QLabel *decayLFRatioLabel;
    QLineEdit *decayLFRatioFactor;
    QLabel *decayLFRatioRoomSize;
    QLineEdit *decayLFRatioIntercept;
    QLabel *decayLFRatioPlus;
    QLabel *decayLFRatioValue;
    QWidget *diffusionWidget;
    QGridLayout *diffussionLayout;
    QLabel *diffusionMultiplacation;
    QLabel *diffusionValue;
    QLabel *diffusionLabel;
    QLabel *diffusionRoomSize;
    QLineEdit *diffusionFactor;
    QLabel *diffusionPlus;
    QLineEdit *diffusionIntercept;
    QWidget *densityWidget;
    QGridLayout *densityLayout;
    QLabel *densityMultiplacation;
    QLabel *densityPlus;
    QLabel *densityRoomSize;
    QLabel *densityLabel;
    QLineEdit *densityFactor;
    QLineEdit *densityIntercept;
    QLabel *densityValue;

    void setupUi(QWidget *SourceParameterWidget)
    {
        if (SourceParameterWidget->objectName().isEmpty())
            SourceParameterWidget->setObjectName("SourceParameterWidget");
        SourceParameterWidget->resize(434, 712);
        SourceParameterWidgetLayout = new QVBoxLayout(SourceParameterWidget);
        SourceParameterWidgetLayout->setSpacing(0);
        SourceParameterWidgetLayout->setObjectName("SourceParameterWidgetLayout");
        SourceParameterWidgetLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(SourceParameterWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(-50, -18, 465, 711));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        nameWidget = new QWidget(scrollAreaWidgetContents);
        nameWidget->setObjectName("nameWidget");
        gridLayout_4 = new QGridLayout(nameWidget);
        gridLayout_4->setObjectName("gridLayout_4");
        nameEdit = new QLineEdit(nameWidget);
        nameEdit->setObjectName("nameEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nameEdit->sizePolicy().hasHeightForWidth());
        nameEdit->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(nameEdit, 1, 1, 1, 1);

        nameLabel = new QLabel(nameWidget);
        nameLabel->setObjectName("nameLabel");

        gridLayout_4->addWidget(nameLabel, 1, 0, 1, 1);


        verticalLayout->addWidget(nameWidget);

        roomSizeWidget = new QWidget(scrollAreaWidgetContents);
        roomSizeWidget->setObjectName("roomSizeWidget");
        gridLayout_3 = new QGridLayout(roomSizeWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        roomSizeLabel = new QLabel(roomSizeWidget);
        roomSizeLabel->setObjectName("roomSizeLabel");

        gridLayout_3->addWidget(roomSizeLabel, 1, 0, 1, 1);

        roomSizeValue = new QLabel(roomSizeWidget);
        roomSizeValue->setObjectName("roomSizeValue");

        gridLayout_3->addWidget(roomSizeValue, 1, 1, 1, 1);


        verticalLayout->addWidget(roomSizeWidget);

        decayTimeWidget = new QWidget(scrollAreaWidgetContents);
        decayTimeWidget->setObjectName("decayTimeWidget");
        decayTimeWidgetLayout = new QGridLayout(decayTimeWidget);
        decayTimeWidgetLayout->setObjectName("decayTimeWidgetLayout");
        decayTimeMultiplacation = new QLabel(decayTimeWidget);
        decayTimeMultiplacation->setObjectName("decayTimeMultiplacation");

        decayTimeWidgetLayout->addWidget(decayTimeMultiplacation, 1, 6, 1, 1);

        decayTimeLabel = new QLabel(decayTimeWidget);
        decayTimeLabel->setObjectName("decayTimeLabel");

        decayTimeWidgetLayout->addWidget(decayTimeLabel, 1, 0, 1, 1);

        decayTimeRoomSize = new QLabel(decayTimeWidget);
        decayTimeRoomSize->setObjectName("decayTimeRoomSize");

        decayTimeWidgetLayout->addWidget(decayTimeRoomSize, 1, 7, 1, 1);

        decayTimePlus = new QLabel(decayTimeWidget);
        decayTimePlus->setObjectName("decayTimePlus");

        decayTimeWidgetLayout->addWidget(decayTimePlus, 1, 4, 1, 1);

        decayTimeIntercept = new QLineEdit(decayTimeWidget);
        decayTimeIntercept->setObjectName("decayTimeIntercept");
        sizePolicy.setHeightForWidth(decayTimeIntercept->sizePolicy().hasHeightForWidth());
        decayTimeIntercept->setSizePolicy(sizePolicy);

        decayTimeWidgetLayout->addWidget(decayTimeIntercept, 1, 2, 1, 1);

        decayTimeFactor = new QLineEdit(decayTimeWidget);
        decayTimeFactor->setObjectName("decayTimeFactor");
        sizePolicy.setHeightForWidth(decayTimeFactor->sizePolicy().hasHeightForWidth());
        decayTimeFactor->setSizePolicy(sizePolicy);

        decayTimeWidgetLayout->addWidget(decayTimeFactor, 1, 5, 1, 1);

        decayTimeValue = new QLabel(decayTimeWidget);
        decayTimeValue->setObjectName("decayTimeValue");

        decayTimeWidgetLayout->addWidget(decayTimeValue, 1, 1, 1, 1);


        verticalLayout->addWidget(decayTimeWidget);

        reflectionsDelayWidget = new QWidget(scrollAreaWidgetContents);
        reflectionsDelayWidget->setObjectName("reflectionsDelayWidget");
        reflectionDelayWidgetLayout = new QGridLayout(reflectionsDelayWidget);
        reflectionDelayWidgetLayout->setObjectName("reflectionDelayWidgetLayout");
        reflectionsDelayFactor = new QLineEdit(reflectionsDelayWidget);
        reflectionsDelayFactor->setObjectName("reflectionsDelayFactor");
        sizePolicy.setHeightForWidth(reflectionsDelayFactor->sizePolicy().hasHeightForWidth());
        reflectionsDelayFactor->setSizePolicy(sizePolicy);

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayFactor, 1, 5, 1, 1);

        reflectionsDelayRoomSize = new QLabel(reflectionsDelayWidget);
        reflectionsDelayRoomSize->setObjectName("reflectionsDelayRoomSize");

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayRoomSize, 1, 7, 1, 1);

        reflectionsDelayIntercept = new QLineEdit(reflectionsDelayWidget);
        reflectionsDelayIntercept->setObjectName("reflectionsDelayIntercept");
        sizePolicy.setHeightForWidth(reflectionsDelayIntercept->sizePolicy().hasHeightForWidth());
        reflectionsDelayIntercept->setSizePolicy(sizePolicy);

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayIntercept, 1, 2, 1, 1);

        reflectionsDelayPlus = new QLabel(reflectionsDelayWidget);
        reflectionsDelayPlus->setObjectName("reflectionsDelayPlus");

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayPlus, 1, 4, 1, 1);

        reflectionsDelayMultiplacation = new QLabel(reflectionsDelayWidget);
        reflectionsDelayMultiplacation->setObjectName("reflectionsDelayMultiplacation");

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayMultiplacation, 1, 6, 1, 1);

        reflectionsDelayLabel = new QLabel(reflectionsDelayWidget);
        reflectionsDelayLabel->setObjectName("reflectionsDelayLabel");

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayLabel, 1, 0, 1, 1);

        reflectionsDelayValue = new QLabel(reflectionsDelayWidget);
        reflectionsDelayValue->setObjectName("reflectionsDelayValue");

        reflectionDelayWidgetLayout->addWidget(reflectionsDelayValue, 1, 1, 1, 1);


        verticalLayout->addWidget(reflectionsDelayWidget);

        lateReverbDelayWidget = new QWidget(scrollAreaWidgetContents);
        lateReverbDelayWidget->setObjectName("lateReverbDelayWidget");
        lateReverbDelayWidgetLayout = new QGridLayout(lateReverbDelayWidget);
        lateReverbDelayWidgetLayout->setObjectName("lateReverbDelayWidgetLayout");
        lateReverbDelayRoomSize = new QLabel(lateReverbDelayWidget);
        lateReverbDelayRoomSize->setObjectName("lateReverbDelayRoomSize");

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayRoomSize, 1, 7, 1, 1);

        lateReverbDelayFactor = new QLineEdit(lateReverbDelayWidget);
        lateReverbDelayFactor->setObjectName("lateReverbDelayFactor");
        sizePolicy.setHeightForWidth(lateReverbDelayFactor->sizePolicy().hasHeightForWidth());
        lateReverbDelayFactor->setSizePolicy(sizePolicy);

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayFactor, 1, 5, 1, 1);

        lateReverbDelayMultiplacation = new QLabel(lateReverbDelayWidget);
        lateReverbDelayMultiplacation->setObjectName("lateReverbDelayMultiplacation");

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayMultiplacation, 1, 6, 1, 1);

        lateReverbDelayLabel = new QLabel(lateReverbDelayWidget);
        lateReverbDelayLabel->setObjectName("lateReverbDelayLabel");

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayLabel, 1, 0, 1, 1);

        lateReverbDelayPlus = new QLabel(lateReverbDelayWidget);
        lateReverbDelayPlus->setObjectName("lateReverbDelayPlus");

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayPlus, 1, 4, 1, 1);

        lateReverbDelayIntercept = new QLineEdit(lateReverbDelayWidget);
        lateReverbDelayIntercept->setObjectName("lateReverbDelayIntercept");
        sizePolicy.setHeightForWidth(lateReverbDelayIntercept->sizePolicy().hasHeightForWidth());
        lateReverbDelayIntercept->setSizePolicy(sizePolicy);

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayIntercept, 1, 2, 1, 1);

        lateReverbDelayValue = new QLabel(lateReverbDelayWidget);
        lateReverbDelayValue->setObjectName("lateReverbDelayValue");

        lateReverbDelayWidgetLayout->addWidget(lateReverbDelayValue, 1, 1, 1, 1);


        verticalLayout->addWidget(lateReverbDelayWidget);

        gainWidget = new QWidget(scrollAreaWidgetContents);
        gainWidget->setObjectName("gainWidget");
        gainWidgetLayout = new QGridLayout(gainWidget);
        gainWidgetLayout->setObjectName("gainWidgetLayout");
        gainPlus = new QLabel(gainWidget);
        gainPlus->setObjectName("gainPlus");

        gainWidgetLayout->addWidget(gainPlus, 1, 4, 1, 1);

        gainIntercept = new QLineEdit(gainWidget);
        gainIntercept->setObjectName("gainIntercept");
        sizePolicy.setHeightForWidth(gainIntercept->sizePolicy().hasHeightForWidth());
        gainIntercept->setSizePolicy(sizePolicy);

        gainWidgetLayout->addWidget(gainIntercept, 1, 2, 1, 1);

        gainMultiplacation = new QLabel(gainWidget);
        gainMultiplacation->setObjectName("gainMultiplacation");

        gainWidgetLayout->addWidget(gainMultiplacation, 1, 6, 1, 1);

        gainFactor = new QLineEdit(gainWidget);
        gainFactor->setObjectName("gainFactor");
        sizePolicy.setHeightForWidth(gainFactor->sizePolicy().hasHeightForWidth());
        gainFactor->setSizePolicy(sizePolicy);

        gainWidgetLayout->addWidget(gainFactor, 1, 5, 1, 1);

        gainLabel = new QLabel(gainWidget);
        gainLabel->setObjectName("gainLabel");

        gainWidgetLayout->addWidget(gainLabel, 1, 0, 1, 1);

        gainRoomSize = new QLabel(gainWidget);
        gainRoomSize->setObjectName("gainRoomSize");

        gainWidgetLayout->addWidget(gainRoomSize, 1, 7, 1, 1);

        gainValue = new QLabel(gainWidget);
        gainValue->setObjectName("gainValue");

        gainWidgetLayout->addWidget(gainValue, 1, 1, 1, 1);


        verticalLayout->addWidget(gainWidget);

        reflectionsGainWidget = new QWidget(scrollAreaWidgetContents);
        reflectionsGainWidget->setObjectName("reflectionsGainWidget");
        reflectionsGainWidgetLayout = new QGridLayout(reflectionsGainWidget);
        reflectionsGainWidgetLayout->setObjectName("reflectionsGainWidgetLayout");
        reflectionsGainFactor = new QLineEdit(reflectionsGainWidget);
        reflectionsGainFactor->setObjectName("reflectionsGainFactor");
        sizePolicy.setHeightForWidth(reflectionsGainFactor->sizePolicy().hasHeightForWidth());
        reflectionsGainFactor->setSizePolicy(sizePolicy);

        reflectionsGainWidgetLayout->addWidget(reflectionsGainFactor, 1, 5, 1, 1);

        reflectionsGainRoomSize = new QLabel(reflectionsGainWidget);
        reflectionsGainRoomSize->setObjectName("reflectionsGainRoomSize");

        reflectionsGainWidgetLayout->addWidget(reflectionsGainRoomSize, 1, 7, 1, 1);

        reflectionsGainLabel = new QLabel(reflectionsGainWidget);
        reflectionsGainLabel->setObjectName("reflectionsGainLabel");

        reflectionsGainWidgetLayout->addWidget(reflectionsGainLabel, 1, 0, 1, 1);

        reflectionsGainPlus = new QLabel(reflectionsGainWidget);
        reflectionsGainPlus->setObjectName("reflectionsGainPlus");

        reflectionsGainWidgetLayout->addWidget(reflectionsGainPlus, 1, 4, 1, 1);

        reflectionsGainMultiplacation = new QLabel(reflectionsGainWidget);
        reflectionsGainMultiplacation->setObjectName("reflectionsGainMultiplacation");

        reflectionsGainWidgetLayout->addWidget(reflectionsGainMultiplacation, 1, 6, 1, 1);

        reflectionsGainIntercept = new QLineEdit(reflectionsGainWidget);
        reflectionsGainIntercept->setObjectName("reflectionsGainIntercept");
        sizePolicy.setHeightForWidth(reflectionsGainIntercept->sizePolicy().hasHeightForWidth());
        reflectionsGainIntercept->setSizePolicy(sizePolicy);

        reflectionsGainWidgetLayout->addWidget(reflectionsGainIntercept, 1, 2, 1, 1);

        reflectionsGainValue = new QLabel(reflectionsGainWidget);
        reflectionsGainValue->setObjectName("reflectionsGainValue");

        reflectionsGainWidgetLayout->addWidget(reflectionsGainValue, 1, 1, 1, 1);


        verticalLayout->addWidget(reflectionsGainWidget);

        lateReverbGainWidget = new QWidget(scrollAreaWidgetContents);
        lateReverbGainWidget->setObjectName("lateReverbGainWidget");
        lateReverbGainLayout = new QGridLayout(lateReverbGainWidget);
        lateReverbGainLayout->setObjectName("lateReverbGainLayout");
        lateReverbGainIntercept = new QLineEdit(lateReverbGainWidget);
        lateReverbGainIntercept->setObjectName("lateReverbGainIntercept");
        sizePolicy.setHeightForWidth(lateReverbGainIntercept->sizePolicy().hasHeightForWidth());
        lateReverbGainIntercept->setSizePolicy(sizePolicy);

        lateReverbGainLayout->addWidget(lateReverbGainIntercept, 1, 2, 1, 1);

        lateReverbGainLabel = new QLabel(lateReverbGainWidget);
        lateReverbGainLabel->setObjectName("lateReverbGainLabel");

        lateReverbGainLayout->addWidget(lateReverbGainLabel, 1, 0, 1, 1);

        lateReverbGainFactor = new QLineEdit(lateReverbGainWidget);
        lateReverbGainFactor->setObjectName("lateReverbGainFactor");
        sizePolicy.setHeightForWidth(lateReverbGainFactor->sizePolicy().hasHeightForWidth());
        lateReverbGainFactor->setSizePolicy(sizePolicy);

        lateReverbGainLayout->addWidget(lateReverbGainFactor, 1, 5, 1, 1);

        lateReverbGainRoomSize = new QLabel(lateReverbGainWidget);
        lateReverbGainRoomSize->setObjectName("lateReverbGainRoomSize");

        lateReverbGainLayout->addWidget(lateReverbGainRoomSize, 1, 7, 1, 1);

        lateReverbGainMultiplacation = new QLabel(lateReverbGainWidget);
        lateReverbGainMultiplacation->setObjectName("lateReverbGainMultiplacation");

        lateReverbGainLayout->addWidget(lateReverbGainMultiplacation, 1, 6, 1, 1);

        lateReverbGainPlus = new QLabel(lateReverbGainWidget);
        lateReverbGainPlus->setObjectName("lateReverbGainPlus");

        lateReverbGainLayout->addWidget(lateReverbGainPlus, 1, 4, 1, 1);

        lateReverbGainValue = new QLabel(lateReverbGainWidget);
        lateReverbGainValue->setObjectName("lateReverbGainValue");

        lateReverbGainLayout->addWidget(lateReverbGainValue, 1, 1, 1, 1);


        verticalLayout->addWidget(lateReverbGainWidget);

        airAbsorptionHFWidget = new QWidget(scrollAreaWidgetContents);
        airAbsorptionHFWidget->setObjectName("airAbsorptionHFWidget");
        airAbsorptionHFLayout = new QGridLayout(airAbsorptionHFWidget);
        airAbsorptionHFLayout->setObjectName("airAbsorptionHFLayout");
        airAbsorptionHFIntercept = new QLineEdit(airAbsorptionHFWidget);
        airAbsorptionHFIntercept->setObjectName("airAbsorptionHFIntercept");
        sizePolicy.setHeightForWidth(airAbsorptionHFIntercept->sizePolicy().hasHeightForWidth());
        airAbsorptionHFIntercept->setSizePolicy(sizePolicy);

        airAbsorptionHFLayout->addWidget(airAbsorptionHFIntercept, 1, 2, 1, 1);

        airAbsorptionHFRoomSize = new QLabel(airAbsorptionHFWidget);
        airAbsorptionHFRoomSize->setObjectName("airAbsorptionHFRoomSize");

        airAbsorptionHFLayout->addWidget(airAbsorptionHFRoomSize, 1, 7, 1, 1);

        airAbsorptionHFLabel = new QLabel(airAbsorptionHFWidget);
        airAbsorptionHFLabel->setObjectName("airAbsorptionHFLabel");

        airAbsorptionHFLayout->addWidget(airAbsorptionHFLabel, 1, 0, 1, 1);

        airAbsorptionHFMultiplacation = new QLabel(airAbsorptionHFWidget);
        airAbsorptionHFMultiplacation->setObjectName("airAbsorptionHFMultiplacation");

        airAbsorptionHFLayout->addWidget(airAbsorptionHFMultiplacation, 1, 6, 1, 1);

        airAbsorptionHFFactor = new QLineEdit(airAbsorptionHFWidget);
        airAbsorptionHFFactor->setObjectName("airAbsorptionHFFactor");
        sizePolicy.setHeightForWidth(airAbsorptionHFFactor->sizePolicy().hasHeightForWidth());
        airAbsorptionHFFactor->setSizePolicy(sizePolicy);

        airAbsorptionHFLayout->addWidget(airAbsorptionHFFactor, 1, 5, 1, 1);

        airAbsorptionHFPlus = new QLabel(airAbsorptionHFWidget);
        airAbsorptionHFPlus->setObjectName("airAbsorptionHFPlus");

        airAbsorptionHFLayout->addWidget(airAbsorptionHFPlus, 1, 4, 1, 1);

        airAbsorptionHFValue = new QLabel(airAbsorptionHFWidget);
        airAbsorptionHFValue->setObjectName("airAbsorptionHFValue");

        airAbsorptionHFLayout->addWidget(airAbsorptionHFValue, 1, 1, 1, 1);


        verticalLayout->addWidget(airAbsorptionHFWidget);

        decayHFRatioWidget = new QWidget(scrollAreaWidgetContents);
        decayHFRatioWidget->setObjectName("decayHFRatioWidget");
        decayHFRatioWidgetLayout = new QGridLayout(decayHFRatioWidget);
        decayHFRatioWidgetLayout->setObjectName("decayHFRatioWidgetLayout");
        decayHFRatioLabel = new QLabel(decayHFRatioWidget);
        decayHFRatioLabel->setObjectName("decayHFRatioLabel");

        decayHFRatioWidgetLayout->addWidget(decayHFRatioLabel, 1, 0, 1, 1);

        decayHFRatioMultiplacation = new QLabel(decayHFRatioWidget);
        decayHFRatioMultiplacation->setObjectName("decayHFRatioMultiplacation");

        decayHFRatioWidgetLayout->addWidget(decayHFRatioMultiplacation, 1, 6, 1, 1);

        decayHFRatioIntercept = new QLineEdit(decayHFRatioWidget);
        decayHFRatioIntercept->setObjectName("decayHFRatioIntercept");
        sizePolicy.setHeightForWidth(decayHFRatioIntercept->sizePolicy().hasHeightForWidth());
        decayHFRatioIntercept->setSizePolicy(sizePolicy);

        decayHFRatioWidgetLayout->addWidget(decayHFRatioIntercept, 1, 2, 1, 1);

        decayHFRatioPlus = new QLabel(decayHFRatioWidget);
        decayHFRatioPlus->setObjectName("decayHFRatioPlus");

        decayHFRatioWidgetLayout->addWidget(decayHFRatioPlus, 1, 4, 1, 1);

        decayHFRatioFactor = new QLineEdit(decayHFRatioWidget);
        decayHFRatioFactor->setObjectName("decayHFRatioFactor");
        sizePolicy.setHeightForWidth(decayHFRatioFactor->sizePolicy().hasHeightForWidth());
        decayHFRatioFactor->setSizePolicy(sizePolicy);

        decayHFRatioWidgetLayout->addWidget(decayHFRatioFactor, 1, 5, 1, 1);

        decayHFRatioRoomSize = new QLabel(decayHFRatioWidget);
        decayHFRatioRoomSize->setObjectName("decayHFRatioRoomSize");

        decayHFRatioWidgetLayout->addWidget(decayHFRatioRoomSize, 1, 7, 1, 1);

        decayHFRatioValue = new QLabel(decayHFRatioWidget);
        decayHFRatioValue->setObjectName("decayHFRatioValue");

        decayHFRatioWidgetLayout->addWidget(decayHFRatioValue, 1, 1, 1, 1);


        verticalLayout->addWidget(decayHFRatioWidget);

        decayLFRatioWidget = new QWidget(scrollAreaWidgetContents);
        decayLFRatioWidget->setObjectName("decayLFRatioWidget");
        decayLFRatioLayout = new QGridLayout(decayLFRatioWidget);
        decayLFRatioLayout->setObjectName("decayLFRatioLayout");
        decayLFRatioMultiplacation = new QLabel(decayLFRatioWidget);
        decayLFRatioMultiplacation->setObjectName("decayLFRatioMultiplacation");

        decayLFRatioLayout->addWidget(decayLFRatioMultiplacation, 1, 6, 1, 1);

        decayLFRatioLabel = new QLabel(decayLFRatioWidget);
        decayLFRatioLabel->setObjectName("decayLFRatioLabel");

        decayLFRatioLayout->addWidget(decayLFRatioLabel, 1, 0, 1, 1);

        decayLFRatioFactor = new QLineEdit(decayLFRatioWidget);
        decayLFRatioFactor->setObjectName("decayLFRatioFactor");
        sizePolicy.setHeightForWidth(decayLFRatioFactor->sizePolicy().hasHeightForWidth());
        decayLFRatioFactor->setSizePolicy(sizePolicy);

        decayLFRatioLayout->addWidget(decayLFRatioFactor, 1, 5, 1, 1);

        decayLFRatioRoomSize = new QLabel(decayLFRatioWidget);
        decayLFRatioRoomSize->setObjectName("decayLFRatioRoomSize");

        decayLFRatioLayout->addWidget(decayLFRatioRoomSize, 1, 7, 1, 1);

        decayLFRatioIntercept = new QLineEdit(decayLFRatioWidget);
        decayLFRatioIntercept->setObjectName("decayLFRatioIntercept");
        sizePolicy.setHeightForWidth(decayLFRatioIntercept->sizePolicy().hasHeightForWidth());
        decayLFRatioIntercept->setSizePolicy(sizePolicy);

        decayLFRatioLayout->addWidget(decayLFRatioIntercept, 1, 2, 1, 1);

        decayLFRatioPlus = new QLabel(decayLFRatioWidget);
        decayLFRatioPlus->setObjectName("decayLFRatioPlus");

        decayLFRatioLayout->addWidget(decayLFRatioPlus, 1, 4, 1, 1);

        decayLFRatioValue = new QLabel(decayLFRatioWidget);
        decayLFRatioValue->setObjectName("decayLFRatioValue");

        decayLFRatioLayout->addWidget(decayLFRatioValue, 1, 1, 1, 1);


        verticalLayout->addWidget(decayLFRatioWidget);

        diffusionWidget = new QWidget(scrollAreaWidgetContents);
        diffusionWidget->setObjectName("diffusionWidget");
        diffussionLayout = new QGridLayout(diffusionWidget);
        diffussionLayout->setObjectName("diffussionLayout");
        diffusionMultiplacation = new QLabel(diffusionWidget);
        diffusionMultiplacation->setObjectName("diffusionMultiplacation");

        diffussionLayout->addWidget(diffusionMultiplacation, 1, 6, 1, 1);

        diffusionValue = new QLabel(diffusionWidget);
        diffusionValue->setObjectName("diffusionValue");

        diffussionLayout->addWidget(diffusionValue, 1, 1, 1, 1);

        diffusionLabel = new QLabel(diffusionWidget);
        diffusionLabel->setObjectName("diffusionLabel");

        diffussionLayout->addWidget(diffusionLabel, 1, 0, 1, 1);

        diffusionRoomSize = new QLabel(diffusionWidget);
        diffusionRoomSize->setObjectName("diffusionRoomSize");

        diffussionLayout->addWidget(diffusionRoomSize, 1, 7, 1, 1);

        diffusionFactor = new QLineEdit(diffusionWidget);
        diffusionFactor->setObjectName("diffusionFactor");
        sizePolicy.setHeightForWidth(diffusionFactor->sizePolicy().hasHeightForWidth());
        diffusionFactor->setSizePolicy(sizePolicy);

        diffussionLayout->addWidget(diffusionFactor, 1, 5, 1, 1);

        diffusionPlus = new QLabel(diffusionWidget);
        diffusionPlus->setObjectName("diffusionPlus");

        diffussionLayout->addWidget(diffusionPlus, 1, 4, 1, 1);

        diffusionIntercept = new QLineEdit(diffusionWidget);
        diffusionIntercept->setObjectName("diffusionIntercept");
        sizePolicy.setHeightForWidth(diffusionIntercept->sizePolicy().hasHeightForWidth());
        diffusionIntercept->setSizePolicy(sizePolicy);

        diffussionLayout->addWidget(diffusionIntercept, 1, 2, 1, 1);


        verticalLayout->addWidget(diffusionWidget);

        densityWidget = new QWidget(scrollAreaWidgetContents);
        densityWidget->setObjectName("densityWidget");
        densityLayout = new QGridLayout(densityWidget);
        densityLayout->setObjectName("densityLayout");
        densityMultiplacation = new QLabel(densityWidget);
        densityMultiplacation->setObjectName("densityMultiplacation");

        densityLayout->addWidget(densityMultiplacation, 1, 6, 1, 1);

        densityPlus = new QLabel(densityWidget);
        densityPlus->setObjectName("densityPlus");

        densityLayout->addWidget(densityPlus, 1, 4, 1, 1);

        densityRoomSize = new QLabel(densityWidget);
        densityRoomSize->setObjectName("densityRoomSize");

        densityLayout->addWidget(densityRoomSize, 1, 7, 1, 1);

        densityLabel = new QLabel(densityWidget);
        densityLabel->setObjectName("densityLabel");

        densityLayout->addWidget(densityLabel, 1, 0, 1, 1);

        densityFactor = new QLineEdit(densityWidget);
        densityFactor->setObjectName("densityFactor");
        sizePolicy.setHeightForWidth(densityFactor->sizePolicy().hasHeightForWidth());
        densityFactor->setSizePolicy(sizePolicy);

        densityLayout->addWidget(densityFactor, 1, 5, 1, 1);

        densityIntercept = new QLineEdit(densityWidget);
        densityIntercept->setObjectName("densityIntercept");
        sizePolicy.setHeightForWidth(densityIntercept->sizePolicy().hasHeightForWidth());
        densityIntercept->setSizePolicy(sizePolicy);

        densityLayout->addWidget(densityIntercept, 1, 2, 1, 1);

        densityValue = new QLabel(densityWidget);
        densityValue->setObjectName("densityValue");

        densityLayout->addWidget(densityValue, 1, 1, 1, 1);


        verticalLayout->addWidget(densityWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        SourceParameterWidgetLayout->addWidget(scrollArea);


        retranslateUi(SourceParameterWidget);

        QMetaObject::connectSlotsByName(SourceParameterWidget);
    } // setupUi

    void retranslateUi(QWidget *SourceParameterWidget)
    {
        SourceParameterWidget->setWindowTitle(QCoreApplication::translate("SourceParameterWidget", "Form", nullptr));
        nameLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\345\243\260\346\272\220\345\220\215\347\247\260\357\274\232", nullptr));
        roomSizeLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\344\274\260\347\256\227\346\210\277\351\227\264\345\244\247\345\260\217\357\274\210roomSize\357\274\211\357\274\232", nullptr));
        roomSizeValue->setText(QCoreApplication::translate("SourceParameterWidget", "0", nullptr));
        decayTimeMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        decayTimeLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\350\241\260\345\207\217\346\227\266\351\227\264\357\274\232", nullptr));
        decayTimeRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        decayTimePlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        decayTimeValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        reflectionsDelayRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        reflectionsDelayPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        reflectionsDelayMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        reflectionsDelayLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\345\217\215\345\260\204\345\273\266\350\277\237\357\274\232", nullptr));
        reflectionsDelayValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        lateReverbDelayRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        lateReverbDelayMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        lateReverbDelayLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\346\267\267\345\223\215\345\273\266\350\277\237\357\274\232", nullptr));
        lateReverbDelayPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        lateReverbDelayValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        gainPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        gainMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        gainLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\346\200\273\345\242\236\347\233\212\357\274\232", nullptr));
        gainRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        gainValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        reflectionsGainRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        reflectionsGainLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\345\217\215\345\260\204\345\242\236\347\233\212\357\274\232", nullptr));
        reflectionsGainPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        reflectionsGainMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        reflectionsGainValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        lateReverbGainLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\345\220\216\346\234\237\346\267\267\345\223\215\345\242\236\347\233\212\357\274\232", nullptr));
        lateReverbGainRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        lateReverbGainMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        lateReverbGainPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        lateReverbGainValue->setText(QCoreApplication::translate("SourceParameterWidget", "l", nullptr));
        airAbsorptionHFRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        airAbsorptionHFLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\351\253\230\351\242\221\347\251\272\346\260\224\345\220\270\346\224\266\357\274\232", nullptr));
        airAbsorptionHFMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        airAbsorptionHFPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        airAbsorptionHFValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        decayHFRatioLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\351\253\230\351\242\221\350\241\260\345\207\217\346\257\224\357\274\232", nullptr));
        decayHFRatioMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        decayHFRatioPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        decayHFRatioRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        decayHFRatioValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        decayLFRatioMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        decayLFRatioLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\344\275\216\351\242\221\350\241\260\345\207\217\346\257\224\357\274\232", nullptr));
        decayLFRatioRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        decayLFRatioPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        decayLFRatioValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        diffusionMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        diffusionValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
        diffusionLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\346\211\251\346\225\243\345\272\246\357\274\232", nullptr));
        diffusionRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        diffusionPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        densityMultiplacation->setText(QCoreApplication::translate("SourceParameterWidget", " * ", nullptr));
        densityPlus->setText(QCoreApplication::translate("SourceParameterWidget", " + ", nullptr));
        densityRoomSize->setText(QCoreApplication::translate("SourceParameterWidget", "roomSize", nullptr));
        densityLabel->setText(QCoreApplication::translate("SourceParameterWidget", "\345\257\206\345\272\246\357\274\232", nullptr));
        densityValue->setText(QCoreApplication::translate("SourceParameterWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SourceParameterWidget: public Ui_SourceParameterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOURCEPARAMETERWIDGET_H
