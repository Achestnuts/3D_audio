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
    void updatePosition();

    Ui::StackPanel *ui;

    float widthFactor = 0.4, heightFactor = 0.8;

protected:

private slots:
    void togglePanel();

private:

    QPropertyAnimation* animation;
    bool isExpanded = false;


};

#endif // STACKPANEL_H
