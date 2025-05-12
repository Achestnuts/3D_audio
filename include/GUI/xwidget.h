#ifndef XWIDGET_H
#define XWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "stackpanel.h"
#include "ui_stackpanel.h"

#define MARGIN_MIN_SIZE -10
#define MARGIN_MAX_SIZE 15

#define NONE 0
#define UP 1
#define TOPRIGHT 2
#define RIGHT 3
#define BOTTOMRIGHT 4
#define DOWN 5
#define BOTTOMLEFT 6
#define LEFT 7
#define TOPLEFT 8

QT_BEGIN_NAMESPACE
namespace Ui {
class XWidget;
}
QT_END_NAMESPACE


// 最外透明层
class XWidget : public QWidget
{
    Q_OBJECT

public:
    XWidget(QWidget *parent = nullptr);
    ~XWidget();
    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void updateRegion(QMouseEvent *event);
    void resizeRegion(int marginTop, int marginBottom,
                      int marginLeft, int marginRight);
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void createShadow();
    void maximizeWidget();
    void restoreWidget();
    bool isWidgetSizeGreaterScreenSize();
    bool eventFilter(QObject *watched, QEvent *event) override;
    void animatePageSwitch(int from, int to);

    Ui::XWidget* ui;                          //边框ui
    StackPanel* stackPanel;
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

// public slots:
//     void updateSourceParameterWidget(DraggableSource* source);
//     void updateParameterWidget(DraggableListener* source);
//     void updateParameterWidget(WallRectItem* source);

// signals:
//     void clickClose();

    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    //void showEvent(QShowEvent *event) override;
private:

    // std::shared_ptr<RoomMap> roomMap;
    // ContentWidget *contentWidget;             //中间内容层
    bool m_bIsPressed;                        //是否按下鼠标
    bool m_bIsDoublePressed;                  //是否是左键双击
    bool m_bIsResizing;                       //是否正在调整窗口，调整窗口大小时不移动
    int m_direction;                          //拖拽方向

    QPointF m_movePoint;                      //鼠标移动至何处
    QPointF m_pressPoint;                     //鼠标按下的位置

};


#endif // XWIDGET_H


















