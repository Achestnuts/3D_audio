#ifndef SOURCEPARAMETERWIDGET_H
#define SOURCEPARAMETERWIDGET_H

#include "draggablesource.h"
#include <QWidget>

namespace Ui {
class SourceParameterWidget;
}

class SourceParameterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SourceParameterWidget(QWidget *parent = nullptr);
    void disconnectBound();
    bool boundSource(DraggableSource* boundSource);
    Ui::SourceParameterWidget *ui;
    DraggableSource* source;
private:

};

#endif // SOURCEPARAMETERWIDGET_H
