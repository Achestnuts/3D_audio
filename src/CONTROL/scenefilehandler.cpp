#include "scenefilehandler.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <wallrectitem.h>
#include <draggablesource.h>

SceneFileHandler::SceneFileHandler(QObject *parent) {

}

bool SceneFileHandler::saveScene(const QString &filename,
                                 const std::list<std::shared_ptr<WallRectItem>> &walls,
                                 const std::list<std::shared_ptr<DraggableSource>> &sources,
                                 float gridSize)
{
    QJsonObject rootObj;
    rootObj["gridSize"] = gridSize;

    QJsonArray wallArray;
    for (auto wall : walls) {
        QJsonObject wallObj;
        // WallRectItem 提供 toJson() 方法
        wallObj = wall->toJson();
        wallArray.append(wallObj);
    }
    rootObj["walls"] = wallArray;

    QJsonArray sourceArray;
    for (auto source : sources) {
        QJsonObject sourceObj;
        // WallRectItem 提供 toJson() 方法
        sourceObj = source->toJson();
        sourceArray.append(sourceObj);
    }
    rootObj["sources"] = sourceArray;


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
                                 std::list<std::shared_ptr<WallRectItem>> &walls,
                                 std::list<std::shared_ptr<DraggableSource>> &sources,
                                 float &gridSize)
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
    gridSize = rootObj["gridSize"].toDouble();

    QJsonArray wallArray = rootObj["walls"].toArray();
    for (const QJsonValue &val : wallArray) {
        QJsonObject wallObj = val.toObject();

        std::shared_ptr<WallRectItem> wall = WallRectItem::createFromJson(wallObj);
        if (wall)
            walls.push_back(wall);
    }

    QJsonArray sourceArray = rootObj["sources"].toArray();
    for (const QJsonValue &val : sourceArray) {
        QJsonObject sourceObj = val.toObject();

        std::shared_ptr<DraggableSource> source = DraggableSource::createFromJson(sourceObj);
        if (source)
            sources.push_back(source);
    }


    // emit sceneLoaded();
    qDebug()<<"load work is over";
    return true;
}
