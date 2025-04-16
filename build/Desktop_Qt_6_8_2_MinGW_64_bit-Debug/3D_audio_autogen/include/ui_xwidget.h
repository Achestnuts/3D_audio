/********************************************************************************
** Form generated from reading UI file 'xwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XWIDGET_H
#define UI_XWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <audiosourcepanel.h>
#include <occlusionfilterpanel.h>
#include <roommap.h>
#include <sourceparameterwidget.h>

QT_BEGIN_NAMESPACE

class Ui_XWidget
{
public:
    QVBoxLayout *XWidgetLayout;
    QWidget *top;
    QGridLayout *topLayout;
    QPushButton *pushButtonMin;
    QPushButton *pushButtonRestore;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonMax;
    QSpacerItem *hSpacerRight;
    QSpacerItem *hSpacerMaxAndNor;
    QSpacerItem *hSpacerLeft;
    QSpacerItem *hSpacerNorAndClose;
    QSpacerItem *hSpacerMinAndMax;
    QWidget *contentWidget;
    QGridLayout *contentWidgetLayout;
    RoomMap *roomMap;
    QStackedWidget *stackedPanel;
    QWidget *publicParameter;
    QGridLayout *publicParaterLayout;
    QLineEdit *lineEdit_4;
    QLabel *publicParameterTitle;
    QLabel *gridMeterLabel;
    QLineEdit *lineEdit_2;
    QLabel *meterLabel;
    QLineEdit *gridMeterEdit;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_3;
    QPushButton *stopButton;
    QPushButton *startButton;
    QPushButton *sceneSaveButton;
    QPushButton *sceneLoadButton;
    AudioSourcePanel *audioSourcePanel;
    SourceParameterWidget *sourceParameterWidget;
    QGridLayout *itemParameterLayout;
    OcclusionFilterPanel *occlusionFilterPanel;

    void setupUi(QWidget *XWidget)
    {
        if (XWidget->objectName().isEmpty())
            XWidget->setObjectName("XWidget");
        XWidget->resize(827, 602);
        QFont font;
        font.setWeight(QFont::Thin);
        XWidget->setFont(font);
        XWidget->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256\351\241\266\351\203\250\346\240\217\347\232\204\346\240\267\345\274\217 */\n"
"QWidget#top {\n"
"    background-color: #2c3e50; /* \346\267\261\350\223\235\350\211\262\350\203\214\346\231\257 */\n"
"    color: red; /*\347\272\242\350\211\262\346\226\207\345\255\227 */\n"
"    border-top-left-radius: 7px;     /* \345\267\246\344\270\212\350\247\222 */\n"
"    border-top-right-radius: 7px;     /* \345\217\263\344\270\212\350\247\222 */\n"
"}\n"
"\n"
"#contentWidget {\n"
"    background-color:white;/* \347\231\275\350\211\262\350\203\214\346\231\257 */\n"
"    border-bottom-left-radius: 7px;  /* \345\267\246\344\270\213\350\247\222 */\n"
"    border-bottom-right-radius: 7px; /* \345\217\263\344\270\213\350\247\222 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256\346\214\211\351\222\256\347\232\204\345\237\272\346\234\254\346\240\267\345\274\217*/\n"
"QPushButton {\n"
"    background-color: #3498db; /* \350\223\235\350\211\262\350\203\214\346\231\257 */\n"
"    border: none; /* \346\227\240"
                        "\350\276\271\346\241\206 */\n"
"    color: red; /* \347\272\242\350\211\262\346\226\207\345\255\227 */\n"
"    margin: 4px; /* \346\214\211\351\222\256\345\244\226\350\276\271\350\267\235 */\n"
"    border-radius: 5px; /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\346\214\211\351\222\256\347\232\204\346\240\267\345\274\217 */\n"
"QPushButton:hover {\n"
"    background-color: #2980b9; /* \346\267\261\344\270\200\344\272\233\347\232\204\350\223\235\350\211\262 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\346\227\266\346\214\211\351\222\256\347\232\204\346\240\267\345\274\217 */\n"
"QPushButton:pressed {\n"
"    background-color: #1e3799; /* \346\233\264\346\267\261\347\232\204\350\223\235\350\211\262 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256\346\260\264\345\271\263\351\227\264\350\267\235\347\232\204\346\240\267\345\274\217 */\n"
"spacer#hSpacerLeft,\n"
"spacer#hSpacerMinAndMax,\n"
"spacer#hSpacer"
                        "MaxAndNor,\n"
