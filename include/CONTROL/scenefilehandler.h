#ifndef SCENEFILEHANDLER_H
#define SCENEFILEHANDLER_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

// 前向声明各个场景对象类
class WallRectItem;
class DraggableSource;
class Listener;

class SceneFileHandler : public QObject
{
    Q_OBJECT
public:
    explicit SceneFileHandler(QObject *parent = nullptr);

    // 保存场景到指定文件
    bool saveScene(const QString &filename,
                          const std::list<std::shared_ptr<WallRectItem>> &walls,
                          const std::list<std::shared_ptr<DraggableSource>> &sources,
                          float gridSize);

    // 读取场景文件并生成各对象
    // 返回 true 表示读取成功，并利用输出参数加载到各个容器中
    bool loadScene(const QString &filename,
                          std::list<std::shared_ptr<WallRectItem>> &walls,
                          std::list<std::shared_ptr<DraggableSource>> &sources,
                          float &gridSize);

signals:
    void sceneLoaded();

};

#endif // SCENEFILEHANDLER_H
