
class WallManager;
#ifndef WALLRECTITEM_H
#define WALLRECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QMutex>
#include <QReadWriteLock>
#include <occlusionfilter.h>

#define GridSize 50

class AudioManager;

class WallRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 }; // 自定义类型

    explicit WallRectItem(const QRectF rect,  QGraphicsItem *parent = nullptr);
    ~WallRectItem();
    int type() const override { return Type; }

    // 设置吸附阈值
    void setSnapThreshold(float threshold);
    float snapThreshold() const;

    // 允许拖拽大小/位置
    void setResizable(bool resizable);
    bool isResizable() const;
    void snapToGrid(int gridSize);
    void updateLocation(const QPointF & newPos);
    void initMenu();

    float leftTopX, leftTopY;
    float width, height;

    OcclusionFilter filter;

    QJsonObject toJson() const;
    static std::shared_ptr<WallRectItem> createFromJson(const QJsonObject &obj);

signals:
    void itemSelected(WallRectItem* wall);
    void needUpdateEffect();

protected:
    // 鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    // itemChange: 在位置/大小变化后做一些处理（可放吸附逻辑）
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    enum ResizeMode {
        NoResize,
        ResizeLeft,
        ResizeRight,
        ResizeTop,
        ResizeBottom,
        ResizeTopLeft,
        ResizeTopRight,
        ResizeBottomLeft,
        ResizeBottomRight
    };

    // 根据鼠标点判断正在拖拽哪一条边或角
    ResizeMode hitTest(const QPointF &pos) const;
    void resizeItem(const QPointF &pos);

    std::shared_ptr<QReadWriteLock> mutex = nullptr; // 来自管理器的读写锁

private:
    float m_snapThreshold;
    bool m_resizable;

    ResizeMode m_resizeMode;
    QPointF m_pressPos;       // 记录按下时鼠标在本地坐标
    QRectF  m_pressRect;      // 记录按下时矩形

    QMenu* menu;

};

#endif // WALLRECTITEM_H