"spacer#hSpacerNorAndClose,\n"
"spacer#hSpacerRight {\n"
"    background-color: transparent; /* \351\200\217\346\230\216\350\203\214\346\231\257 */\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256\345\236\202\347\233\264\351\227\264\350\267\235\347\232\204\346\240\267\345\274\217 */\n"
"spacer#vSpacer {\n"
"    background-color: transparent; /* \351\200\217\346\230\216\350\203\214\346\231\257 */\n"
"}\n"
"\n"
"\n"
""));
        XWidgetLayout = new QVBoxLayout(XWidget);
        XWidgetLayout->setSpacing(0);
        XWidgetLayout->setObjectName("XWidgetLayout");
        XWidgetLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        XWidgetLayout->setContentsMargins(10, 10, 10, 10);
        top = new QWidget(XWidget);
        top->setObjectName("top");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(top->sizePolicy().hasHeightForWidth());
        top->setSizePolicy(sizePolicy);
        topLayout = new QGridLayout(top);
        topLayout->setSpacing(0);
        topLayout->setObjectName("topLayout");
        topLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        topLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonMin = new QPushButton(top);
        pushButtonMin->setObjectName("pushButtonMin");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonMin->sizePolicy().hasHeightForWidth());
        pushButtonMin->setSizePolicy(sizePolicy1);
        pushButtonMin->setMinimumSize(QSize(25, 25));
        pushButtonMin->setMaximumSize(QSize(25, 25));
        pushButtonMin->setBaseSize(QSize(25, 25));

        topLayout->addWidget(pushButtonMin, 0, 1, 1, 1);

        pushButtonRestore = new QPushButton(top);
        pushButtonRestore->setObjectName("pushButtonRestore");
        pushButtonRestore->setEnabled(true);
        sizePolicy1.setHeightForWidth(pushButtonRestore->sizePolicy().hasHeightForWidth());
        pushButtonRestore->setSizePolicy(sizePolicy1);
        pushButtonRestore->setMinimumSize(QSize(25, 25));
        pushButtonRestore->setMaximumSize(QSize(25, 25));
        pushButtonRestore->setBaseSize(QSize(25, 25));

        topLayout->addWidget(pushButtonRestore, 0, 5, 1, 1);

        pushButtonClose = new QPushButton(top);
        pushButtonClose->setObjectName("pushButtonClose");
        sizePolicy1.setHeightForWidth(pushButtonClose->sizePolicy().hasHeightForWidth());
        pushButtonClose->setSizePolicy(sizePolicy1);
        pushButtonClose->setMinimumSize(QSize(25, 25));
        pushButtonClose->setMaximumSize(QSize(25, 25));
        pushButtonClose->setBaseSize(QSize(25, 25));

        topLayout->addWidget(pushButtonClose, 0, 7, 1, 1);

        pushButtonMax = new QPushButton(top);
        pushButtonMax->setObjectName("pushButtonMax");
        sizePolicy1.setHeightForWidth(pushButtonMax->sizePolicy().hasHeightForWidth());
        pushButtonMax->setSizePolicy(sizePolicy1);
        pushButtonMax->setMinimumSize(QSize(25, 25));
        pushButtonMax->setMaximumSize(QSize(25, 25));
        pushButtonMax->setBaseSize(QSize(25, 25));

        topLayout->addWidget(pushButtonMax, 0, 3, 1, 1);

        hSpacerRight = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        topLayout->addItem(hSpacerRight, 0, 8, 1, 1);

        hSpacerMaxAndNor = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        topLayout->addItem(hSpacerMaxAndNor, 0, 4, 1, 1);

        hSpacerLeft = new QSpacerItem(578, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topLayout->addItem(hSpacerLeft, 0, 0, 1, 1);

        hSpacerNorAndClose = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        topLayout->addItem(hSpacerNorAndClose, 0, 6, 1, 1);

        hSpacerMinAndMax = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        topLayout->addItem(hSpacerMinAndMax, 0, 2, 1, 1);


        XWidgetLayout->addWidget(top);

        contentWidget = new QWidget(XWidget);
        contentWidget->setObjectName("contentWidget");
        contentWidgetLayout = new QGridLayout(contentWidget);
        contentWidgetLayout->setObjectName("contentWidgetLayout");
        roomMap = new RoomMap(contentWidget);
        roomMap->setObjectName("roomMap");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(roomMap->sizePolicy().hasHeightForWidth());
        roomMap->setSizePolicy(sizePolicy2);

        contentWidgetLayout->addWidget(roomMap, 0, 0, 2, 1);

        stackedPanel = new QStackedWidget(contentWidget);
        stackedPanel->setObjectName("stackedPanel");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(stackedPanel->sizePolicy().hasHeightForWidth());
        stackedPanel->setSizePolicy(sizePolicy3);
        publicParameter = new QWidget();
        publicParameter->setObjectName("publicParameter");
        publicParaterLayout = new QGridLayout(publicParameter);
        publicParaterLayout->setObjectName("publicParaterLayout");
        lineEdit_4 = new QLineEdit(publicParameter);
        lineEdit_4->setObjectName("lineEdit_4");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy4);

        publicParaterLayout->addWidget(lineEdit_4, 4, 2, 1, 3);

        publicParameterTitle = new QLabel(publicParameter);
        publicParameterTitle->setObjectName("publicParameterTitle");

        publicParaterLayout->addWidget(publicParameterTitle, 1, 0, 1, 5);

        gridMeterLabel = new QLabel(publicParameter);
        gridMeterLabel->setObjectName("gridMeterLabel");

        publicParaterLayout->addWidget(gridMeterLabel, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(publicParameter);
        lineEdit_2->setObjectName("lineEdit_2");
        sizePolicy4.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy4);

        publicParaterLayout->addWidget(lineEdit_2, 6, 2, 1, 3);

        meterLabel = new QLabel(publicParameter);
        meterLabel->setObjectName("meterLabel");

        publicParaterLayout->addWidget(meterLabel, 2, 4, 1, 1);

        gridMeterEdit = new QLineEdit(publicParameter);
        gridMeterEdit->setObjectName("gridMeterEdit");
        sizePolicy4.setHeightForWidth(gridMeterEdit->sizePolicy().hasHeightForWidth());
        gridMeterEdit->setSizePolicy(sizePolicy4);

        publicParaterLayout->addWidget(gridMeterEdit, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        publicParaterLayout->addItem(verticalSpacer, 9, 3, 1, 1);

        lineEdit_3 = new QLineEdit(publicParameter);
        lineEdit_3->setObjectName("lineEdit_3");
        sizePolicy4.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy4);

        publicParaterLayout->addWidget(lineEdit_3, 5, 2, 1, 3);

        stopButton = new QPushButton(publicParameter);
        stopButton->setObjectName("stopButton");

        publicParaterLayout->addWidget(stopButton, 7, 3, 1, 1);

        startButton = new QPushButton(publicParameter);
        startButton->setObjectName("startButton");

        publicParaterLayout->addWidget(startButton, 7, 2, 1, 1);

        sceneSaveButton = new QPushButton(publicParameter);
        sceneSaveButton->setObjectName("sceneSaveButton");

        publicParaterLayout->addWidget(sceneSaveButton, 8, 2, 1, 1);

        sceneLoadButton = new QPushButton(publicParameter);
        sceneLoadButton->setObjectName("sceneLoadButton");

        publicParaterLayout->addWidget(sceneLoadButton, 8, 3, 1, 1);

        stackedPanel->addWidget(publicParameter);
        audioSourcePanel = new AudioSourcePanel();
        audioSourcePanel->setObjectName("audioSourcePanel");
        stackedPanel->addWidget(audioSourcePanel);
        sourceParameterWidget = new SourceParameterWidget();
        sourceParameterWidget->setObjectName("sourceParameterWidget");
        itemParameterLayout = new QGridLayout(sourceParameterWidget);
        itemParameterLayout->setObjectName("itemParameterLayout");
        stackedPanel->addWidget(sourceParameterWidget);
        occlusionFilterPanel = new OcclusionFilterPanel();
        occlusionFilterPanel->setObjectName("occlusionFilterPanel");
        stackedPanel->addWidget(occlusionFilterPanel);

        contentWidgetLayout->addWidget(stackedPanel, 0, 1, 2, 1);


        XWidgetLayout->addWidget(contentWidget);


        retranslateUi(XWidget);

        stackedPanel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(XWidget);
    } // setupUi

    void retranslateUi(QWidget *XWidget)
    {
        XWidget->setWindowTitle(QCoreApplication::translate("XWidget", "XWidget", nullptr));
        pushButtonMin->setText(QCoreApplication::translate("XWidget", "\344\270\200", nullptr));
        pushButtonRestore->setText(QCoreApplication::translate("XWidget", "\345\223\201", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("XWidget", "X", nullptr));
        pushButtonMax->setText(QCoreApplication::translate("XWidget", "\345\217\243", nullptr));
        publicParameterTitle->setText(QCoreApplication::translate("XWidget", "\345\205\254\345\205\261\345\217\202\346\225\260", nullptr));
        gridMeterLabel->setText(QCoreApplication::translate("XWidget", "\346\240\274\345\255\220\351\225\277\345\272\246", nullptr));
        meterLabel->setText(QCoreApplication::translate("XWidget", "\347\261\263", nullptr));
        stopButton->setText(QCoreApplication::translate("XWidget", "stop", nullptr));
        startButton->setText(QCoreApplication::translate("XWidget", "start", nullptr));
        sceneSaveButton->setText(QCoreApplication::translate("XWidget", "save", nullptr));
        sceneLoadButton->setText(QCoreApplication::translate("XWidget", "load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XWidget: public Ui_XWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XWIDGET_H
