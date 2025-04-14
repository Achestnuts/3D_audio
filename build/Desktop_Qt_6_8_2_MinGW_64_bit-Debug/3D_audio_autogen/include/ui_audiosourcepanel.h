/********************************************************************************
** Form generated from reading UI file 'audiosourcepanel.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOSOURCEPANEL_H
#define UI_AUDIOSOURCEPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioSourcePanel
{
public:
    QGridLayout *gridLayout;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSlider *progressSlider;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSlider *volumeSlider;
    QLabel *labelProgress;

    void setupUi(QWidget *AudioSourcePanel)
    {
        if (AudioSourcePanel->objectName().isEmpty())
            AudioSourcePanel->setObjectName("AudioSourcePanel");
        AudioSourcePanel->resize(315, 520);
        gridLayout = new QGridLayout(AudioSourcePanel);
        gridLayout->setObjectName("gridLayout");
        playPauseButton = new QPushButton(AudioSourcePanel);
        playPauseButton->setObjectName("playPauseButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/play.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        playPauseButton->setIcon(icon);
        playPauseButton->setIconSize(QSize(50, 50));

        gridLayout->addWidget(playPauseButton, 2, 1, 1, 1);

        stopButton = new QPushButton(AudioSourcePanel);
        stopButton->setObjectName("stopButton");

        gridLayout->addWidget(stopButton, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 2, 1, 1);

        progressSlider = new QSlider(AudioSourcePanel);
        progressSlider->setObjectName("progressSlider");
        progressSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(progressSlider, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        volumeSlider = new QSlider(AudioSourcePanel);
        volumeSlider->setObjectName("volumeSlider");
        volumeSlider->setOrientation(Qt::Orientation::Vertical);

        gridLayout->addWidget(volumeSlider, 0, 3, 2, 1);

        labelProgress = new QLabel(AudioSourcePanel);
        labelProgress->setObjectName("labelProgress");

        gridLayout->addWidget(labelProgress, 1, 0, 1, 1);


        retranslateUi(AudioSourcePanel);

        QMetaObject::connectSlotsByName(AudioSourcePanel);
    } // setupUi

    void retranslateUi(QWidget *AudioSourcePanel)
    {
        AudioSourcePanel->setWindowTitle(QCoreApplication::translate("AudioSourcePanel", "Form", nullptr));
        playPauseButton->setText(QString());
        stopButton->setText(QCoreApplication::translate("AudioSourcePanel", "stop", nullptr));
        labelProgress->setText(QCoreApplication::translate("AudioSourcePanel", "00:00 / 00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioSourcePanel: public Ui_AudioSourcePanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOSOURCEPANEL_H
