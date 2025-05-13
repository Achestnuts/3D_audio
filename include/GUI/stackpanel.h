#ifndef STACKPANEL_H
#define STACKPANEL_H

#include <QWidget>
#include <QPropertyAnimation>

#define NONE 0
#define UP 1
#define TOPRIGHT 2
#define RIGHT 3
#define BOTTOMRIGHT 4
#define DOWN 5
#define BOTTOMLEFT 6
#define LEFT 7
#define TOPLEFT 8

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
    bool resizing = false;

    void updatePosition();
    void togglePanel();
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    int resizeDirection = 0;
    QPoint dragStartPos;
    QRect originalRect;
};

#endif // STACKPANEL_H
