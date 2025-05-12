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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <waveformwidget.h>

QT_BEGIN_NAMESPACE

class Ui_OcclusionFilterPanel
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    WaveformWidget *waveformWidget;
    QDial *knobGain;
    QLabel *label_2;
    QLabel *labelGain;
    QDial *knobGainHF;
    QLabel *label;
    QLabel *labelGainHF;
    QDial *knobGainLF;
    QLabel *label_3;
    QLabel *labelGainLF;

    void setupUi(QWidget *OcclusionFilterPanel)
    {
        if (OcclusionFilterPanel->objectName().isEmpty())
            OcclusionFilterPanel->setObjectName("OcclusionFilterPanel");
        OcclusionFilterPanel->resize(353, 571);
        gridLayout = new QGridLayout(OcclusionFilterPanel);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(OcclusionFilterPanel);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 351, 569));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        waveformWidget = new WaveformWidget(scrollAreaWidgetContents);
        waveformWidget->setObjectName("waveformWidget");

        gridLayout_2->addWidget(waveformWidget, 0, 0, 1, 3);

        knobGain = new QDial(scrollAreaWidgetContents);
        knobGain->setObjectName("knobGain");

        gridLayout_2->addWidget(knobGain, 1, 0, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 1, 1, 1);

        labelGain = new QLabel(scrollAreaWidgetContents);
        labelGain->setObjectName("labelGain");

        gridLayout_2->addWidget(labelGain, 1, 2, 1, 1);

        knobGainHF = new QDial(scrollAreaWidgetContents);
        knobGainHF->setObjectName("knobGainHF");

        gridLayout_2->addWidget(knobGainHF, 2, 0, 1, 1);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 2, 1, 1, 1);

        labelGainHF = new QLabel(scrollAreaWidgetContents);
        labelGainHF->setObjectName("labelGainHF");

        gridLayout_2->addWidget(labelGainHF, 2, 2, 1, 1);

        knobGainLF = new QDial(scrollAreaWidgetContents);
        knobGainLF->setObjectName("knobGainLF");

        gridLayout_2->addWidget(knobGainLF, 3, 0, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 3, 1, 1, 1);

        labelGainLF = new QLabel(scrollAreaWidgetContents);
        labelGainLF->setObjectName("labelGainLF");

        gridLayout_2->addWidget(labelGainLF, 3, 2, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(OcclusionFilterPanel);

        QMetaObject::connectSlotsByName(OcclusionFilterPanel);
    } // setupUi

    void retranslateUi(QWidget *OcclusionFilterPanel)
    {
        OcclusionFilterPanel->setWindowTitle(QCoreApplication::translate("OcclusionFilterPanel", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("OcclusionFilterPanel", "Gain:", nullptr));
        labelGain->setText(QCoreApplication::translate("OcclusionFilterPanel", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("OcclusionFilterPanel", "GainHF:", nullptr));
        labelGainHF->setText(QCoreApplication::translate("OcclusionFilterPanel", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("OcclusionFilterPanel", "GainLF:", nullptr));
        labelGainLF->setText(QCoreApplication::translate("OcclusionFilterPanel", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OcclusionFilterPanel: public Ui_OcclusionFilterPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCCLUSIONFILTERPANEL_H
