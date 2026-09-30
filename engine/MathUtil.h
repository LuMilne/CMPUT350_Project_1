#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <iostream>
#include <algorithm>

namespace CMPUT350 {

struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}
    double Distance(const Point2D &other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    Point2D operator+(const Point2D &other) const {
        return {x + other.x, y + other.y};
    }
    Point2D operator+(const float &other) const {
        return {x + other, y + other};
    }
    Point2D operator-(const Point2D &other) const {
        return {x - other.x, y - other.y};
    }
    Point2D operator-(const float &other) const {
        return {x - other, y - other};
    }
    Point2D operator*(const float &scalar) const {
        return {x * scalar, y * scalar};
    }
    Point2D &operator+=(const float &scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    Point2D &operator+=(const Point2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    //Theres no scalar for this one for some reason?
    Point2D &operator-=(const Point2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    bool operator==(const Point2D &other) const {
        return ((x == other.x) && (y == other.y));
    }
    Point2D &operator*=(const int &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Point2D &operator/=(const int &scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    float operator*(const Point2D &other) const {
        return Dot(other);
    }
    float Dot(Point2D b) const {
        return x * b.x + y * b.y;
    }
    static float Dot(Point2D a, Point2D b) {
        float dot = a.x * b.x + a.y * b.y;
        return dot;
    }
    static float Cross(Point2D a, Point2D b) {
        return (a.x * b.y) - (a.y * b.x);
    }
    void Normalize() {
        float dist = std::sqrt(x * x + y * y);
        if (dist != 0) {
            x /= dist;
            y /= dist;
        }
    }
};

static std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    // TODO: write this code
    return os;
}

static Point2D operator*(float number, const Point2D &rhs) {
    return {rhs.x * number, rhs.y * number};
}

struct Line {
    Point2D p1, p2;

    Line(Point2D p1 = {0, 0}, Point2D p2 = {0, 0}) : p1(p1), p2(p2) {}
    Line(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}

    float Length() const {
        return p1.Distance(p2);
    }

    //((a dot b)/(b dot b)) * b then add p1 to get the point
    //a = p1 to p, b = p1 to p2 (line)
    Point2D ClosestPoint(const Point2D &p) const {
        Point2D a = p - p1;
        Point2D b = p2 - p1;

        return ((a.Dot(b)/b.Dot(b)) * (b)) + p1;
    }

    //Checks if crossingPoint is both on line and other. If its on both than return true
    bool Crosses(Line other, Point2D &crossingPoint) const {
        if (p1.Distance(crossingPoint) + p2.Distance(crossingPoint) == p1.Distance(p2)
            && other.p1.Distance(crossingPoint) + other.p2.Distance(crossingPoint) == other.p1.Distance(other.p2))
        {
            return true;
        }
        return false;
    }
};

static std::ostream &operator<<(std::ostream &os, const Line &l) {
    // TODO: write this code
    return os;
}

struct Circle {
    Point2D center;
    float radius;

    Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}

    Circle(float x, float y, float r) : center(x, y), radius(r) {}
};

struct Rect {
    Point2D topLeft;
    float width, height;

    Rect(float left, float top, float width, float height)
        : topLeft(Point2D(left, top)), width(width), height(height) {}

    Rect(Point2D tl = {0, 0}, int w = 0, int h = 0) : topLeft(tl), width(w), height(h) {}

    // Creates bounding box around p1 and p2 with positive width/height
    Rect(Point2D p1, Point2D p2)
        : topLeft(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
          width(fabs(p1.x - p2.x)),
          height(fabs(p1.y - p2.y)) {}

    Rect(Point2D center, float radius)
        : topLeft(center.x - radius, center.y - radius), width(2 * radius), height(2 * radius) {}

    /*Build a new rect that contains both rects
     *Need: Top (highest x), Left (Left most y), width, height
     *height and width would be top - bottom and right - left
     *since origin is top left we scale downwards IMPORTANT
     */
    Rect &operator|=(const Rect &other) {
        float left = std::min(topLeft.x, other.topLeft.x);
        float top= std::min(topLeft.y, other.topLeft.y);
        float right = std::max(topLeft.x + width, other.topLeft.x + width);
        float bottom = std::max(topLeft.y + height, other.topLeft.y + height);

        width = right - left;
        height = bottom - top;

        topLeft = Point2D(left, top);
        return *this;
    }

    Rect &operator|=(const Point2D &other) {
        float left = std::min(topLeft.x, other.x);
        float top= std::min(topLeft.y, other.y);
        float right = std::max(topLeft.x + width, other.x + width);
        float bottom = std::max(topLeft.y + height, other.y + height);

        width = right - left;
        height = bottom - top;

        topLeft = Point2D(left, top);
        return *this;
    }
    Rect &operator|=(const Line &other) {
        float left = std::min({topLeft.x, other.p1.x, other.p2.x});
        float top= std::min({topLeft.y, other.p1.y, other.p2.y});
        float right = std::max({topLeft.x + width, other.p1.x + width, other.p2.x + width});
        float bottom = std::max({topLeft.y + height, other.p1.y + height, other.p2.y + height});

        width = right - left;
        height = bottom - top;

        topLeft = Point2D(left, top);
        return *this;
    }
    Rect &operator&=(const Rect &other) {
        float left = std::max(topLeft.x, other.topLeft.x);
        float top= std::max(topLeft.y, other.topLeft.y);
        float right = std::min(topLeft.x + width, other.topLeft.x + width);
        float bottom = std::min(topLeft.y + height, other.topLeft.y + height);

        width = right - left;
        height = bottom - top;

        topLeft = Point2D(left, top);
        return *this;
    }
    Rect &operator+=(const Point2D &other) {
        topLeft += other;
        return *this;
    }
    Rect operator+(const Point2D &other) const {
        Rect temp_rect = *this;
        temp_rect += other;
        return temp_rect;
    }
    void Inset(int inset) {
        topLeft.x += inset;
        topLeft.y += inset;
        width -= inset;
        height -= inset;
    }

    bool IsInside(const Point2D &p) const {
        if (topLeft.x <= p.x && topLeft.y <= p.y
            && topLeft.x + width >= p.x && topLeft.y + height >= p.y)
        {
            return true;
        }
        return false;
    }
};

static std::ostream &operator<<(std::ostream &os, const Rect &l) {
    // TODO: write this code
    return os;
}

}  // namespace CMPUT350

#endif  // MATHUTIL_H
