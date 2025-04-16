#include "parametercalculationengine.h"
#include "listener.h"

ParameterCalculationEngine::ParameterCalculationEngine() {}


std::list<WallLineSegment> ParameterCalculationEngine::lineSplit(std::list<WallLineSegment> & walls) {
    QMutex mutex;
    QMutexLocker locker(&mutex);
    // 先将墙体线段按距离升序排序
    // std::sort(walls.begin(), walls.end(), [](WallLineSegment a, WallLineSegment b){
    //     return a.distance <= b.distance;
    // });
    walls.sort();
    //qDebug()<<walls.size()<<"walls need be splited";
    // 返回的墙体序列
    std::list<WallLineSegment> splitedWalls;

    for(auto wall : walls) {

        bool finishInsert = false;

        for(auto it = splitedWalls.begin(); it != splitedWalls.end(); it++) {
            auto splitedWall = *it;
            // 后端点小于前端点，全部放入
            if(wall.getBack() <= splitedWall.getFront()) {
                splitedWalls.insert(it, wall);
                finishInsert = true;
            }
            // 先将可放入的截下，再往后继续找
            else {
                splitedWalls.insert(it, wall.cutDownTo(splitedWall.getFront()));
            }
        }

        if(!finishInsert) {
            finishInsert = true;
            splitedWalls.push_back(wall);
        }

    }
    //qDebug()<<splitedWalls.size()<<"walls were splited";
    return splitedWalls;
}

// 计算向量点积
float dotProduct(float x1, float y1, float x2, float y2) {
    return x1 * x2 + y1 * y2;
}

// 计算向量的模
float magnitude(float x, float y) {
    return std::sqrt(x * x + y * y);
}

// 计算三角形面积的函数
float calculateTriangleArea(float x1, float y1, float x2, float y2, float x3, float y3) {
    return std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0;
}

// 计算点 A 对应的角度的函数
double calculateAngleAtPointA(float x1, float y1, float x2, float y2, float x3, float y3) {
    // 向量 AB 和 AC
    float ABx = x2 - x1;
    float ABy = y2 - y1;
    float ACx = x3 - x1;
    float ACy = y3 - y1;

    // 计算点积和模
    float dot = dotProduct(ABx, ABy, ACx, ACy);
    float magAB = magnitude(ABx, ABy);
    float magAC = magnitude(ACx, ACy);

    // 计算夹角的余弦值
    float cosTheta = dot / (magAB * magAC);
    qDebug()<<"cos:"<<cosTheta;

    // 防止计算误差导致 acos 参数超出 [-1, 1] 范围
    if (cosTheta > 1.0) cosTheta = 1.0;
    if (cosTheta < -1.0) cosTheta = -1.0;
    qDebug()<<"Theta"<<std::acos(cosTheta) *180 / M_PI;
    // 计算角度（弧度）
    return std::acos(cosTheta) *180 / M_PI;
}


// 计算点积
float dotProduct(QPointF a, QPointF b) {
    return a.x() * b.x() + a.y() * b.y();
}

// 计算反射向量
QPointF reflectVector(QPointF incident, QPointF normal) {
    float scalar = 2 * dotProduct(incident, normal);
    QPointF reflected = {
        incident.x() - scalar * normal.x(),
        incident.y() - scalar * normal.y()
    };
    return reflected;
}

// 计算权重，这里使用线段长度和距离的倒数作为权重
float calculateWeight(float segmentLength, float distanceToSource) {
    if (distanceToSource == 0) {
        distanceToSource = 1e-10; // 避免除以零
    }
    return segmentLength / distanceToSource;
}
void ParameterCalculationEngine::estimateQuarterAreaAndRadianAndReflection(
    QPointF source, const std::list<WallLineSegment> &walls,
    double *quarterArea, double *quarterRadian, QPointF* quarterReflection) {

    QMutex mutex;
    QMutexLocker locker(&mutex);

    *quarterReflection = {0, 0};
    float totalWeight = 0;
    *quarterArea = 0;
    *quarterRadian = 0;
    for(auto wall : walls) {
        double area, radian;
        area = calculateTriangleArea(
            source.x(), source.y(),
            wall.frontEnd.x(), wall.frontEnd.y(),
            wall.backEnd.x(), wall.backEnd.y()
            );
        *quarterArea += area;
        radian = calculateAngleAtPointA(
            source.x(), source.y(),
            wall.frontEnd.x(), wall.frontEnd.y(),
            wall.backEnd.x(), wall.backEnd.y()
            );
        *quarterRadian += radian;

        QPointF incident = {(wall.frontEnd.x() + wall.backEnd.x()) / 2 - source.x(), (wall.frontEnd.y() + wall.backEnd.y()) / 2 - source.y()};
        QPointF reflection = reflectVector(incident, wall.getNormal());
        float  weight = calculateWeight(wall.getLength(), wall.distance);
        quarterReflection->setX(quarterReflection->x() + reflection.x() * weight);
        quarterReflection->setY(quarterReflection->y() + reflection.y() * weight);
        totalWeight += weight;

        qDebug()<<wall.getFront()<<"end"<<wall.getBack();
        qDebug()<<"wall y at:"<<wall.frontEnd.y();
        qDebug()<<source.x()<<"and"<<source.y();
        qDebug()<<"Area:"<<area;
        qDebug()<<"Radian:"<<radian;
    }

    quarterReflection->setX(quarterReflection->x() / totalWeight);
    quarterReflection->setY(quarterReflection->y() / totalWeight);

    return ;
}

