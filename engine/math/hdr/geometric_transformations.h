#ifndef ENGINE_MATH_HDR_GEOMETRIC_TRANSFORMATIONS_H
#define ENGINE_MATH_HDR_GEOMETRIC_TRANSFORMATIONS_H

#include <array>
#include <math.h>
#include <SFML/System/Vector2.hpp>

constexpr uint8_t number_of_borders{4};
using RectangleBorders = std::array<sf::Vector2f, number_of_borders>;


namespace math
{
sf::Vector2f getTransformedBorder(const sf::Vector2f center_point, const sf::Vector2f border_relative_pos, const float angle)
{
    sf::Vector2f new_relative_border_pos{
        border_relative_pos.x * cos(angle) - (border_relative_pos.y * sin(angle)),
        border_relative_pos.x * sin(angle) + (border_relative_pos.y * cos(angle)),
    };
    return center_point + new_relative_border_pos;
}

// For now it is assumed that car has 0 rotation at the beginning
/**
 * @brief Get the Borders From Center Point object
 * 1-------2
 * |       |
 * |   c   |
 * |       |
 * 4-------3
 */
RectangleBorders getBordersFromCenterPoint(const sf::Vector2f& center_point, const sf::Vector2f& size, const float angle)
{
    RectangleBorders borders;
    // Could be constexpr based on the constexpr car size
    const std::array<sf::Vector2f, number_of_borders> border_placement_table{
        sf::Vector2f{-size.x / 2, size.y / 2},
        sf::Vector2f{size.x / 2, size.y / 2},
        sf::Vector2f{size.x / 2, -size.y / 2},
        sf::Vector2f{-size.x / 2, -size.y / 2}
    };

    for (uint8_t idx=0; idx < number_of_borders; ++idx)
    {
        borders[idx] = getTransformedBorder(center_point, border_placement_table[idx], angle);
    }
    return borders;
}

}  // math

#endif  // ENGINE_MATH_HDR_GEOMETRIC_TRANSFORMATIONS_H