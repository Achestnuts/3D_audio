/********************************************************************************
** Form generated from reading UI file 'occlusionfilterpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCCLUSIONFILTERPANEL_H
#define UI_OCCLUSIONFILTERPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <waveformwidget.h>

QT_BEGIN_NAMESPACE

class Ui_OcclusionFilterPanel
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QDial *knobGainHF;
    QDial *knobGainLF;
    QDial *knobGain;
    QLabel *label_2;
    QLabel *labelGain;
    WaveformWidget *waveformWidget;
    QLabel *labelGainHF;
    QLabel *labelGainLF;

    void setupUi(QWidget *OcclusionFilterPanel)
    {
        if (OcclusionFilterPanel->objectName().isEmpty())
            OcclusionFilterPanel->setObjectName("OcclusionFilterPanel");
        OcclusionFilterPanel->resize(353, 571);
        gridLayout = new QGridLayout(OcclusionFilterPanel);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(OcclusionFilterPanel);
        label->setObjectName("label");

        gridLayout->addWidget(label, 2, 1, 1, 1);

        label_3 = new QLabel(OcclusionFilterPanel);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        knobGainHF = new QDial(OcclusionFilterPanel);
        knobGainHF->setObjectName("knobGainHF");

        gridLayout->addWidget(knobGainHF, 2, 0, 1, 1);

        knobGainLF = new QDial(OcclusionFilterPanel);
        knobGainLF->setObjectName("knobGainLF");

        gridLayout->addWidget(knobGainLF, 3, 0, 1, 1);

        knobGain = new QDial(OcclusionFilterPanel);
        knobGain->setObjectName("knobGain");

        gridLayout->addWidget(knobGain, 1, 0, 1, 1);

        label_2 = new QLabel(OcclusionFilterPanel);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        labelGain = new QLabel(OcclusionFilterPanel);
        labelGain->setObjectName("labelGain");

        gridLayout->addWidget(labelGain, 1, 2, 1, 1);

        waveformWidget = new WaveformWidget(OcclusionFilterPanel);
        waveformWidget->setObjectName("waveformWidget");

        gridLayout->addWidget(waveformWidget, 0, 0, 1, 3);

        labelGainHF = new QLabel(OcclusionFilterPanel);
        labelGainHF->setObjectName("labelGainHF");

        gridLayout->addWidget(labelGainHF, 2, 2, 1, 1);

        labelGainLF = new QLabel(OcclusionFilterPanel);
        labelGainLF->setObjectName("labelGainLF");

        gridLayout->addWidget(labelGainLF, 3, 2, 1, 1);


        retranslateUi(OcclusionFilterPanel);

        QMetaObject::connectSlotsByName(OcclusionFilterPanel);
    } // setupUi

    void retranslateUi(QWidget *OcclusionFilterPanel)
    {
        OcclusionFilterPanel->setWindowTitle(QCoreApplication::translate("OcclusionFilterPanel", "Form", nullptr));
        label->setText(QCoreApplication::translate("OcclusionFilterPanel", "GainHF:", nullptr));
        label_3->setText(QCoreApplication::translate("OcclusionFilterPanel", "GainLF:", nullptr));
        label_2->setText(QCoreApplication::translate("OcclusionFilterPanel", "Gain:", nullptr));
        labelGain->setText(QCoreApplication::translate("OcclusionFilterPanel", "TextLabel", nullptr));
        labelGainHF->setText(QCoreApplication::translate("OcclusionFilterPanel", "TextLabel", nullptr));
        labelGainLF->setText(QCoreApplication::translate("OcclusionFilterPanel", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OcclusionFilterPanel: public Ui_OcclusionFilterPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCCLUSIONFILTERPANEL_H
