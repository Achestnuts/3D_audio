#ifndef PARAMETERCALCULATIONENGINE_H
#define PARAMETERCALCULATIONENGINE_H

#include "audiosource.h"
#include "listener.h"
#include "wallrectitem.h"

#include <QMutex>
#include <QPointF>
#include <list>

// typedef struct {
//     float x;
//     float y;
// } QPointF;

struct WallLineSegment {
    QPointF frontEnd, backEnd;
    float distance;

    float getFront() {
        return frontEnd.y() == backEnd.y() ? frontEnd.x() : frontEnd.y();
    }

    float getBack() {
        return frontEnd.y() == backEnd.y() ? backEnd.x() : backEnd.y();
    }

    float getLength() {
        return frontEnd.y() == backEnd.y() ? backEnd.x() - frontEnd.x() : backEnd.y() - frontEnd.y();
    }

    WallLineSegment cutDownTo(float newFrontEnd) {
        WallLineSegment cuttedLine = WallLineSegment({frontEnd, backEnd, distance});
        frontEnd.y() == backEnd.y() ? cuttedLine.backEnd.setX(newFrontEnd) : cuttedLine.backEnd.setY(newFrontEnd);
        frontEnd.y() == backEnd.y() ? frontEnd.setX(newFrontEnd) : frontEnd.setY(newFrontEnd);
        return cuttedLine;
    }

    QPointF getNormal() {
        return frontEnd.y() == backEnd.y() ? QPointF(0.0, 1.0) : QPointF(1.0, 0.0);
    }

    QPointF getMidPoint() {
        return {(frontEnd.x() + backEnd.x()) / 2, (frontEnd.y() + backEnd.y()) / 2};
    }

    bool operator < (WallLineSegment b)
    {
        return this->distance < b.distance;
    }

    bool operator > (WallLineSegment b)
    {
        return this->distance > b.distance;
    }

    // 检测相交
    bool existIntersection(const QPointF& p1, const QPointF& p2) const {
        QLineF path(p1, p2);
        QLineF wallEdge(frontEnd, backEnd);

        QPointF intersection;
        if (path.intersects(wallEdge, &intersection) == QLineF::BoundedIntersection)
            return true;
        else {
            return false;
        }
    }

};



class ParameterCalculationEngine
{
public:
    ParameterCalculationEngine();
    static std::list<WallLineSegment> lineSplit(std::list<WallLineSegment> &walls);
    static void estimateQuarterAreaAndRadianAndReflection(
        QPointF source,
        const std::list<WallLineSegment> &walls,
        double* quarterArea, double* quarterRadian, QPointF* quarterReflection
        );
    static float calculateEffectParameter(
        std::shared_ptr<AudioSource> source,
        const Listener* listener,
        const std::unordered_map<ALuint, WallRectItem*> &walls,
        float gridMeter,
        float *estimateRoomSize, QPointF *totalReflection
        );


};

#endif // PARAMETERCALCULATIONENGINE_H
