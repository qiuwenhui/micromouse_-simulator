#include "Sensor.h"

#include <QVector>
#include <QtMath>

#include <algorithm>

#include "Assert.h"
#include "GeometryUtilities.h"
#include "Param.h"

namespace mms {

Sensor::Sensor() :
    m_range(Distance()),
    m_halfWidth(Angle()),
    m_initialPosition(Coordinate()),
    m_initialDirection(Angle()) {
}

Sensor::Sensor(
    const Distance& radius,
    const Distance& range,
    const Angle& halfWidth,
    const Coordinate& position,
    const Angle& direction,
    const Maze& maze) :
    m_range(range),
    m_halfWidth(halfWidth),
    m_initialPosition(position),
    m_initialDirection(direction),
    m_numberOfViewEdgePoints(8) {

    // Create the polygon for the body of the sensor
    m_initialPolygon = GeometryUtilities::createCirclePolygon(
        position,
        radius,
        8  // number of vertices
    );

    // Create the polygon for the view of the sensor
    QVector<Coordinate> view;
    view.push_back(position);
    for (double i = -1; i <= 1; i += 2.0 / (m_numberOfViewEdgePoints - 1)) {
        view.push_back(Coordinate::Polar(range, (halfWidth * i) + direction) + position);
    }
    m_initialViewPolygon = Polygon(view);

    // Initialize the sensor reading
    updateReading(m_initialPosition, m_initialDirection, maze);
}

const Coordinate& Sensor::getInitialPosition() const {
    return m_initialPosition;
}

const Angle& Sensor::getInitialDirection() const {
    return m_initialDirection;
}

const Polygon& Sensor::getInitialPolygon() const {
    return m_initialPolygon;
}

const Polygon& Sensor::getInitialViewPolygon() const {
    return m_initialViewPolygon;
}

Polygon Sensor::getCurrentViewPolygon(
        const Coordinate& currentPosition,
        const Angle& currentDirection,
        const Maze& maze) const {
    return getViewPolygon(currentPosition, currentDirection, maze);
}

double Sensor::read() const {
    return m_currentReading;
}

void Sensor::updateReading(
        const Coordinate& currentPosition,
        const Angle& currentDirection,
        const Maze& maze) {

    m_currentReading = std::max(
        0.0,
        1.0 - 
            getViewPolygon(currentPosition, currentDirection, maze)
                .area().getMetersSquared() /
            getInitialViewPolygon().area().getMetersSquared());

    ASSERT_LE(0.0, m_currentReading);
    ASSERT_LE(m_currentReading, 1.0);
}

Polygon Sensor::getViewPolygon(
        const Coordinate& currentPosition,
        const Angle& currentDirection,
        const Maze& maze) const {

    // TODO: MACK - this can be deduped with getCurrentViewPolygon

    // Calling this function causes triangulation of a polygon

    static Distance halfWallWidth = Distance::Meters(P()->wallWidth() / 2.0);
    static Distance tileLength = Distance::Meters(P()->wallLength() + P()->wallWidth());

    QVector<Coordinate> polygon {currentPosition};

    for (double i = -1; i <= 1; i += 2.0 / (m_numberOfViewEdgePoints - 1)) {
        polygon.push_back(
            GeometryUtilities::castRay(
                currentPosition,
                currentPosition + Coordinate::Polar(
                    m_range,
                    currentDirection + (m_halfWidth * i)
                ),
                maze,
                halfWallWidth,
                tileLength
            )
        );
    }

    return Polygon(polygon);
}

} // namespace mms
