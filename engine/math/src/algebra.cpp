#include "engine/math/hdr/algebra.h"
#include "engine/math/hdr/numerical_utilities.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <math.h>

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& point)
{
    os << "Point- x: " << point.x << "; y: " <<  point.y << "\n";
    return os;
}

namespace math
{

float crossProduct(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return (p1.x * p2.y) - (p1.y * p2.x);
}

float getDistanceBetweenPoints(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float getDistanceBetweenPointsSquared(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

sf::Vector2f getClosestPoint(const sf::Vector2f& reference_point, const std::vector<sf::Vector2f>& points)
{
    return *std::min_element(points.cbegin(), points.cend(), [&reference_point](const auto& p1, const auto& p2)
        {
            return getDistanceBetweenPointsSquared(reference_point, p1) < getDistanceBetweenPointsSquared(reference_point, p2);
        }
    );
}

bool checkBounds(const sf::Vector2f& ref_point, const sf::Vector2f& start, const sf::Vector2f& end)
{
    const auto [x_min, x_max] = end.x >= start.x ? std::pair{start.x, end.x} : std::pair{end.x, start.x};
    const auto [y_min, y_max] = end.y >= start.y ? std::pair{start.y, end.y} : std::pair{end.y, start.y};
    const auto [x_ref, y_ref] = ref_point;
    const bool in_bound{fGEqual(x_ref, x_min) && fLEqual(x_ref, x_max) && fGEqual(y_ref, y_min) && fLEqual(y_ref, y_max)};
    return in_bound;
}


}