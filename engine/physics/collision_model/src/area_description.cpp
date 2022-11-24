#include "engine/math/hdr/algebra.h"
#include "engine/math/hdr/mathematical_analysis.h"
#include "engine/physics/collision_model/hdr/area_description.h"

namespace physics
{

template<class T, class U>
std::optional<sf::Vector2f> getIntersectionPoint(const T& line_1, const U& line_2)
{
    std::cerr << "Calling not defined templated version, check if types are casted correctly\n";
    return std::nullopt;
}

/**
     * @brief Get the intersection point of two lines
     * @note Equations from: https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
     * 
     * @param line 
     * @return std::optional<sf::Vector2f> Intersection point or std::nullopt if id does not exist
     */
template<>
std::optional<sf::Vector2f> getIntersectionPoint<LineDescription, LineDescription>(const LineDescription& line_1, const LineDescription& line_2)
{
    const float denominator = math::crossProduct(line_2.direction_vector, line_1.direction_vector);
    if (denominator == 0)
        return std::nullopt; 
    const float scalar_1 = math::crossProduct((line_2.start_point - line_1.start_point), line_1.direction_vector)
        / denominator;
    const float scalar_2 = math::crossProduct((line_2.start_point - line_1.start_point), line_2.direction_vector) 
        / denominator;
    if ((scalar_1 >= 0 && scalar_1 <= 1) && (scalar_1 >= 0 && scalar_1 <= 1))
    {
        return line_1.start_point + scalar_2 * line_1.direction_vector;
    }
    return std::nullopt;
}

template<>
std::optional<sf::Vector2f> getIntersectionPoint<LineDescription, RectangleDescription>(const LineDescription& line, const RectangleDescription& rectangle)
{
    std::vector<sf::Vector2f> intersection_points{};
    for (const auto& rec_line: rectangle.getLines())
    {
        const auto intersection_point = getIntersectionPoint(line, rec_line);
        if (intersection_point.has_value())
            intersection_points.push_back(intersection_point.value());
    }
    if (intersection_points.size() > 0)
        return math::getClosestPoint(line.start_point, intersection_points);
    return std::nullopt;
}

/**
 * @brief Get the Intersection Point of line and circle
 * 
 * @note To calculate intersection points for the line and circle we have to solve the quadratic quadratic equation in the form:
 * coeff_quad_a * x ^ 2 + coeff_quad_b * x + coeff_quad_c = 0
 * where:
 * coeff_quad_a = (1 - coeff_a^2)
 * coeff_quad_b = (2 * coeff_a * (coeff_b - center.y) - (2 * center.x))
 * coeff_quad_c = center.x^2 + (coeff_b - center.y)^2 - radius^2
 * 
 * @param circle 
 * @return std::optional<sf::Vector2f> 
 */
template<>
std::optional<sf::Vector2f> getIntersectionPoint<LineDescription, CircleDescription>(const LineDescription& line, const CircleDescription& circle)
{
    std::vector<sf::Vector2f> intersection_points{};
    const float coeff_quad_a = 1 + pow(line.coeff_a, 2);
    const float coeff_quad_b = 2 * line.coeff_a * (line.coeff_b - circle.center_point.y) - (2 * circle.center_point.x);
    const float coeff_quad_c = pow(circle.center_point.x, 2) + pow(line.coeff_b - circle.center_point.y, 2) - pow(circle.radius, 2);
    const auto solutions_x = math::getQuadraticEquationSolutions(coeff_quad_a, coeff_quad_b, coeff_quad_c);
    for (const float x: solutions_x)
    {
        const float coeff = (x - line.start_point.x) / line.direction_vector.x;
        if (coeff >= 0 && coeff <= 1)
        {                
            const float y = line.coeff_a * x + line.coeff_b;
            intersection_points.push_back({x, y});
        }
    }

    if (intersection_points.size() > 0)
        return math::getClosestPoint(line.start_point, intersection_points);
    return std::nullopt;
}

template<class T>
std::optional<sf::Vector2f> getIntersectionPoint(const T& other_type, const LineDescription& line)
{
    return getIntersectionPoint<LineDescription, T>(line, other_type);
}

void LineDescription::calculateCoefficients()
{
    coeff_a = direction_vector.x / direction_vector.y;
    coeff_b = start_point.y - (coeff_a * start_point.x);
}

std::optional<sf::Vector2f> LineDescription::getIntersectionPoint(const LineDescription& line) const
{
    return ::physics::getIntersectionPoint(*this, line);
}

std::optional<sf::Vector2f> LineDescription::getIntersectionPoint(const CircleDescription& circle) const
{
    return ::physics::getIntersectionPoint(*this, circle);
}

std::optional<sf::Vector2f> LineDescription::getIntersectionPoint(const RectangleDescription& rect) const
{
    return ::physics::getIntersectionPoint(*this, rect);
}

std::optional<sf::Vector2f> CircleDescription::getIntersectionPoint(const LineDescription& line) const
{
    return ::physics::getIntersectionPoint(*this, line);
}

std::optional<sf::Vector2f> RectangleDescription::getIntersectionPoint(const LineDescription& line) const
{
    return ::physics::getIntersectionPoint(*this, line);
}


}  // physics