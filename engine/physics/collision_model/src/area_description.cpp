#include "engine/math/hdr/algebra.h"
#include "engine/math/hdr/mathematical_analysis.h"
#include "engine/math/hdr/numerical_utilities.h"
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
     * Probably because of some missunderstanding it does not work in the end. Used different approach but may be needed in the future
     * 
     * @param line 
     * @return std::optional<sf::Vector2f> Intersection point or std::nullopt if id does not exist
     */
template<>
std::optional<sf::Vector2f> getIntersectionPoint<LineDescription, LineDescription>(const LineDescription& line_1, const LineDescription& line_2)
{
    const float a1 = line_1.end_point.y - line_1.start_point.y;
    const float b1 = line_1.start_point.x - line_1.end_point.x;
    const float c1 = a1 * line_1.start_point.x + b1 * line_1.start_point.y;

    const float a2 = line_2.end_point.y - line_2.start_point.y;
    const float b2 = line_2.start_point.x - line_2.end_point.x;
    const float c2 = a2 * line_2.start_point.x + b2 * line_2.start_point.y;

    const float determinant = a1 * b2 - a2 * b1;
    if (math::fEqual(determinant, 0.f)) 
    {
        // The lines are parallel
        return std::nullopt;
    } 
    else 
    {    
        sf::Vector2f intersection_point{(b2 * c1 - b1 * c2) / determinant, (a1 * c2 - a2 * c1) / determinant};
        if (math::checkBounds(intersection_point, line_1.start_point, line_1.end_point) && 
            math::checkBounds(intersection_point, line_2.start_point, line_2.end_point))
        {
            return intersection_point;
        }
        else
        { 
            return std::nullopt;
        }
    }
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
        if (math::fGEqual(coeff, 0.f) && math::fLEqual(coeff, 1.f))
        {                
            const float y = line.coeff_a * x + line.coeff_b;
            intersection_points.push_back({x, y});
        }
    }
    if (intersection_points.size() > 0)
    {
        return math::getClosestPoint(line.start_point, intersection_points);
    }
    return std::nullopt;
}

template<>
std::optional<sf::Vector2f> getIntersectionPoint<RectangleDescription, CircleDescription>(const RectangleDescription& rect, const CircleDescription& circle)
{
    std::vector<sf::Vector2f> intersection_points{};
    for (auto& line: rect.getLines())
    {
        const auto i_p = line.getIntersectionPoint(circle);
        if (i_p.has_value())
            intersection_points.push_back(i_p.value());
    }
    if (intersection_points.empty())
        return std::nullopt;
    return intersection_points.front();
}

template<>
std::optional<sf::Vector2f> getIntersectionPoint<RectangleDescription, RectangleDescription>(const RectangleDescription& rect_1, const RectangleDescription& rect_2)
{
    std::vector<sf::Vector2f> intersection_points{};
    for (const auto& line_1: rect_1.getLines())
    {
        for (auto& line_2: rect_2.getLines())
        {
            const auto i_p = line_1.getIntersectionPoint(line_2);
            if (i_p.has_value())
                intersection_points.push_back(i_p.value());
        }
    }
    if (intersection_points.empty())
        return std::nullopt;
    return intersection_points.front();
}

template<class T>
std::optional<sf::Vector2f> getIntersectionPoint(const T& other_type, const LineDescription& line)
{
    return getIntersectionPoint<LineDescription, T>(line, other_type);
}

template<>
std::optional<sf::Vector2f> getIntersectionPoint(const RectangleDescription& other_type, const LineDescription& line)
{
    return getIntersectionPoint<LineDescription, RectangleDescription>(line, other_type);
}

template<class T>
std::optional<sf::Vector2f> getIntersectionPoint(const T& other_type, const RectangleDescription& rect)
{
    return getIntersectionPoint<RectangleDescription, T>(rect, other_type);
}

void LineDescription::calculateCoefficients()
{
    coeff_a = direction_vector.x != 0 ? direction_vector.y / direction_vector.x : 0;
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

std::optional<sf::Vector2f> CircleDescription::getIntersectionPoint(const RectangleDescription& rect) const
{
    return ::physics::getIntersectionPoint(*this, rect);
}

std::optional<sf::Vector2f> RectangleDescription::getIntersectionPoint(const LineDescription& line) const
{
    return ::physics::getIntersectionPoint(*this, line);
}

std::optional<sf::Vector2f> RectangleDescription::getIntersectionPoint(const CircleDescription& circle) const
{
    return ::physics::getIntersectionPoint(*this, circle);
}

std::optional<sf::Vector2f> RectangleDescription::getIntersectionPoint(const RectangleDescription& rect) const
{
    return ::physics::getIntersectionPoint(*this, rect);
}


}  // physics