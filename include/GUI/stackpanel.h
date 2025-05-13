#ifndef STACKPANEL_H
#define STACKPANEL_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class StackPanel;
}

class StackPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StackPanel(QWidget *parent = nullptr);
    ~StackPanel();

    void setCurrentPage(int index);
    void setPageWidget(QWidget* widget, int index = -1);  // 添加页面

    Ui::StackPanel *ui;

    float widthFactor = 0.4, heightFactor = 0.4;
    QPropertyAnimation* showAnimation;
    bool is_visible = true;

    void updatePosition();
    void togglePanel();
};

#endif // STACKPANEL_H
