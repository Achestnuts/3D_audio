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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <roommap.h>

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
    QVBoxLayout *verticalLayout;
    QPushButton *toggleButton;

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

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        toggleButton = new QPushButton(contentWidget);
        toggleButton->setObjectName("toggleButton");

        verticalLayout->addWidget(toggleButton);


        contentWidgetLayout->addLayout(verticalLayout, 0, 2, 2, 1);


        XWidgetLayout->addWidget(contentWidget);


        retranslateUi(XWidget);

        QMetaObject::connectSlotsByName(XWidget);
    } // setupUi

    void retranslateUi(QWidget *XWidget)
    {
        XWidget->setWindowTitle(QCoreApplication::translate("XWidget", "XWidget", nullptr));
        pushButtonMin->setText(QCoreApplication::translate("XWidget", "\344\270\200", nullptr));
        pushButtonRestore->setText(QCoreApplication::translate("XWidget", "\345\223\201", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("XWidget", "X", nullptr));
        pushButtonMax->setText(QCoreApplication::translate("XWidget", "\345\217\243", nullptr));
        toggleButton->setText(QCoreApplication::translate("XWidget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XWidget: public Ui_XWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XWIDGET_H
