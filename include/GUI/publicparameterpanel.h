#ifndef PUBLICPARAMETERPANEL_H
#define PUBLICPARAMETERPANEL_H

#include <QWidget>
#include "ui_publicparameterpanel.h"

namespace Ui {
class PublicParameterPanel;
}

class PublicParameterPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PublicParameterPanel(QWidget *parent = nullptr);

    Ui::PublicParameterPanel *ui;

protected:
    QSize sizeHint() const override;
private:

};

#endif // PUBLICPARAMETERPANEL_H
