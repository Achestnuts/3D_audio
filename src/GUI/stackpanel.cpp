#include "stackpanel.h"
#include "ui_stackpanel.h"

#include <QMainWindow>
#include <QApplication>
#include <QScreen>

StackPanel::StackPanel(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::StackPanel),
    animation(new QPropertyAnimation)
{
    ui->setupUi(this);
    // 关闭透明背景属性
    setAttribute(Qt::WA_TranslucentBackground, false);
    // // 设置子部件的背景样式，例如设置为不透明的白色背景
    // setStyleSheet("background-color: white;");

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    // connect(ui->toggleButton, &QPushButton::clicked, this, &StackPanel::togglePanel);

    animation->setTargetObject(ui->panelBodyWidget);
    animation->setPropertyName("pos");
    animation->setDuration(300);

    setMinimumSize(0, 0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    raise();
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
    QWidget *mainWidget = parentWidget(); // 通常是 XWidget
    if (!mainWidget) return;

    QWidget *roomMap = mainWidget->findChild<QWidget*>("roomMap");
    if (!roomMap) return;

    setMinimumSize(0, 0);

    // 获取 roomMap 在 parent（XWidget）中的位置
    QPoint mapPos = roomMap->mapTo(mainWidget, QPoint(0, 0));
    QSize mapSize = roomMap->size();

    int panelWidth = mapSize.width() * 0.4;
    int panelHeight = mapSize.height() * 0.4;
    this->resize(panelWidth, panelHeight);

    // 计算面板的位置（位于 roomMap 内部右侧）
    int x = mainWidget->geometry().left() + mapPos.x() + mapSize.width() - panelWidth - 20;
    int y = mainWidget->geometry().top() + mapPos.y();
    qDebug()<<"some para";
    qDebug()<<x;
    qDebug()<<mainWidget->geometry().left();
    qDebug()<<mapPos.x();
    qDebug()<<mapSize.width();
    qDebug()<<panelWidth;
    qDebug() << "min width:" << this->minimumWidth() << ", min height:" << this->minimumHeight();

    this->move(x, y);

    this->raise(); // 保证在前
}

void StackPanel::togglePanel()
{
    const int panelWidth = ui->panelBodyWidget->width();
    const QPoint startPos = ui->panelBodyWidget->pos();
    QPoint endPos;

    if (isExpanded) {
        // slide out
        endPos = QPoint(width(), 0);
    } else {
        // slide in
        endPos = QPoint(width() - panelWidth, 0);
    }

    animation->stop();
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->start();

    isExpanded = !isExpanded;
}