float ParameterCalculationEngine::calculateEffectParameter(
    std::shared_ptr<DraggableSource> source,
    const std::shared_ptr<Listener> listener,
    const std::unordered_map<ALuint, std::shared_ptr<WallRectItem>> &walls,
    float gridMeter,
    float *estimateRoomSize, QPointF *totalReflection
    ) {

    QMutex mutex;
    QMutexLocker locker(&mutex);
    // 获取声源位置
    float srcX = source->boundSource->posX / GridSize * gridMeter;
    float srcY = source->boundSource->posY / GridSize * gridMeter;
    QPointF sourcePoint = {srcX, srcY};
    QPointF listenerPoint = {listener->posX / GridSize * gridMeter, listener->posY / GridSize * gridMeter};

    double totalArea = 0;
    double totalRadian = 0;
    *totalReflection = {0.0, 0.0};
    int existWall = 0; // 几面方向有墙

    // 对于每个方向：Front, Back, Left, Right（定义在 AuxEffectSlot.h 中）
    for (int dir = 0; dir < 4; ++dir) {
        float minDistance = std::numeric_limits<float>::max();
        bool foundWall = false;

        double quarterArea = 0;
        double quarterRadian = 0;
        QPointF quarterReflection = {0.0, 0.0};

        std::list<WallLineSegment> needHandleWalls;

        // 遍历所有墙体
        for (auto wallPair : walls) {
            auto wall = wallPair.second;
            // 获取墙体在场景中的左上角坐标
            QPointF wallPos = wall->scenePos();
            float wallLeft = wallPos.x()  / GridSize * gridMeter;
            float wallTop = wallPos.y()  / GridSize * gridMeter;
            float wallWidth = wall->rect().width()  / GridSize * gridMeter;
            float wallHeight = wall->rect().height()  / GridSize * gridMeter;
            float wallRight = wallLeft + wallWidth;
            float wallBottom = wallTop + wallHeight;
            // qDebug()<<"source at:"<<srcX<<" "<<srcY;
            // qDebug()<<"wall x at:"<<wallLeft<<" "<<wallBottom;
            // qDebug()<<"wall y at:"<<wallLeft<<" "<<wallBottom;

            bool candidate = false;
            float distance = 0.0f;

            WallLineSegment needHandleWall;

            switch (dir) {
            case RightEffect:
                // 检查墙体的左边界是否在声源右侧，/*并且声源的 y 坐标在墙体上下范围内*/
                if (wallLeft >= srcX /*&& srcY >= wallTop && srcY <= wallBottom*/) {
                    distance = wallLeft - srcX;
                    candidate = true;
                    needHandleWall.frontEnd = {wallLeft, wallTop};
                    needHandleWall.backEnd = {wallLeft, wallBottom};
                    needHandleWall.distance = distance;
                }
                break;
            case LeftEffect:
                if (wallRight <= srcX /*&& srcY >= wallTop && srcY <= wallBottom*/) {
                    distance = srcX - wallRight;
                    candidate = true;
                    needHandleWall.frontEnd = {wallRight, wallTop};
                    needHandleWall.backEnd = {wallRight, wallBottom};
                    needHandleWall.distance = distance;
                }
                break;
            case FrontEffect: // 前方：假设向上
                if (wallBottom <= srcY /*&& srcX >= wallLeft && srcX <= wallRight*/) {
                    distance = srcY - wallBottom;
                    candidate = true;
                    needHandleWall.frontEnd = {wallLeft, wallBottom};
                    needHandleWall.backEnd = {wallRight, wallBottom};
                    needHandleWall.distance = distance;
                }
                break;
            case BackEffect: // 后方：假设向下
                if (wallTop >= srcY /*&& srcX >= wallLeft && srcX <= wallRight*/) {
                    distance = wallTop - srcY;
                    candidate = true;
                    needHandleWall.frontEnd = {wallLeft, wallTop};
                    needHandleWall.backEnd = {wallRight, wallTop};
                    needHandleWall.distance = distance;
                }
                break;
            default:
                break;
            }

            if (candidate) {
                //minDistance = distance;
                // 如果听者与声源的连线与墙体相交，就将墙体的过滤器加入到声源中
                if(needHandleWall.existIntersection(sourcePoint, listenerPoint)) {
                    source->boundSource->addFilter(&(wall->filter));
                }
                else {
                    source->boundSource->removeFilter(wall->filter.getFilterId());
                }
                needHandleWalls.push_back(needHandleWall);
                foundWall = true;
            }
        } // end walls loop

        if (foundWall) {
            existWall++;
            std::list<WallLineSegment> handledWalls = ParameterCalculationEngine::lineSplit(needHandleWalls);
            qDebug()<<"the dir is "<<dir;
            //qDebug()<<handledWalls.size()<<"walls were splited";
            ParameterCalculationEngine::estimateQuarterAreaAndRadianAndReflection(
                sourcePoint, handledWalls,
                &quarterArea, &quarterRadian, &quarterReflection
                );
            //qDebug() << "更新方向" << dir;
        } else {
            // 没有墙体，效果器接近无效
            //source->auxEffectSlots.resetEffect();
            //qDebug() << "方向" << dir << "未检测到墙体，效果置零";
        }

        totalArea += quarterArea;
        totalRadian += quarterRadian;
        totalReflection->setX(totalReflection->x() + quarterReflection.x());
        totalReflection->setY(totalReflection->y() + quarterReflection.y());
    }
    *estimateRoomSize = totalArea / totalRadian * 360.0;
    totalReflection->setX(totalReflection->x() / 4);
    totalReflection->setY(totalReflection->y() / 4);
    return existWall;
}



