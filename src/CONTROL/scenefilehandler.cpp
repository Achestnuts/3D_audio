#include "scenefilehandler.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

// 以下假设你的各个对象都提供了 toJson() 和 fromJson() 方法。
// 你需要在 WallRectItem、AudioSource 和 Listener 类中添加类似如下的接口：
//
// QJsonObject toJson() const;
// void fromJson(const QJsonObject &obj);
//
// 如果没有，也可以在 SceneFileHandler 中直接访问对象的公开字段，这里采用更干净的面向对象方法。

// 示例：若你未实现 toJson/fromJson，可以参考下面代码，再在各类中补充相应实现。

bool SceneFileHandler::saveScene(const QString &filename,
                                 const QList<WallRectItem*> &walls,
                                 const QList<AudioSource*> &audioSources,
                                 const Listener* listener,
                                 int gridSize)
{
    QJsonObject rootObj;
    rootObj["gridSize"] = gridSize;

    QJsonArray wallArray;
    for (WallRectItem* wall : walls) {
        QJsonObject wallObj;
        // 假设 WallRectItem 提供 toJson() 方法
        wallObj = wall->toJson();
        wallArray.append(wallObj);
    }
    rootObj["walls"] = wallArray;

    QJsonArray audioArray;
    for (AudioSource* audio : audioSources) {
        QJsonObject audioObj;
        // 假设 AudioSource 提供 toJson() 方法
        audioObj = audio->toJson();
        audioArray.append(audioObj);
    }
    rootObj["audioSources"] = audioArray;

    QJsonObject listenerObj;
    // 假设 Listener 提供 toJson() 方法
    listenerObj = listener->toJson();
    rootObj["listener"] = listenerObj;

    QJsonDocument doc(rootObj);

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot open file for writing:" << filename;
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

bool SceneFileHandler::loadScene(const QString &filename,
                                 QList<WallRectItem*> &walls,
                                 QList<AudioSource*> &audioSources,
                                 Listener* listener,
                                 int &gridSize)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file for reading:" << filename;
        return false;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Invalid JSON in file:" << filename;
        return false;
    }

    QJsonObject rootObj = doc.object();
    gridSize = rootObj["gridSize"].toInt();

    // 清空当前墙体列表（实际情况请根据对象管理器清理）
    for (WallRectItem* wall : walls) {
        wall->deleteLater();
    }
    walls.clear();

    QJsonArray wallArray = rootObj["walls"].toArray();
    for (const QJsonValue &val : wallArray) {
        QJsonObject wallObj = val.toObject();
        // 根据你的构造函数创建新的 WallRectItem 对象
        // 假设 WallRectItem 有个静态方法 createFromJson()
        WallRectItem* wall = WallRectItem::createFromJson(wallObj);
        if (wall)
            walls.append(wall);
    }

    // 清空当前音源列表
    for (AudioSource* audio : audioSources) {
        audio->deleteLater();
    }
    audioSources.clear();

    QJsonArray audioArray = rootObj["audioSources"].toArray();
    for (const QJsonValue &val : audioArray) {
        QJsonObject audioObj = val.toObject();
        // 假设 AudioSource 有个静态方法 createFromJson()
        AudioSource* audio = AudioSource::createFromJson(audioObj);
        if (audio)
            audioSources.append(audio);
    }

    // 更新 Listener
    QJsonObject listenerObj = rootObj["listener"].toObject();
    if (listener) {
        listener->fromJson(listenerObj);
    } else {
        qWarning() << "Listener pointer is null";
    }

    emit sceneLoaded();
    return true;
}
