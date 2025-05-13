#include "xwidget.h"
#include "ui_xwidget.h"
#include <QFile>
#include <QHoverEvent>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QLineEdit>
#include <QScrollBar>
#include <QPropertyAnimation>


XWidget::XWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::XWidget)
{
    qDebug()<<"prepare store point";
    qApp->setProperty("MainXWidget", QVariant::fromValue(std::shared_ptr<XWidget>(this))); // 存储指针
qDebug()<<"finish store point";
    setWindowFlags(Qt::FramelessWindowHint);    // 隐藏标题栏（无边框）
    setAttribute(Qt::WA_StyledBackground);      // 启用样式背景绘制
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明
    setAttribute(Qt::WA_Hover);                 // 启动鼠标悬浮追踪
qDebug()<<"finish set";
    m_bIsPressed = false;
    m_bIsResizing = false;
    m_bIsDoublePressed = false;
    m_direction = NONE;

    qDebug()<<"prepare all setup";
    ui->setupUi(this);

    // if (ui->roomMap) {
    //     roomMap = new RoomMap(ui->contentWidget);
    //     qApp->setProperty("RoomMap", QVariant::fromValue(roomMap)); // 存储指针
    //     QGraphicsView *graphicsView = ui->roomMap;
    //     roomMap->setWindowTitle(graphicsView->windowTitle());
    //     roomMap->setObjectName(graphicsView->objectName());
    //     roomMap->setSizePolicy(graphicsView->sizePolicy());
    //     ui->contentWidgetLayout->replaceWidget(ui->roomMap, roomMap);
    //     ui->roomMap = roomMap;
    //     delete graphicsView;
    // }

    // QFile xWidgetStyleSheet(":/qss/qss/xwidget.qss");
    // xWidgetStyleSheet.open(QIODevice::ReadOnly);
    // setStyleSheet(QString::fromUtf8(xWidgetStyleSheet.readAll()));

    qDebug()<<"all setup";

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->pushButtonMax, &QPushButton::clicked, this, &XWidget::maximizeWidget);
    connect(ui->pushButtonRestore, &QPushButton::clicked, this, &XWidget::restoreWidget);
    connect(ui->pushButtonMin, &QPushButton::clicked, this, &QWidget::showMinimized);

    //AudioManager* audioManager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
    // ui->publicParameterPanel->ui->gridMeterEdit->setText(QString::number(ui->roomMap->audioManager->gridMeter));
    // connect(ui->publicParameterPanel->ui->gridMeterEdit, &QLineEdit::editingFinished, [this]() {
    //     ui->roomMap->audioManager->gridMeter = this->ui->publicParameterPanel->ui->gridMeterEdit->text().toFloat();
    // });


    createShadow();

    restoreWidget();

    // 初始化面板
    stackPanel = new StackPanel(this);
    stackPanel->updatePosition();
    stackPanel->show();
    stackPanel->installEventFilter(this);

    connect(ui->toggleButton, &QPushButton::clicked, [this]() {
        stackPanel->is_visible = !stackPanel->isVisible();
        if (stackPanel->isVisible()) {
            stackPanel->raise();
            stackPanel->togglePanel();
            stackPanel->hide();
            ui->toggleButton->setText("<");
        } else {
            stackPanel->show();
            stackPanel->togglePanel();
            stackPanel->raise();
            ui->toggleButton->setText(">");
        }
    });

}

XWidget::~XWidget() {

}

// void XWidget::showEvent(QShowEvent *event)
// {
//     QWidget::showEvent(event);

//     static bool inited = false;
//     if (!inited) {
//         inited = true;

//         setWindowFlags(Qt::FramelessWindowHint);
//         setAttribute(Qt::WA_StyledBackground);
//         setAttribute(Qt::WA_TranslucentBackground);
//         setAttribute(Qt::WA_Hover);

//         show(); // 重新显示窗口以应用无边框
//     }
// }


