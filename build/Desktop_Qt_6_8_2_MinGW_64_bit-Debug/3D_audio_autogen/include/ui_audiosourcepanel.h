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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioSourcePanel
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QSlider *volumeSlider;
    QLabel *labelProgress;
    QSlider *progressSlider;
    QSpacerItem *horizontalSpacer;
    QPushButton *playPauseButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *AudioSourcePanel)
    {
        if (AudioSourcePanel->objectName().isEmpty())
            AudioSourcePanel->setObjectName("AudioSourcePanel");
        AudioSourcePanel->resize(315, 520);
        gridLayout = new QGridLayout(AudioSourcePanel);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(AudioSourcePanel);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 313, 518));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 205, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        volumeSlider = new QSlider(scrollAreaWidgetContents);
        volumeSlider->setObjectName("volumeSlider");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy);
        volumeSlider->setOrientation(Qt::Orientation::Vertical);

        gridLayout_2->addWidget(volumeSlider, 0, 3, 2, 1);

        labelProgress = new QLabel(scrollAreaWidgetContents);
        labelProgress->setObjectName("labelProgress");

        gridLayout_2->addWidget(labelProgress, 1, 0, 1, 1);

        progressSlider = new QSlider(scrollAreaWidgetContents);
        progressSlider->setObjectName("progressSlider");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressSlider->sizePolicy().hasHeightForWidth());
        progressSlider->setSizePolicy(sizePolicy1);
        progressSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(progressSlider, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(91, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        playPauseButton = new QPushButton(scrollAreaWidgetContents);
        playPauseButton->setObjectName("playPauseButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(playPauseButton->sizePolicy().hasHeightForWidth());
        playPauseButton->setSizePolicy(sizePolicy2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/play.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        playPauseButton->setIcon(icon);
        playPauseButton->setIconSize(QSize(50, 50));

        gridLayout_2->addWidget(playPauseButton, 2, 1, 1, 1);

        stopButton = new QPushButton(scrollAreaWidgetContents);
        stopButton->setObjectName("stopButton");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(stopButton, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(39, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 205, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 2, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 2, 6, 1, 1);


        retranslateUi(AudioSourcePanel);

        QMetaObject::connectSlotsByName(AudioSourcePanel);
    } // setupUi

    void retranslateUi(QWidget *AudioSourcePanel)
    {
        AudioSourcePanel->setWindowTitle(QCoreApplication::translate("AudioSourcePanel", "Form", nullptr));
        labelProgress->setText(QCoreApplication::translate("AudioSourcePanel", "00:00 / 00:00", nullptr));
        playPauseButton->setText(QString());
        stopButton->setText(QCoreApplication::translate("AudioSourcePanel", "stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioSourcePanel: public Ui_AudioSourcePanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOSOURCEPANEL_H
