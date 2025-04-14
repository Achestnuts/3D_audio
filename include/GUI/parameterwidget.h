#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QPushButton>
#include <QWidget>

class ParameterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParameterWidget(QWidget *parent = nullptr);

    QPushButton* add;

signals:
};

#endif // PARAMETERWIDGET_H