void XWidget::animatePageSwitch(int from, int to)
{
    QWidget* fromWidget = stackPanel->ui->stackedWidget->widget(from);
    QWidget* toWidget   = stackPanel->ui->stackedWidget->widget(to);

    int w = stackPanel->width();

    // 初始位置：待切换页面在右侧或左侧
    toWidget->move(to > from ? w : -w, 0);
    toWidget->show();

    // 启用动画：当前页面滑出，目标页面滑入
    QPropertyAnimation* animFrom = new QPropertyAnimation(fromWidget, "pos");
    QPropertyAnimation* animTo   = new QPropertyAnimation(toWidget,   "pos");

    animFrom->setDuration(300);
    animTo->setDuration(300);

    animFrom->setStartValue(QPoint(0, 0));
    animFrom->setEndValue(QPoint(to > from ? -w : w, 0));

    animTo->setStartValue(QPoint(to > from ? w : -w, 0));
    animTo->setEndValue(QPoint(0, 0));

    animFrom->start(QAbstractAnimation::DeleteWhenStopped);
    animTo->start(QAbstractAnimation::DeleteWhenStopped);

    // 切换 stack index
    stackPanel->ui->stackedWidget->setCurrentIndex(to);
}


bool XWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == stackPanel && event->type() == QEvent::Wheel) {
        QWheelEvent* wheel = static_cast<QWheelEvent*>(event);

        int delta = wheel->angleDelta().y();
        if (delta == 0) return true;

        int current = stackPanel->ui->stackedWidget->currentIndex();
        int count = stackPanel->ui->stackedWidget->count();

        int nextIndex = current + (delta < 0 ? 1 : -1);
        nextIndex = std::clamp(nextIndex, 0, count - 1);

        if (nextIndex != current) {
            animatePageSwitch(current, nextIndex); // 切换动画函数
        }

        return true; // 已处理，不再向上传播
    }

    return QWidget::eventFilter(watched, event);
}


// void XWidget::updateSourceParameterWidget(DraggableSource* source) {
//     QMutex mutex;
//     QMutexLocker locker(&mutex);
//     if(ui->sourceParameterWidget) {
//         qDebug()<<"准备更新窗口";

//         // 获取原页面的索引
//         //int originalIndex = ui->stackedPanel->indexOf(ui->itemParameter);

//         // AudioManager* audioManager = qvariant_cast<AudioManager*>(qApp->property("AudioManager"));
//         // QWidget* widget = ui->itemParameter;
//         // SourceParameterWidget* itemParamter = new SourceParameterWidget(ui->contentWidget);

//         // itemParamter->setWindowTitle(widget->windowTitle());
//         // itemParamter->setObjectName(widget->objectName());
//         // itemParamter->setSizePolicy(widget->sizePolicy());

//         // //ui->sidePanleLayout->removeWidget(ui->itemParameter);

//         // ui->stackedPanel->insertWidget(originalIndex, itemParamter);
//         ui->sourceParameterWidget->disconnectBound();
//         ui->sourceParameterWidget->boundSource(source);




//         qDebug()<<"完成窗口更新";
//     }
// }
// void XWidget::updateParameterWidget(DraggableListener* source) {

// }
// void XWidget::updateParameterWidget(WallRectItem* source) {

// }

bool XWidget::event(QEvent *event)
{
    // 获取悬浮事件，转化为鼠标移动统一处理
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
        QMouseEvent mouseEvent(QEvent::MouseMove, hoverEvent->position(), hoverEvent->globalPosition(),
                               Qt::NoButton, Qt::NoButton, Qt::NoModifier);

        mouseMoveEvent(&mouseEvent);
    }

    if(stackPanel && stackPanel->isVisible()) {
        stackPanel->updatePosition();
    }

    return QWidget::event(event);
}

void XWidget::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
    setWindowTitle(windowTitle()); // 触发 titleChanged，stackPanel 已连接此信号
}

void XWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    setWindowTitle(windowTitle()); // 触发 titleChanged
}


void XWidget::mousePressEvent(QMouseEvent *event)
{
    // 检测是否按下左键
    if (event->button() == Qt::LeftButton) {
        m_bIsPressed = true;
        m_pressPoint = event->globalPosition();
        // if(event-> == QEvent::MouseButtonDblClick)
    }

    return QWidget::mousePressEvent(event);
}

void XWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bIsPressed) {
        if (m_bIsResizing) {
            // 计算调整尺寸
            m_movePoint = event->globalPosition() - m_pressPoint;
            m_pressPoint += m_movePoint;
        } else {
            // 全屏拖动
            if (!m_bIsDoublePressed && isWidgetSizeGreaterScreenSize()) {
                // setGeometry(QRect(400, 400, 600, 500));
                //setWindowState(Qt::WindowMaximized);
                restoreWidget();
                // 根据拖拽百分比移动窗口
                QPointF point(width() * ((double)(event->globalPosition().x())/QApplication::primaryScreen()->availableSize().width()),
                              height() * ((double)(event->globalPosition().y())/QApplication::primaryScreen()->availableSize().height()));

                move((event->globalPosition() - point.toPoint()).toPoint());

                m_pressPoint = event->globalPosition();
            }
            // 非全屏拖动
            else {
                QPointF point = event->globalPosition() - m_pressPoint;
                move((pos() + point).toPoint());

                m_pressPoint = event->globalPosition();
            }
        }
    }
    // 更新游标
    if (!isWidgetSizeGreaterScreenSize()) {
        updateRegion(event);
    }

    QWidget::mouseMoveEvent(event);
}

// 设置游标图形与拖拽方向
void XWidget::updateRegion(QMouseEvent *event)
{
    QRect mainRect = geometry();

    // 游标与窗口距离
    int marginTop = event->globalPosition().y() - mainRect.y();
    int marginBottom = mainRect.y() + mainRect.height() - event->globalPosition().y();
    int marginLeft = event->globalPosition().x() - mainRect.x();
    int marginRight = mainRect.x() + mainRect.width() - event->globalPosition().x();

    if (!m_bIsResizing) {
        if ( (marginRight >= MARGIN_MIN_SIZE && marginRight <= MARGIN_MAX_SIZE)
            && ((marginBottom <= MARGIN_MAX_SIZE) && marginBottom >= MARGIN_MIN_SIZE) ) {
            m_direction = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        } else if ( (marginTop >= MARGIN_MIN_SIZE && marginTop <= MARGIN_MAX_SIZE)
                   && (marginRight >= MARGIN_MIN_SIZE && marginRight <= MARGIN_MAX_SIZE)) {
            m_direction = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        } else if ( (marginLeft >= MARGIN_MIN_SIZE && marginLeft <= MARGIN_MAX_SIZE)
                   && (marginTop >= MARGIN_MIN_SIZE && marginTop <= MARGIN_MAX_SIZE) ) {
            m_direction = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        } else if ( (marginLeft >= MARGIN_MIN_SIZE && marginLeft <= MARGIN_MAX_SIZE)
                   && (marginBottom >= MARGIN_MIN_SIZE && marginBottom <= MARGIN_MAX_SIZE)) {
            m_direction = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        } else if (marginBottom <= MARGIN_MAX_SIZE && marginBottom >= MARGIN_MIN_SIZE) {
            m_direction = DOWN;
            setCursor(Qt::SizeVerCursor);
        } else if (marginLeft <= MARGIN_MAX_SIZE - 1 && marginLeft >= MARGIN_MIN_SIZE - 1) {
            m_direction = LEFT;
            setCursor(Qt::SizeHorCursor);
        } else if (marginRight <= MARGIN_MAX_SIZE && marginRight >= MARGIN_MIN_SIZE) {
            m_direction = RIGHT;
            setCursor(Qt::SizeHorCursor);
        } else if (marginTop <= MARGIN_MAX_SIZE && marginTop >= MARGIN_MIN_SIZE) {
            m_direction = UP;
            setCursor(Qt::SizeVerCursor);
        } else {
            if (!m_bIsPressed) {
                setCursor(Qt::ArrowCursor);
            }
        }
    }

    if (NONE != m_direction) {
        m_bIsResizing = true;
        resizeRegion(marginTop, marginBottom, marginLeft, marginRight);
    }
}

