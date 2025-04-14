#include "parameterwidget.h"

#include <QBoxLayout>
#include <QPushButton>

ParameterWidget::ParameterWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    setObjectName("para");

    add = new QPushButton(this);
    add->setObjectName("addname");
    layout->addWidget(add);
    setAttribute(Qt::WA_StyleSheet, true);
    setStyleSheet("QPushButton#add {background-color: red;}");


}
