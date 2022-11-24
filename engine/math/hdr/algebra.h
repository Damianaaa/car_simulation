#ifndef ENGINE_MATH_HDR_ALGEBRA_H
#define ENGINE_MATH_HDR_ALGEBRA_H

#include <SFML/Graphics.hpp>

// Get rid of sqrt as much as possible, e.g. in distance comparison it is not rly needed.

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& point);

namespace math
{

float crossProduct(const sf::Vector2f& p1, const sf::Vector2f& p2);

float getDistanceBetweenPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);

float getDistanceBetweenPointsSquared(const sf::Vector2f& p1, const sf::Vector2f& p2);

sf::Vector2f getClosestPoint(const sf::Vector2f& reference_point, const std::vector<sf::Vector2f>& points);

}  // math

#endif
