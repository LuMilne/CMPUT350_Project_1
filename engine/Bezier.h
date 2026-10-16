//
// Created by csobe on 2026-10-09.
//

#ifndef PROJECT1_BEZIER_H
#define PROJECT1_BEZIER_H
#include <vector>
#include "MathUtil.h"

namespace CMPUT350 {

class Bezier {
public:
    Bezier(const std::vector<Point2D> &pts);

    Point2D GetPoint(float t) const;
    Point2D GetSlope(float t) const;

    static Point2D GetPoint(const std::vector<Point2D> &pts, float t);
    static Point2D GetSlope(const std::vector<Point2D> &pts, float t);

private:
    Point2D bezier_point;
    std::vector<Point2D> pts;
};
}

#endif  // PROJECT1_BEZIER_H
