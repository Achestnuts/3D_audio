#include "stackpanel.h"
#include "ui_stackpanel.h"

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <qevent.h>
#include <QTabBar>

StackPanel::StackPanel(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::StackPanel)
    , showAnimation(new QPropertyAnimation)
{
    ui->setupUi(this);
    // 关闭透明背景属性

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setMouseTracking(true);

    // connect(ui->toggleButton, &QPushButton::clicked, this, &StackPanel::togglePanel);

    showAnimation->setTargetObject(ui->panelBodyWidget);
    showAnimation->setPropertyName("pos");
    showAnimation->setDuration(300);

    ui->stackedWidget->tabBar()->setMinimumSize(0, 0);
    ui->stackedWidget->setUsesScrollButtons(true);  // 启用滚动按钮
    ui->stackedWidget->setElideMode(Qt::ElideRight);  // 文本过长时显示省略号
    // // 方法一：使用样式表
    // ui->stackedWidget->tabBar()->setStyleSheet(
    //     "QTabBar::tab {"
    //     "    min-width: 0px;"    // 限制选项卡最小宽度
    //     "    min-height: 0px;"   // 限制选项卡最小高度
    //     "    padding: 4px 8px;"   // 减少内边距
    //     "}"
    //     );
    // ui->stackedWidget->tabBar()->hide();
    setMinimumSize(0, 0);

}

StackPanel::~StackPanel()
{
    delete ui;
}

void StackPanel::setCurrentPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void StackPanel::setPageWidget(QWidget *widget, int index)
{
    // if (index == -1)
    //     ui->stackedWidget->addTab(widget, "");
    // else
    //     ui->stackedWidget->insertWidget(index, widget);
}


void StackPanel::updatePosition()
{
    QWidget *mainWidget = parentWidget(); // 应该是 XWidget 指针
    if (!mainWidget) return;

    QWidget *mapWidget = mainWidget->findChild<QWidget*>("roomMap");
    if (!mapWidget) return;

    // 获取 roomMap 的相对位置和大小
    QPoint mapPos = mapWidget->mapTo(mainWidget, QPoint(0, 0));
    QSize mapSize = mapWidget->size();

    // 固定宽度，根据需要可自定义
    int panelWidth = mapSize.width() * widthFactor;
    int panelHeight = mapSize.height() * heightFactor;

    // 计算面板的位置（位于 roomMap 内部右侧）
    int x = mainWidget->geometry().left() + mapPos.x() + mapSize.width() - panelWidth - 15;
    int y = mainWidget->geometry().top() + mapPos.y();

    // qDebug()<<"*******************";
    // qDebug()<<x;
    // qDebug()<<mainWidget->geometry().left();
    // qDebug()<<mapPos.x();
    // qDebug()<<mapSize.width();
    // qDebug()<<panelWidth;

    this->resize(panelWidth, panelHeight);
    this->move(x, y);

    // this->raise(); // 保证在最前面

    // qDebug()<<pos();

    // for (int i = 0; i < ui->stackedWidget->count(); ++i) {
    //     QWidget* page = ui->stackedWidget->widget(i);
    //     qDebug() << "Page" << i
    //              << "minSize:" << page->minimumSize()
    //              << "sizeHint:" << page->sizeHint();
    // }


}

void StackPanel::togglePanel()
{
    const int panelWidth = ui->panelBodyWidget->width();
    const QPoint startPos = ui->panelBodyWidget->pos();
    QPoint endPos;
    //qDebug()<<is_visible;
    if (!is_visible) {
        // slide out
        endPos = startPos + QPoint(panelWidth, 0);
    } else {
        // slide in
        endPos = startPos - QPoint(panelWidth , 0);
    }

    // qDebug()<<panelWidth;
    // qDebug()<<startPos;
    // qDebug()<<endPos;

    showAnimation->stop();
    showAnimation->setStartValue(startPos);
    showAnimation->setEndValue(endPos);
    showAnimation->start();

    // if(isVisible()) {
    //     hide();
    // }
    // else {
    //     show();
    // }
}

void StackPanel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int hitSize = 10;
        QRect leftEdge(0, 0, hitSize, height());
        QRect bottomEdge(0, height() - hitSize, width(), hitSize);
        QRect bottomLeftCorner(0, height() - hitSize, hitSize, hitSize);

        if (bottomLeftCorner.contains(event->pos())) {
            resizing = true;
            resizeDirection = BOTTOMLEFT;
        } else if (leftEdge.contains(event->pos())) {
            resizing = true;
            resizeDirection = LEFT;
        } else if (bottomEdge.contains(event->pos())) {
            resizing = true;
            resizeDirection = DOWN;
        }

        if (resizing) {
            dragStartPos = event->globalPos();
            originalRect = geometry();
        }
    }
}

void StackPanel::mouseMoveEvent(QMouseEvent *event)
{
    if (resizing) {
        // 获取 roomMap 的尺寸
        QWidget *mainWidget = parentWidget();
        QWidget *roomMap = mainWidget->findChild<QWidget*>("roomMap");
        QSize mapSize = roomMap->size();


        QPoint delta = event->globalPos() - dragStartPos;
        QRect newRect = originalRect;

        if (resizeDirection == LEFT || resizeDirection == BOTTOMLEFT) {
            newRect.setLeft(originalRect.left() + delta.x());
            widthFactor = 1.0 * newRect.width() / mapSize.width();
        }
        if (resizeDirection == DOWN || resizeDirection == BOTTOMLEFT) {
            newRect.setBottom(originalRect.bottom() + delta.y());
            heightFactor = 1.0 * newRect.height() / mapSize.height();
        }

        // 计算最大尺寸
        int maxWidth = mapSize.width() * 0.9;
        int maxHeight = mapSize.height() * 0.9;

        // 限制尺寸
        if (newRect.width() > maxWidth) {
            newRect.setWidth(maxWidth);
            widthFactor = 0.9;
        }
        if (newRect.height() > maxHeight) {
            newRect.setHeight(maxHeight);
            heightFactor = 0.9;
        }

        setGeometry(newRect);
        //resize(newRect.width(), newRect.height());
    }

}

void StackPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (resizing) {
        resizing = false;
    }
}

