//
// Created by csobe on 2026-10-09.
//

#include "Bezier.h"

#include <cmath>
namespace CMPUT350 {

Bezier::Bezier(const std::vector<CMPUT350::Point2D> &pts) : pts(pts) {

}

void FindSeg(size_t pt_count, float &t, int &idx) {
    size_t seg_count = (pt_count - 1) / 3;
    int cur_seg = static_cast<int>(std::floor(t));
    if (cur_seg == seg_count) {
        cur_seg--;
    }

    t = t - cur_seg;
    idx = cur_seg * 3;

}

Point2D Bezier::GetPoint(float t) const {
    int idx;
    FindSeg(size(pts), t, idx);

    float k = (1 - t);

    float b1 = k * k * k;
    float b2 = k * k * 3 * t;
    float b3 = k * 3 * t * t;
    float b4 = t * t * t;

    Point2D bezier_pt = pts[idx] * b1 + pts[idx + 1] * b2 + pts[idx + 2] * b3 + pts[idx + 3] * b4;

    return bezier_pt;
}

Point2D Bezier::GetSlope(float t) const {
    int idx;
    FindSeg(size(pts), t, idx);

    float k = (1 - t);

    float b1 = 3 * k * k;
    float b2 = 6 * k * t;
    float b3 = 3 * t * t;

    Point2D bezier_slope = b1 * (pts[idx + 1] - pts[idx]) + b2 * (pts[idx + 2] - pts[idx + 1])  + b3 * (pts[idx + 3] - pts[idx + 2]);

    return bezier_slope;

}

static Point2D GetPoint(const std::vector<Point2D> &pts, float t) {
    int idx;
    FindSeg(size(pts), t, idx);

    float k = (1 - t);

    float b1 = k * k * k;
    float b2 = k * k * 3 * t;
    float b3 = k * 3 * t * t;
    float b4 = t * t * t;

    Point2D bezier_pt = pts[idx] * b1 + pts[idx + 1] * b2 + pts[idx + 2] * b3 + pts[idx + 3] * b4;

    return bezier_pt;
}
static Point2D GetSlope(const std::vector<Point2D> &pts, float t) {
    int idx;
    FindSeg(size(pts), t, idx);

    float k = (1 - t);

    float b1 = 3 * k * k;
    float b2 = 6 * k * t;
    float b3 = 3 * t * t;

    Point2D bezier_slope = b1 * (pts[idx + 1] - pts[idx]) + b2 * (pts[idx + 2] - pts[idx + 1])  + b3 * (pts[idx + 3] - pts[idx + 2]);

    return bezier_slope;
}

}
