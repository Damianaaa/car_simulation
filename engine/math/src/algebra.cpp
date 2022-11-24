#include "engine/math/hdr/algebra.h"
#include <algorithm>
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

}