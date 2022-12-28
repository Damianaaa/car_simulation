#ifndef ENGINE_PHYSICS_COLLISION_MODEL_HDR_AREA_DESCRIPTION_H
#define ENGINE_PHYSICS_COLLISION_MODEL_HDR_AREA_DESCRIPTION_H

#include <iostream>
#include <array>
#include <optional>
#include <variant>
#include <SFML/Graphics.hpp>

namespace physics
{
class LineDescription;
class CircleDescription;
class RectangleDescription;
using Area = std::variant<LineDescription, CircleDescription, RectangleDescription>;

struct LineDescription
{
    LineDescription(const sf::Vector2f start_point, const sf::Vector2f end_point):
        start_point{start_point}, end_point{end_point}, direction_vector{end_point - start_point}
    {
        calculateCoefficients();
    }
    LineDescription() = delete;

    std::optional<sf::Vector2f> getIntersectionPoint(const LineDescription& line) const;

    std::optional<sf::Vector2f> getIntersectionPoint(const CircleDescription& circle) const;

    std::optional<sf::Vector2f> getIntersectionPoint(const RectangleDescription& rect) const;

    const sf::Vector2f start_point, end_point;
    const sf::Vector2f direction_vector;
    float coeff_a, coeff_b;

    void calculateCoefficients();
};

struct CircleDescription
{
    CircleDescription(const sf::Vector2f& center, const float r): center_point{center}, radius{r} {}
    CircleDescription() = delete;

    std::optional<sf::Vector2f> getIntersectionPoint(const LineDescription& line) const;

    const sf::Vector2f center_point;
    const float radius;
};

// Check for the perpendicularity? Creation safety should be improved. 
struct RectangleDescription
{
    RectangleDescription(const std::array<LineDescription, 4>&& lines): lines_{std::move(lines)} {}
    RectangleDescription() = delete;

    std::optional<sf::Vector2f> getIntersectionPoint(const LineDescription& line) const;

    const std::array<LineDescription, 4>& getLines() const { return lines_; }
    const std::array<LineDescription, 4> lines_;
};

}  // physics

#endif