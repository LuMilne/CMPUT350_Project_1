#include "DrawContext.h"

#include <cmath>

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {}

void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {}

void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(c.r, c.g, c.b));
    circle.setPosition({p.x, p.y});
    circle.setOrigin({radius, radius});
    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rect({r.width, r.height});
    rect.setFillColor(sf::Color(c.r, c.g, c.b));
    rect.setPosition({r.topLeft.x, r.topLeft.y});
    mWindow->draw(rect);
}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {}

/**
 * @brief Draws a line between two points with a specified width and color.
 *
 * @param from The starting point of the line (Point2D).
 * @param to The ending point of the line (Point2D).
 * @param width The width of the line in pixels.
 * @param c The color of the line, specified as an RGBColor object.
 *
 * This function calculates the distance and angle between the two points
 * and uses a polygone shape to represent the line. The line is drawn
 * relative to the world offset and rendered onto the associated window.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    float top_point = std::min(to.y, from.y);
    float length = std::abs(to.y - from.y);

    sf::RectangleShape rect({width, length});
    rect.setPosition({from.x, top_point});
    rect.setFillColor(sf::Color(c.r, c.g, c.b));
    mWindow->draw(rect);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

void DrawContext::SetContextOffset(Point2D p) {
    offset = p;
}

void DrawContext::SetContextRotation(float rot) {
    rotation = rot;
}

Point2D DrawContext::Transform(Point2D p) {
    const Point2D x_transformed(std::cos(rotation), -std::sin(rotation));
    const Point2D y_transformed(std::sin(rotation), std::cos(rotation));

    Point2D result(x_transformed.Dot(p), y_transformed.Dot(p));
    return result + offset;
}

Point2D DrawContext::ReverseTransform(Point2D p) {
    p -= offset;
    const Point2D x_transformed(std::cos(rotation), std::sin(rotation));
    const Point2D y_transformed(-std::sin(rotation), std::cos(rotation));
    Point2D result(x_transformed.Dot(p), y_transformed.Dot(p));

    return result;
}

// Rotates rectangle and computes new bounding box after rotation
Rect DrawContext::Transform(Rect r) {
    //Transform all 4 points and then build the bounding box
    Point2D tl_point = Transform(r.topLeft);
    Point2D bl_point = Transform(Point2D(r.topLeft.x, r.topLeft.y + r.height));
    Point2D tr_point = Transform(Point2D(r.topLeft.x + r.width, r.topLeft.y));
    Point2D br_point = Transform(Point2D(r.topLeft.x + r.width, r.topLeft.y + r.height));

    //Makes a new rectangle of the transformed points
    Rect transformed(tl_point, br_point);

    //Ensures that we have all 4 corners in box
    transformed |= bl_point;
    transformed |= tr_point;

    return transformed;
}

}  // namespace CMPUT350