// 更新窗口
void XWidget::resizeRegion(int marginTop, int marginBottom,
                           int marginLeft, int marginRight)
{
    if (m_bIsPressed) {
        switch (m_direction) {
        case BOTTOMRIGHT:
        {
            QRect rect = geometry();
            rect.setBottomRight((rect.bottomRight() + m_movePoint).toPoint());
            setGeometry(rect);
        }
        break;
        case TOPRIGHT:
        {
            if (marginLeft > minimumWidth() && marginBottom > minimumHeight()) {
                QRect rect = geometry();
                rect.setTopRight((rect.topRight() + m_movePoint).toPoint());
                setGeometry(rect);
            }
        }
        break;
        case TOPLEFT:
        {
            if (marginRight > minimumWidth() && marginBottom > minimumHeight()) {
                QRect rect = geometry();
                rect.setTopLeft((rect.topLeft() + m_movePoint).toPoint());
                setGeometry(rect);
            }
        }
        break;
        case BOTTOMLEFT:
        {
            if (marginRight > minimumWidth() && marginTop> minimumHeight()) {
                QRect rect = geometry();
                rect.setBottomLeft((rect.bottomLeft() + m_movePoint).toPoint());
                setGeometry(rect);
            }
        }
        break;
        case RIGHT:
        {
            QRect rect = geometry();
            rect.setWidth(rect.width() + m_movePoint.x());
            setGeometry(rect);
        }
        break;
        case DOWN:
        {
            QRect rect = geometry();
            rect.setHeight(rect.height() + m_movePoint.y());
            setGeometry(rect);
        }
        break;
        case LEFT:
        {
            if (marginRight > minimumWidth()) {
                QRect rect = geometry();
                rect.setLeft(rect.x() + m_movePoint.x());
                setGeometry(rect);
            }
        }
        break;
        case UP:
        {
            if (marginBottom > minimumHeight()) {
                QRect rect = geometry();
                rect.setTop(rect.y() + m_movePoint.y());
                setGeometry(rect);
            }
        }
        break;
        default:
        {
        }
        break;
        }
    } else {
        m_bIsResizing = false;
        m_direction = NONE;
    }
}

void XWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bIsPressed = false;
        m_bIsResizing = false;
        m_bIsDoublePressed = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void XWidget::leaveEvent(QEvent *event)
{
    m_bIsPressed = false;
    m_bIsDoublePressed = false;
    m_bIsResizing = false;

    QWidget::leaveEvent(event);
}

void XWidget::createShadow()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setBlurRadius(20);
    this->setGraphicsEffect(shadowEffect);

}

void XWidget::maximizeWidget()
{
    ui->hSpacerMaxAndNor->changeSize(5, 20);
    ui->pushButtonRestore->show();
    ui->pushButtonMax->hide();
    ui->hSpacerMinAndMax->changeSize(0, 0);
    ui->XWidgetLayout->setContentsMargins(0, 0, 0, 0);

    showMaximized();
}

void XWidget::restoreWidget()
{
    ui->hSpacerMaxAndNor->changeSize(0, 0);
    ui->pushButtonRestore->hide();
    ui->pushButtonMax->show();
    ui->hSpacerMinAndMax->changeSize(5,20);
    ui->XWidgetLayout->setContentsMargins(10, 10, 10, 10);

    showNormal();

    QRect rect = geometry();
    rect.setSize(QSize(600, 500));
    setGeometry(rect);
}

void XWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    // 检查是否是鼠标左键双击
    if (event->button() == Qt::LeftButton) {
        m_bIsDoublePressed = true;
        // 获取双击的坐标
        QPoint pos = event->pos();
        // 这里可以添加你的双击事件处理代码
        // 例如：打印双击位置
        qDebug() << "Double clicked at:" << pos;
        qDebug()<<"is double, and state is "<<windowState();
        if(isWidgetSizeGreaterScreenSize()) {
            restoreWidget();
        }
        else {
            maximizeWidget();
        }
    }

    // 调用父类的处理函数，确保其他双击事件也能被正确处理
    QWidget::mouseDoubleClickEvent(event);

};

bool XWidget::isWidgetSizeGreaterScreenSize() {
    // 获取QWidget的尺寸
    QSize widgetSize = this->size();

    // 获取QWidget所在屏幕的尺寸
    QScreen *screen = QApplication::screenAt(this->pos());
    if (screen) {
        QSize screenSize = screen->size();

        // 比较QWidget的尺寸和屏幕的尺寸
        return widgetSize.width() >= screenSize.width() && widgetSize.height() >= screenSize.height();
    }

    // 如果无法获取屏幕信息，返回false
    return false;
}




