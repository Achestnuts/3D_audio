#include "stackpanel.h"
#include "ui_stackpanel.h"

#include <QMainWindow>
#include <QApplication>
#include <QScreen>

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

    // connect(ui->toggleButton, &QPushButton::clicked, this, &StackPanel::togglePanel);

    showAnimation->setTargetObject(ui->panelBodyWidget);
    showAnimation->setPropertyName("pos");
    showAnimation->setDuration(300);

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
    if (index == -1)
        ui->stackedWidget->addWidget(widget);
    else
        ui->stackedWidget->insertWidget(index, widget);
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

    this->resize(panelWidth, panelHeight);
    this->move(x, y);

    this->raise(); // 保证在最前面

}

void StackPanel::togglePanel()
{
    const int panelWidth = ui->panelBodyWidget->width();
    const QPoint startPos = ui->panelBodyWidget->pos();
    QPoint endPos;
qDebug()<<is_visible;
    if (!is_visible) {
        // slide out
        endPos = startPos + QPoint(panelWidth, 0);
    } else {
        // slide in
        endPos = startPos - QPoint(panelWidth , 0);
    }

    qDebug()<<panelWidth;
    qDebug()<<startPos;
    qDebug()<<endPos;

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
